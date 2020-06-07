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
		virtual void initial() {};	//初始化
		virtual LightSample sample(Union& generations, const Vector3& position) { return zero(); };	//获取辐照度
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
		LightSample sample(Union& generations,const Vector3& position);	//获取辐照度
		Color LightRender(Union& generations, IntersectResult& res);	//光照渲染
		bool shadow;	//辐照度
	private:
		Vector3 direction;	//平行光方向
		
	};

	class PointLight :public LightSample
	{
	public:
		PointLight() = default;
		PointLight(const Vector3& L,const Color& c);
		void initialize();
		LightSample sample(Union& generations, const Vector3& position);	//获取辐照度
		Color LightRender(Union& generations, IntersectResult& res);	//光照渲染
		bool shadow;	//阴影
	private:
		Vector3 position;	//点光源位置
		
	};

	class SpotLight :public LightSample	//聚光灯
	{
	public:
		SpotLight() = default;
		SpotLight(const Vector3& _position, const Color& _intensity, const Vector3& _direction, float _theta, float _phi, float _falloff);
		void initialize();
		LightSample sample(Union& _generations, const Vector3& _position);
		Color LightRender(Union& _generations, IntersectResult& _res);
		bool shadow;	//阴影
	private:
		Color intensity;	//光源强度
		Vector3 position;	//聚光灯中心位置
		Vector3 direction;	//聚光灯方向
		float theta;	//内圆锥顶角角度
		float phi;	//外圆锥顶角角度
		float falloff;	//衰减
		
	};
}



#endif // !LIGHT_H
