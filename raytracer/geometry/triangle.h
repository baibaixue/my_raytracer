#pragma once
#ifndef TRANGLE_H
#define TRANGLE_H
#include"geometry/Union.h"

namespace rt {
	class Triangle :public Generation
	{
	public:
		Triangle() = default;
		Triangle(const Triangle& _triangle);
		Triangle(const Vector3& _a, const Vector3& _b, const Vector3& _c);
		//void initialize();
		IntersectResult intersect(Ray3& _ray);	//光线相交
		void move_location(const Vector3& _vec);	//变换位置
		void turn_location(const float& _pitch, const float& _yaw);	//绕中心点旋转
	private:
		Vector3 a;
		Vector3 b;
		Vector3 c;
	};
}

#endif // !TRANGLE_H
