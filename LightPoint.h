//Kristian Sterjo & Albrit Bendo
#pragma once

#include "ILight.h"
using namespace std;

/**
 * @brief Point light source class
 */
class CLightPoint : public ILight
{
public:
	/**
	 * @brief Constructor
	 * @param position The position (origin) of the light source
	 * @param intensity The emission color and strength of the light source
	 */
	CLightPoint(Vec3f intensity, Vec3f position)
		: m_intensity(intensity)
		, m_position(position)
	{} 
	virtual ~CLightPoint(void) = default;

	virtual std::optional<Vec3f> Illuminate(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		ray.dir = normalize(m_position - ray.org);

		ray.t   = ray.dir.dot(ray.dir);

		auto k = make_optional<Vec3f>(0.25 * m_intensity/Pif );

		return k;
	}


private:
	Vec3f m_intensity; ///< emission (red, green, blue)
	Vec3f m_position;  ///< The light source origin
};