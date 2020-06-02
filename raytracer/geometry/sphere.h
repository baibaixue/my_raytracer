#ifndef _RAYTRACER_SPHERE_H_
#define _RAYTRACER_SPHERE_H_


#include"base/header.h"
#include"base/vector3.h"
#include"ray/ray.h"
#include"geometry/union.h"
#include"ray/IntersectResult.h"
namespace rt
{


	class Sphere : public Generation	//��������
	{
	public:
		Sphere() = default;
		Sphere(const Vector3& _dot, float _radius);
		Sphere(const Sphere& _sphere);

		float SqrRadius()const;	//�뾶ƽ��
		IntersectResult intersect(Ray3& _ray);	//�����ཻ
		void move_location(const Vector3& vec);	//�任����λ��
		void turn_location(const float& pitch, const float& yaw);	//�����������ĵ���ת
		~Sphere();
	private:
		Vector3 center;	//��������
		float radius;	//����뾶

	};


}
#endif // !RAYTRACER_SPHERE_H_