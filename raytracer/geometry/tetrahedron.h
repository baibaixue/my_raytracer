#pragma once
#ifndef TETRAHEDRON_H
#define TRTRAHEDRON_H
#include "geometry/Union.h"
#include "geometry/triangle.h"
namespace rt {
	class Tetrahedron :public Generation
	{
	public:
		Tetrahedron() = default;
		Tetrahedron(Vector3& _a, Vector3& _b, Vector3& _c, Vector3& _d);
		void initial();
		IntersectResult intersect(Ray3& _ray);	//�����ཻ
		void move_location(const Vector3& _vec);	//�任λ��
		void turn_location(const float& _pitch, const float& _yaw);	//�����ĵ���ת
	private:
		Triangle a;
		Triangle b;
		Triangle c;
		Triangle d;

	};
}
#endif // !TETRAHEDRON_H
