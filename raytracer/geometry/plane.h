#ifndef _RAYTRACER_PLANE_H_
#define _RAYTRACER_PLANE_H_
#include"base/header.h"
#include"base/vector3.h"
#include"base/mathf.h"
#include"geometry/sphere.h"
#include"geometry/union.h"
#include"ray/IntersectResult.h"
namespace rt
{
	class Plane:public Generation	//������ƽ��
	{
	public:
		Plane() = default;
		Plane(const Vector3& _normal,const Vector3& _position,float _d );	
		Plane(const Plane& _plane);

		IntersectResult intersect(Ray3& _ray);
		void move_location(const Vector3& vec);
		void turn_location(const float& pitch, const float& yaw);
		~Plane();
	private:
		Vector3 normal;	//������
		Vector3 position;	//λ��
		float d;	//�ռ�ԭ�㵽ƽ�����̾���
	};

	
}

#endif // !_RAYTRACER_PLANE_H_
