#ifndef _RAYTRACER_PLANE_H_
#define _RAYTRACER_PLANE_H_
#include"base/header.h"
#include"base/vector3.h"
#include"base/mathf.h"
#include"base/sphere.h"
#include"base/union.h"
#include"base/IntersectResult.h"
namespace rt
{
	class Plane:public Generation
	{
	public:
		Plane() = default;
		Plane(const Vector3& _normal,const Vector3& _position,float _d );
		Plane(const Plane& _plane);

		IntersectResult intersect(Ray3& _ray);
		~Plane();
	private:
		Vector3 normal;
		Vector3 position;
		float d;
	};

	
}

#endif // !_RAYTRACER_PLANE_H_
