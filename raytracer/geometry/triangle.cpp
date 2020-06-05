#include "geometry/triangle.h"

namespace rt {
	Triangle::Triangle(const Triangle& _triangle)
	{
		a = _triangle.a;
		b = _triangle.b;
		c = _triangle.c;
	}

	Triangle::Triangle(const Vector3& _a, const Vector3& _b, const Vector3& _c)
	{
		a = _a;
		b = _b;
		c = _c;
	}
	IntersectResult Triangle::intersect(Ray3& _ray)
	{
		Vector3 e1 = b.Subtract(a);	//e1=V2-V1
		Vector3 e2 = c.Subtract(a);	//e2=V3-V1

		Vector3 P = _ray.direction.Cross(e2);	//P=DXe2
		float det = e1.Dot(P);	//e1°§P
		if (det == 0 ) {
			return IntersectResult::noHit();
		}

		float inv_det = 1.f / det;	//	1/(e1°§P)
		Vector3 T = _ray.origin.Subtract(a);	//T = O-V1
		float u = T.Dot(P) * inv_det;	//º∆À„u
		if (u < 0.f) {	
			return IntersectResult::noHit();
		}
		Vector3 Q = T.Cross(e1);
		float v = _ray.direction.Dot(Q) * inv_det;	//º∆À„v
		if (v < 0.f || u + v > 1.f) {
			return IntersectResult::noHit();
		}
		float t = e2.Dot(Q) * inv_det;
		if (t > 0.0001f) {	
			IntersectResult result = IntersectResult::noHit();
			result.is_hit = true;
			result.material = material;
			result.distance = t;
			result.position = _ray.GetPoint(result.distance);
			result.normal = (e1.Cross(e2)).Normalize();
			return result;
		}

		return IntersectResult::noHit();
	}

	void Triangle::move_location(const Vector3& _vec)
	{
		a.Add(_vec);
		b.Add(_vec);
		c.Add(_vec);
	}

	void rt::Triangle::turn_location(const float& _pitch, const float& _yaw)
	{
		float x = a.x;
		float y = a.y;
		float z = a.z;
		a.x = x * Mathf::Cos(_pitch * Mathf::deg2rad) - z * Mathf::Sin(_pitch * Mathf::deg2rad);
		a.z = x * Mathf::Sin(_pitch * Mathf::deg2rad) + z * Mathf::Cos(_pitch * Mathf::deg2rad);
		a.y = y;
		x = a.x;
		y = a.y;
		z = a.z;
		a.y = y * Mathf::Cos(_yaw * Mathf::deg2rad) - z * Mathf::Sin(_yaw * Mathf::deg2rad);
		a.z = y * Mathf::Sin(_yaw * Mathf::deg2rad) + z * Mathf::Cos(_yaw * Mathf::deg2rad);
		a.x = x;

		x = b.x;
		y = b.y;
		z = b.z;
		b.x = x * Mathf::Cos(_pitch * Mathf::deg2rad) - z * Mathf::Sin(_pitch * Mathf::deg2rad);
		b.z = x * Mathf::Sin(_pitch * Mathf::deg2rad) + z * Mathf::Cos(_pitch * Mathf::deg2rad);
		b.y = y;
		x = b.x;
		y = b.y;
		z = b.z;
		b.y = y * Mathf::Cos(_yaw * Mathf::deg2rad) - z * Mathf::Sin(_yaw * Mathf::deg2rad);
		b.z = y * Mathf::Sin(_yaw * Mathf::deg2rad) + z * Mathf::Cos(_yaw * Mathf::deg2rad);
		b.x = x;

		x = c.x;
		y = c.y;
		z = c.z;
		c.x = x * Mathf::Cos(_pitch * Mathf::deg2rad) - z * Mathf::Sin(_pitch * Mathf::deg2rad);
		c.z = x * Mathf::Sin(_pitch * Mathf::deg2rad) + z * Mathf::Cos(_pitch * Mathf::deg2rad);
		c.y = y;
		x = c.x;
		y = c.y;
		z = c.z;
		c.y = y * Mathf::Cos(_yaw * Mathf::deg2rad) - z * Mathf::Sin(_yaw * Mathf::deg2rad);
		c.z = y * Mathf::Sin(_yaw * Mathf::deg2rad) + z * Mathf::Cos(_yaw * Mathf::deg2rad);
		c.x = x;

	}
}

