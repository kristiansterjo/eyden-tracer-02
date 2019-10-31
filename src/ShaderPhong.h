//Kristian Sterjo & Albrit Bendo
#pragma once

#include "ShaderFlat.h"

class CScene;

class CShaderPhong : public CShaderFlat
{
public:
	/**
	 * @brief Constructor
	 * @param scene Reference to the scene
	 * @param color The color of the object
	 * @param ka The ambient coefficient
	 * @param kd The diffuse reflection coefficients
	 * @param ks The specular refelection coefficients
	 * @param ke The shininess exponent
	 */
	CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
		: CShaderFlat(color)
		, m_scene(scene)
		, m_ka(ka)
		, m_kd(kd)
		, m_ks(ks)
		, m_ke(ke)
	{}
	virtual ~CShaderPhong(void) = default;

	virtual Vec3f Shade(const Ray& ray) const override
	{
		// --- PUT YOUR CODE HERE ---

        int n=1;
		Vec3f diff = 0;
		Vec3f spec = 0;
		
		Ray photon;
		photon.org = ray.org + (ray.t*ray.dir);
		
		for(auto light : m_scene.m_vpLights){
            for(int i=0;i<n;i++){
				auto x = light->Illuminate(photon);
				if(!x){
					continue;
                }
                
                if( m_scene.Occluded(photon)){
                    continue;
                }

                //following the methods for calculating the reflected ray from the lecture slides
				Vec3f incident	= photon.dir;
				Vec3f reflected = 2 * incident.dot( ray.hit->GetNormal(ray) ) * (ray.hit->GetNormal(ray)) - incident;
				diff = diff + (*x) * std::max(0.f, incident.dot(ray.hit->GetNormal(ray)));
				spec = spec + (*x) * std::pow(std::max(0.f, reflected.dot((-1)*ray.dir)), m_ke);
            }
        }

        auto k = m_ka * CShaderFlat::Shade(ray) * 1.1 + m_kd * CShaderFlat::Shade(ray).mul(diff/n) + m_ks * RGB(1, 1, 1).mul(spec/n);

		return  k;
        
	}

	
private:
	CScene& m_scene;
	float 	m_ka;    ///< ambient coefficient
	float 	m_kd;    ///< diffuse reflection coefficients
	float 	m_ks;    ///< specular refelection coefficients
	float 	m_ke;    ///< shininess exponent
};