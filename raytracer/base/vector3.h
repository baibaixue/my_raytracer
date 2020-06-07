#pragma once
#include "base/header.h"

namespace rt
{
	struct Vector3 
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		Vector3() = default;	//默认构造函数
		Vector3(float _x, float _y, float _z);	//复制构造函数	
		Vector3(const Vector3& v);	//复制构造函数

		float Length()const;	//三维向量长度
		float SqrtLength()const;	//向量长度的平方
		const Vector3 Normalize() const;	//求单位向量
		const Vector3 Negate() const;	//求反向量
		const Vector3 Add(const Vector3& v) const;	//两向量相加
		const Vector3 Subtract(const Vector3& v)const;	//两向量相减
		const Vector3 Mulitiply(float f)const;	//向量数乘
		const Vector3 Divide(float f)const;	//向量数除
		const Vector3 Cross(const Vector3& v)const;	//向量叉乘,结果垂直两向量所在平面的向量
		float Dot(const Vector3& v)const;	//向量点乘

		static const Vector3 zero;	//零向量
		static const Vector3 one;	//向量（1，1，1）
		static const Vector3 front;	//向前单位向量
		static const Vector3 up;	//向上单位向量
		static const Vector3 down;	//向下单位向量
		static const Vector3 right;	//向右单位向量
		static const Vector3 left;	//向左单位向量
		static const Vector3 back;	//向后单位向量



	};
}