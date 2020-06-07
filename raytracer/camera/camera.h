#pragma once
#ifndef _RAYTRACER_CAMERA_H_
#define _RAYTRACER_CAMERA_H_

#include"base/header.h"
#include"base/vector3.h"
#include"ray/ray.h"

namespace rt
{
	struct Camera	//相机类
	{
		virtual void Initialize() = 0;	//初始化
		virtual const Ray3 GenerateRay(float x, float y)const =0;	//生成光线

	};

	struct PerspectiveCamera :Camera	//继承，透视相机，能表现近小远大的视觉效果
	{
		PerspectiveCamera() = default;	//构造函数
		PerspectiveCamera(	//复制构造函数
			Vector3& _eye,
			const Vector3& _front,
			const Vector3& _up,
			float _fov
		);
		virtual void Initialize();	//相机初始化
		virtual const Ray3 GenerateRay(float x, float y)const;	//生成光线
		Vector3& getEye();	//返回相机视点
		Vector3& getFront();	
		Vector3& getUp();
		float fov = 90.f;	//代表水平和垂直方向的视野角度
	private:
		Vector3 eye = Vector3::zero;	//视点，默认为0
		Vector3 front = Vector3::front;	//向前的单位向量
		Vector3 up = Vector3::up;	//向上的单位向量
		

		Vector3 right = Vector3::right;	//向右的单位向量
		Vector3 refUp = Vector3::up;	//向上的单位向量
		float fovScale = 0.f;	//相对于相机和物体距离为单位长度时的视角范围

	};

}
#endif // !_RAYTRACER_CAMERA_H_




