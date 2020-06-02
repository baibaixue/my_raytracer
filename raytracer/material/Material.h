#ifndef _RAYTRACER_MATERIAL_H_
#define _RAYTRACER_MATERIAL_H_
#include "base/header.h"
#include "base/mathf.h"
#include "base/vector3.h"
#include "base/color.h"
#include "ray/ray.h"
namespace rt
{

	struct Material	//材质类
	{
	public:
		Material() = default;
		Material(float _reflectiveness);
		virtual Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);	//光线和材质相交情况
		float reflectiveness;	//材质反射度
		~Material();
	};
	struct CheckerMaterial :public Material//格子材质
	{
	public:
		CheckerMaterial(float _scale,float _reflectiveness);
		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		~CheckerMaterial();
	private:
		float scale;//一坐标单位有多少格子
	};


	struct PhongMaterial :public Material//Phong高光材质 光照材质
	{
	public:
		Vector3 lightDir = Vector3(2.f,1.f, 2.f).Normalize();	//光照方向
		Color lightcolor = Color::white;	//光照颜色为白色
		PhongMaterial(const Color& _diffues,const Color& _specular, float _shininess,float _reflectiveness);

		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);

		~PhongMaterial();

	private:
		Color diffuse;//漫反射
		Color specular;//镜反射
		float shininess;//shininess 光线
		
	};
}


#endif // !RAYTRACER_MATERIAL_H_
