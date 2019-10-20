#pragma once
#include"base/header.h"
#include"vector3.h"

namespace rt
{
	struct Ray3
	{
		Vector3 origin = Vector3::zero;//光源射出的方向，初始化为零向量
		Vector3 direction = Vector3::front;//光线方向

		Ray3() = default;
		Ray3(const Vector3& _origin, const Vector3& _direction);

		const Vector3 GetPoint(float t)const ;//发射光线
		//即光线ray(t)=o(origin)+t(光线发射距离)*d(光线发射方向，单位向量）

	};
}
