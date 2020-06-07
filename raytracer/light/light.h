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
		virtual void initial() {};	//��ʼ��
		virtual LightSample sample(Union& generations, const Vector3& position) { return zero(); };	//��ȡ���ն�
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
		LightSample sample(Union& generations,const Vector3& position);	//��ȡ���ն�
		Color LightRender(Union& generations, IntersectResult& res);	//������Ⱦ
		bool shadow;	//���ն�
	private:
		Vector3 direction;	//ƽ�йⷽ��
		
	};

	class PointLight :public LightSample
	{
	public:
		PointLight() = default;
		PointLight(const Vector3& L,const Color& c);
		void initialize();
		LightSample sample(Union& generations, const Vector3& position);	//��ȡ���ն�
		Color LightRender(Union& generations, IntersectResult& res);	//������Ⱦ
		bool shadow;	//��Ӱ
	private:
		Vector3 position;	//���Դλ��
		
	};

	class SpotLight :public LightSample	//�۹��
	{
	public:
		SpotLight() = default;
		SpotLight(const Vector3& _position, const Color& _intensity, const Vector3& _direction, float _theta, float _phi, float _falloff);
		void initialize();
		LightSample sample(Union& _generations, const Vector3& _position);
		Color LightRender(Union& _generations, IntersectResult& _res);
		bool shadow;	//��Ӱ
	private:
		Color intensity;	//��Դǿ��
		Vector3 position;	//�۹������λ��
		Vector3 direction;	//�۹�Ʒ���
		float theta;	//��Բ׶���ǽǶ�
		float phi;	//��Բ׶���ǽǶ�
		float falloff;	//˥��
		
	};
}



#endif // !LIGHT_H
