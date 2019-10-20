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
	struct CheckerMaterial :public Material//���Ӳ���
	{
	public:
		CheckerMaterial(float _scale,float _reflectiveness);
		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		//float reflectiveness;//������
		~CheckerMaterial();
	private:
		float scale;//һ���굥λ�ж��ٸ���
		//float reflectiveness;
	};


	struct PhongMaterial :public Material//Phong���� ���ղ���
	{
	public:
		Vector3 lightDir = Vector3(2.f,1.f, 2.f).Normalize();
		Color lightcolor = Color::white;
		PhongMaterial(const Color& _diffues,const Color& _specular, float _shininess,float _reflectiveness);

		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		//float reflectiveness;//reflectiveness ����
		~PhongMaterial();

	private:
		Color diffuse;//������ɢ����͸������
		Color specular;//specular �߹�
		float shininess;//shininess ����
		
	};
}


#endif // !RAYTRACER_MATERIAL_H_
