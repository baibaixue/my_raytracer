#ifndef _RAYTRACER_MATERIAL_H_
#define _RAYTRACER_MATERIAL_H_
#include "base/header.h"
#include "base/mathf.h"
#include "base/vector3.h"
#include "base/color.h"
#include "ray/ray.h"
namespace rt
{

	struct Material	//������
	{
	public:
		Material() = default;
		Material(float _reflectiveness);
		virtual Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);	//���ߺͲ����ཻ���
		float reflectiveness;	//���ʷ����
		~Material();
	};
	struct CheckerMaterial :public Material//���Ӳ���
	{
	public:
		CheckerMaterial(float _scale,float _reflectiveness);
		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);
		~CheckerMaterial();
	private:
		float scale;//һ���굥λ�ж��ٸ���
	};


	struct PhongMaterial :public Material//Phong�߹���� ���ղ���
	{
	public:
		Vector3 lightDir = Vector3(2.f,1.f, 2.f).Normalize();	//���շ���
		Color lightcolor = Color::white;	//������ɫΪ��ɫ
		PhongMaterial(const Color& _diffues,const Color& _specular, float _shininess,float _reflectiveness);

		Color prototype(Ray3& _ray, Vector3& _position, Vector3& _normal);

		~PhongMaterial();

	private:
		Color diffuse;//������
		Color specular;//������
		float shininess;//shininess ����
		
	};
}


#endif // !RAYTRACER_MATERIAL_H_
