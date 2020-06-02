#pragma once
#ifndef _RAYTRACER_CAMERA_H_
#define _RAYTRACER_CAMERA_H_

#include"base/header.h"
#include"base/vector3.h"
#include"ray/ray.h"

namespace rt
{
	struct Camera	//�����
	{
		virtual void Initialize() = 0;	//��ʼ��
		virtual const Ray3 GenerateRay(float x, float y)const =0;	//���ɹ���

	};

	struct PerspectiveCamera :Camera	//�̳У�͸��������ܱ��ֽ�СԶ����Ӿ�Ч��
	{
		PerspectiveCamera() = default;	//���캯��
		PerspectiveCamera(	//���ƹ��캯��
			Vector3& _eye,
			const Vector3& _front,
			const Vector3& _up,
			float _fov
		);
		virtual void Initialize();	//�����ʼ��
		virtual const Ray3 GenerateRay(float x, float y)const;	//���ɹ���
		Vector3& getEye();	//��������ӵ�
		Vector3& getFront();	
		Vector3& getUp();
		float fov = 90.f;	//����ˮƽ�ʹ�ֱ�������Ұ�Ƕ�
	private:
		Vector3 eye = Vector3::zero;	//�ӵ㣬Ĭ��Ϊ0
		Vector3 front = Vector3::front;	//��ǰ�ĵ�λ����
		Vector3 up = Vector3::up;	//���ϵĵ�λ����
		

		Vector3 right = Vector3::right;	//���ҵĵ�λ����
		Vector3 refUp = Vector3::up;	//���ϵĵ�λ����
		float fovScale = 0.f;	//�����������������Ϊ��λ����ʱ���ӽǷ�Χ

	};

}
#endif // !_RAYTRACER_CAMERA_H_




