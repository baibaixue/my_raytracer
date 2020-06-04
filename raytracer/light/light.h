#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include"base/header.h"
#include"base/vector3.h"
#include"base/color.h"
#include"geometry/Union.h"
#include"ray/ray.h"
#include"ray/IntersectResult.h"
namespace rt
{
	class LightSample	//��Դ�ӿ�
	{
	public:
		LightSample() = default;
		LightSample(const LightSample& light) {
			L = light.L;
			EL = light.EL;
		};
		LightSample(const Vector3& v, const Color& c) {
			L = v;
			EL = c;
		}
		
		static LightSample zero() {
			return LightSample(Vector3::zero,Color::black);
		}
		/*
		bool is_zero() {
			if (L.x == 0.f && L.y == 0.f && L.z == 0.f && EL.a == 0.f && EL.b == 0.f && EL.g == 0.f) {
				return true;
			}
			else {
				return false;
			}
		}*/
		virtual void initial() {};	//��ʼ��
		virtual LightSample sample(Union& generations, const Vector3& position) { return zero(); };	//��Ӱ
		virtual Color LightRender(Union& generations,IntersectResult& res) { return Color::black; };	//������Ⱦ
		Vector3 L;	//�ⷽ��
		Color EL;	//������
	};

	class DirectionalLight :public LightSample	//ƽ�й�Դ
	{
	public:
		DirectionalLight() = default;
		DirectionalLight(const Vector3& L, const Color& c);
		void initialize();
		LightSample sample(Union& generations,const Vector3& position);	//��Ӱ
		Color LightRender(Union& generations, IntersectResult& res);	//������Ⱦ

	private:
		Vector3 direction;	//ƽ�йⷽ��
		bool shadow;	//�Ƿ������Ӱ
	};

	class PointLight :public LightSample
	{
	public:
		PointLight() = default;
		PointLight(const Vector3& L,const Color& c);
		void initialize();
		LightSample sample(Union& generations, const Vector3& position);	//��Ӱ
		Color LightRender(Union& generations, IntersectResult& res);	//������Ⱦ

	private:
		Vector3 position;	//���Դλ��
		bool shadow;	//�Ƿ������Ӱ
	};
}



#endif // !LIGHT_H
