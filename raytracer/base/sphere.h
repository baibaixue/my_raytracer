#ifndef _RAYTRACER_SPHERE_H_
#define _RAYTRACER_SPHERE_H_


#include"base/header.h"
#include"base/vector3.h"
#include"base/ray.h"
#include"base/union.h"
#include"base/IntersectResult.h"
namespace rt
{


	class Sphere : public Generation
	{
	public:
		Sphere() = default;
		Sphere(const Vector3& _dot, float _radius);
		Sphere(const Sphere& _sphere);

		float SqrRadius()const;//�뾶ƽ��
		IntersectResult intersect(Ray3& _ray);//���߽���
		~Sphere();
	private:
		Vector3 center;//��������
		float radius;//����뾶

	};


}
#endif // !RAYTRACER_SPHERE_H_