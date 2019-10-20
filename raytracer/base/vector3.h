#pragma once
#include "base/header.h"

namespace rt
{
	struct Vector3 
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		Vector3() = default;//让编译器依然自动生成相应的默认构造函数
		//比如你已经定义了一个有参的构造函数，
		//那么默认构造函数编译器就不再生成了，
		//你可以通过default关键字让默认构造函数恢复
		//相对于 = default，还有一个 = delete，
		//顾名思义就是禁止生成
		Vector3(float _x, float _y, float _z);
		Vector3(const Vector3& v);

		float Length()const;//三维向量长度
		float SqrtLength()const;//向量长度的平方
		const Vector3 Normalize() const;//求单位向量
		const Vector3 Negate() const;//求反向量
		const Vector3 Add(const Vector3& v) const;//两向量相加
		const Vector3 Subtract(const Vector3& v)const;//两向量相减
		const Vector3 Mulitiply(float f)const;//向量数乘
		const Vector3 Divide(float f)const;//向量数除
		const Vector3 Cross(const Vector3& v)const;//向量叉乘
		float Dot(const Vector3& v)const;//向量点乘

		static const Vector3 zero;//零向量
		static const Vector3 one;//‘单位’向量
		static const Vector3 front;//向前‘单位’向量
		static const Vector3 up;//向上‘单位’向量
		static const Vector3 down;//向下‘单位’向量
		static const Vector3 right;//向右‘单位’向量
		static const Vector3 left;//向左‘单位’向量
		static const Vector3 back;//向后‘单位’向量



	};
}