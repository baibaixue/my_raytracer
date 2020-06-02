#pragma once
#include "base/header.h"

namespace rt
{
	struct Vector3 
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		Vector3() = default;	//�ñ�������Ȼ�Զ�������Ӧ��Ĭ�Ϲ��캯��
		Vector3(float _x, float _y, float _z);	//���ƹ��캯��	
		Vector3(const Vector3& v);	//���ƹ��캯��

		float Length()const;	//��ά��������
		float SqrtLength()const;	//�������ȵ�ƽ��
		const Vector3 Normalize() const;	//��λ����
		const Vector3 Negate() const;	//������
		const Vector3 Add(const Vector3& v) const;	//���������
		const Vector3 Subtract(const Vector3& v)const;	//���������
		const Vector3 Mulitiply(float f)const;	//��������
		const Vector3 Divide(float f)const;	//��������
		const Vector3 Cross(const Vector3& v)const;	//�������,�����ֱ����������ƽ�������
		float Dot(const Vector3& v)const;	//�������

		static const Vector3 zero;	//������
		static const Vector3 one;	//����λ������
		static const Vector3 front;	//��ǰ����λ������
		static const Vector3 up;	//���ϡ���λ������
		static const Vector3 down;	//���¡���λ������
		static const Vector3 right;	//���ҡ���λ������
		static const Vector3 left;	//���󡮵�λ������
		static const Vector3 back;	//��󡮵�λ������



	};
}