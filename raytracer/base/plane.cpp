#include"base/plane.h"
#include"base/IntersectResult.h"
namespace rt
{
	Plane::Plane(const Vector3& _normal,const Vector3& _position, float _d)
		:normal(_normal)
		,position(_position)
		,d(_d)
	{}

	Plane::Plane(const Plane& _plane)
		:normal(_plane.normal)
		,position(_plane.position)
		,d(_plane.d)
	{}

	IntersectResult Plane::intersect(Ray3& _ray)	//判断光线和平面是否有交点
	{
		float a = _ray.direction.Dot(normal);
		if (a >= 0)
		{
			return IntersectResult::noHit();
		}

		float b = normal.Dot(_ray.origin.Subtract(position));
		IntersectResult result = IntersectResult::noHit();
		result.is_hit = true;
		result.material = material;
		result.distance = -b/ a;
		result.position = _ray.GetPoint(result.distance);
		result.normal = normal;
		return result;
	}

	Plane::~Plane() {};
}