#include "Material.h"
#include "base/mathf.h"
namespace rt
{

	Material::Material(float _reflectiveness)
		:reflectiveness(_reflectiveness)
	{
	}

	Color Material::prototype(Ray3& _ray, Vector3& _position, Vector3& _normal) 
	{
		return Color::white;
	};

	Material::~Material() {};

	CheckerMaterial::CheckerMaterial(float _scale, float reflectiveness)
		:scale(_scale)
		, Material(reflectiveness)
		{
		}
	
	Color CheckerMaterial::prototype(Ray3& _ray, Vector3& _position, Vector3& _normal)//格子材质，返回黑色和白色
	{
		return Mathf::Abs((int)(Mathf::Floor(_position.x  * scale) + Mathf::Floor(_position.z * scale))%2) < 1 ? Color::black : Color::white;
	}
	CheckerMaterial::~CheckerMaterial() {};

	PhongMaterial::PhongMaterial(const Color& _diffues,const Color& _specular, float _shininess,float _reflectiveness)
		:Material(_reflectiveness)
		,diffuse(_diffues)
		,specular(_specular)
		,shininess(_shininess)
		//,reflectiveness(_reflectiveness)
		{}

	Color PhongMaterial::prototype(Ray3& _ray, Vector3& _position, Vector3& _normal)
	{
		
		float NdotL = _normal.Dot(lightDir);
		Vector3 H = (lightDir.Subtract(_ray.direction)).Normalize();
		float NdotH = _normal.Dot(H);
		const Color diffuseTerm = diffuse.Multiply(Mathf::Max(NdotL, 0.f));
		const Color specularTerm = specular.Multiply(Mathf::Pow(Mathf::Max(NdotH, 0.f), shininess));
		return lightcolor.Modulate(diffuseTerm.Add(specularTerm));
		
		//return diffuseTerm;
	}

	PhongMaterial::~PhongMaterial() {};

}