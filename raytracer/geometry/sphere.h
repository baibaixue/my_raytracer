#ifndef _RAYTRACER_SPHERE_H_
#define _RAYTRACER_SPHERE_H_


#include"base/header.h"
#include"base/vector3.h"
#include"ray/ray.h"
#include"geometry/union.h"
#include"ray/IntersectResult.h"
namespace rt
{


	class Sphere : public Generation	//几何体球
	{
	public:
		Sphere() = default;
		Sphere(const Vector3& _dot, float _radius);
		Sphere(const Sphere& _sphere);

		float SqrRadius()const;	//半径平方
		IntersectResult intersect(Ray3& _ray);	//光线相交
		void move_location(const Vector3& vec);	//变换球体位置
		void turn_location(const float& pitch, const float& yaw);	//几何体绕中心点旋转
		~Sphere();
	private:
		Vector3 center;	//球体中心
		float radius;	//球体半径

	};


}
#endif // !RAYTRACER_SPHERE_H_