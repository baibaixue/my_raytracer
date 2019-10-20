#ifndef _RAYTRACER_MATERIAL_H_
#define _RAYTRACER_MATERIAL_H_
#include "base/header.h"
#include "base/mathf.h"
#include "base/vector3.h"
#include "base/color.h"
#include "base/ray.h"
namespace rt
{

	struct Material
	{
	public:
		Material() = default;
		Material(float _reflectiveness);
		virtual Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		float reflectiveness;
		~Material();
	};
	struct CheckerMaterial :public Material//格子材质
	{
	public:
		CheckerMaterial(float _scale,float _reflectiveness);
		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		//float reflectiveness;//反射性
		~CheckerMaterial();
	private:
		float scale;//一坐标单位有多少格子
		//float reflectiveness;
	};


	struct PhongMaterial :public Material//Phong材质 光照材质
	{
	public:
		Vector3 lightDir = Vector3(2.f,1.f, 2.f).Normalize();
		Color lightcolor = Color::white;
		PhongMaterial(const Color& _diffues,const Color& _specular, float _shininess,float _reflectiveness);

		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		//float reflectiveness;//reflectiveness 反射
		~PhongMaterial();

	private:
		Color diffuse;//弥漫扩散，渗透，漫射
		Color specular;//specular 高光
		float shininess;//shininess 光线
		
	};
}


#endif // !RAYTRACER_MATERIAL_H_
