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
	class LightSample	//光源接口
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
		virtual void initial() {};	//初始化
		virtual LightSample sample(Union& generations, const Vector3& position) { return zero(); };	//阴影
		virtual Color LightRender(Union& generations,IntersectResult& res) { return Color::black; };	//光照渲染
		Vector3 L;	//光方向
		Color EL;	//光辐射度
	};

	class DirectionalLight :public LightSample	//平行光源
	{
	public:
		DirectionalLight() = default;
		DirectionalLight(const Vector3& L, const Color& c);
		void initialize();
		LightSample sample(Union& generations,const Vector3& position);	//阴影
		Color LightRender(Union& generations, IntersectResult& res);	//光照渲染

	private:
		Vector3 direction;	//平行光方向
		bool shadow;	//是否存在阴影
	};

	class PointLight :public LightSample
	{
	public:
		PointLight() = default;
		PointLight(const Vector3& L,const Color& c);
		void initialize();
		LightSample sample(Union& generations, const Vector3& position);	//阴影
		Color LightRender(Union& generations, IntersectResult& res);	//光照渲染

	private:
		Vector3 position;	//点光源位置
		bool shadow;	//是否存在阴影
	};
}



#endif // !LIGHT_H
