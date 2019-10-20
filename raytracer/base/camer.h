#pragma once
#ifndef _RAYTRACER_CAMERA_H_
#define _RAYTRACER_CAMERA_H_

#include"header.h"
#include"vector3.h"
#include"ray.h"

namespace rt
{
	struct Camera
	{
		virtual void Initialize() = 0;//初始化
		virtual const Ray3 GenerateRay(float x, float y)const =0;//生成光线

	};

	struct PerspectiveCamera :Camera//继承，透视相机
	{
		PerspectiveCamera() = default;
		PerspectiveCamera(
			Vector3& _eye,
			const Vector3& _front,
			const Vector3& _up,
			float _fov
		);//构造函数
		virtual void Initialize();
		virtual const Ray3 GenerateRay(float x, float y)const;
		Vector3& getEye();
		float fov = 90.f;
	private:
		Vector3 eye = Vector3::zero;
		Vector3 front = Vector3::front;
		Vector3 up = Vector3::up;
		

		Vector3 right = Vector3::right;
		Vector3 refUp = Vector3::up;
		float fovScale = 0.f;

	};

}
#endif // !_RAYTRACER_CAMERA_H_




