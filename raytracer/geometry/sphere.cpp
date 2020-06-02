#include"geometry/sphere.h"

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

	IntersectResult Sphere::intersect(Ray3& _ray)	//求光线和球是否有交点
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
	void Sphere::move_location(const Vector3& vec)
	{
		center = center.Add(vec);
		return ;
	}

	void Sphere::turn_location(const float& pitch, const float& yaw)
	{	
		float x = center.x;
		float y = center.y;
		float z = center.z;
		center.x = x * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad) - z * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad);
		center.z = x * rt::Mathf::Sin(pitch * rt::Mathf::deg2rad) + z * rt::Mathf::Cos(pitch * rt::Mathf::deg2rad);
		center.y = y;
		x = center.x;
		y = center.y;
		z = center.z;
		center.y = y * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad) - z * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad);
		center.z = y * rt::Mathf::Sin(yaw * rt::Mathf::deg2rad) + z * rt::Mathf::Cos(yaw * rt::Mathf::deg2rad);
		center.x = x;
		return;
	}

	Sphere::~Sphere() {};
}
