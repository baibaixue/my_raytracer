#include"base/sphere.h"

namespace rt
{
	Sphere::Sphere(const Vector3& _dot, float _radius)
		:center(_dot)
		, radius(_radius)
	{
	}

	Sphere::Sphere(const Sphere& _sphere)
		: center(_sphere.center)
		, radius(_sphere.radius)
	{
	}

	float Sphere::SqrRadius()const 
	{
		return radius * radius;
	}

	IntersectResult Sphere::intersect(Ray3& _ray)
	{
		Vector3 v = _ray.origin.Subtract(Sphere::center);
		float a0 = v.SqrtLength() - SqrRadius();
		float Ddotv = _ray.direction.Dot(v);
		

		if (Ddotv <= 0)
		{
			float discr = Ddotv * Ddotv - a0;
			if (discr >= 0)
			{
				IntersectResult result=IntersectResult::noHit();
				result.is_hit = true;
				result.material = material;
				result.distance = -Ddotv - rt::Mathf::Sqrt(discr);
				result.position = _ray.GetPoint(result.distance);
				result.normal = result.position.Subtract(Sphere::center).Normalize();
				return result;
			}
		}
		return IntersectResult::noHit();
	}
	Sphere::~Sphere() {};
}