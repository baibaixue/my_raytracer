#pragma once
#include"base/header.h"
#include"vector3.h"

namespace rt
{
	struct Ray3
	{
		Vector3 origin = Vector3::zero;//��Դ����ķ��򣬳�ʼ��Ϊ������
		Vector3 direction = Vector3::front;//���߷���

		Ray3() = default;
		Ray3(const Vector3& _origin, const Vector3& _direction);

		const Vector3 GetPoint(float t)const ;//�������
		//������ray(t)=o(origin)+t(���߷������)*d(���߷��䷽�򣬵�λ������

	};
}
