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
		return Color::black;
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
		//printf("r:%lf g:%lf b:%lf\n", diffuseTerm.r, diffuseTerm.g, diffuseTerm.b);
		return lightcolor.Modulate(diffuseTerm.Add(specularTerm));
		
		//return diffuseTerm;
	}

	PhongMaterial::~PhongMaterial() {};

	ColorMaterial::ColorMaterial(const Color& _color,float _reflectivenesss)
		:color(_color)
		, Material(_reflectivenesss)
	{
	}

	Color ColorMaterial::prototype(Ray3& _ray, Vector3& _position, Vector3& _normal)
	{
		
		long maxDepth = 30;	
		float dD = 255.0f / maxDepth;
		//printf("dD:%lf\n", dD);

		float d = Mathf::Sqrt(Mathf::Pow((_ray.origin.x - _position.x), 2.f) + Mathf::Pow((_ray.origin.y - _position.y), 2.f) + Mathf::Pow((_ray.origin.z - _position.z), 2.f));
		//printf("d:%lf\n", d);
		float t = Mathf::Min(Mathf::Abs(d*dD), 255.f);
		//printf("t:%lf\n", t);
		float depth = (float)(255.f - t);
		//printf("depth:%lf\n", depth);
		Color rescolor = Color32(1.f, color.r*(_normal.x*10 + depth), color.g*(_normal.y*10 + depth), color.b*(_normal.z*10 + depth));
		//printf("r:%lf g:%lf b:%lf\n", rescolor.r, rescolor.g, rescolor.b);
		return rescolor;
	}

	ColorMaterial::~ColorMaterial(){}

}