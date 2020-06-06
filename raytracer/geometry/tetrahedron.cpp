#include "tetrahedron.h"

namespace rt 
{
	Tetrahedron::Tetrahedron(Vector3& _a, Vector3& _b, Vector3& _c, Vector3& _d)
	{
		a = Triangle(_a, _b, _c);
		b = Triangle(_a, _c, _d);
		c = Triangle(_a, _d, _b);
		d = Triangle(_b, _d, _c);
	}

	void Tetrahedron::initial()
	{
		a.material = material;
		b.material = material;
		c.material = material;
		d.material = material;
	}

	IntersectResult Tetrahedron::intersect(Ray3& _ray)
	{
		initial();
		IntersectResult resmin = IntersectResult::noHit();
		IntersectResult resa, resb, resc, resd;
		resa = a.intersect(_ray);
		resb = b.intersect(_ray);
		resc = c.intersect(_ray);
		resd = d.intersect(_ray);
		float mindis = Mathf::inifinity;
		if (resa.is_hit && resa.distance < mindis) {
			resmin = resa;
			mindis = resa.distance;
		}
		if (resb.is_hit && resb.distance < mindis) {
			resmin = resb;
			mindis = resb.distance;
		}
		if (resc.is_hit && resc.distance < mindis) {
			resmin = resc;
			mindis = resc.distance;
		}
		if (resd.is_hit && resd.distance < mindis) {
			resmin = resd;
			mindis = resd.distance;
		}
		
		return IntersectResult(resmin);
	}

	void Tetrahedron::move_location(const Vector3& _vec)
	{
		a.move_location(_vec);
		b.move_location(_vec);
		c.move_location(_vec);
		d.move_location(_vec);
	}

	void Tetrahedron::turn_location(const float& _pitch, const float& _yaw)
	{
		a.turn_location(_pitch, _yaw);
		b.turn_location(_pitch, _yaw);
		c.turn_location(_pitch, _yaw);
		d.turn_location(_pitch, _yaw);
	}
}

