#include"light.h"
namespace rt 
{
	DirectionalLight::DirectionalLight(const Vector3& L, const Color& c)
		:LightSample(L, c)
	{
		direction = L;
		shadow = true;
	}

	void DirectionalLight::initialize()
	{
		L = direction.Normalize().Negate();
	}

	LightSample DirectionalLight::sample(Union& generations, const Vector3& position)
	{
		if (shadow) {
			Ray3 shadowRay = Ray3(position, L);
			rt::IntersectResult shadowResult = generations.intersect(shadowRay);
			if (shadowResult.is_hit) {
				return zero();
			}
		}
		return LightSample(L,EL);
	}
	Color DirectionalLight::LightRender(Union& generations, IntersectResult& res)
	{
		initialize();
		Color color = Color::black;
		if (res.is_hit) {
			LightSample lightsample = sample(generations, res.position);
			float NdotL = res.normal.Dot(lightsample.L);

			if (NdotL >= 0) {	//夹角小于90度说明光源在物体前方
				color = color.Add(lightsample.EL.Multiply(NdotL));
			}
		}
		
		return Color(color);
	}
	PointLight::PointLight(const Vector3& L, const Color& c)
		:LightSample(Vector3::zero,c)
	{
		position = L;
		shadow = true;
	}

	void PointLight::initialize()
	{}

	LightSample PointLight::sample(Union & generations, const Vector3 & _position)
	{
		Vector3 delta = position.Subtract(_position);
		float rr = delta.SqrtLength();
		float r = Mathf::Sqrt(rr);
		Vector3 l = delta.Divide(r);
		if (shadow) {
			Ray3 shadowRay = Ray3(_position, l);
			IntersectResult shadowResult = generations.intersect(shadowRay);
			if (shadowResult.is_hit && shadowResult.distance <= r) {
				return LightSample::zero();
			}
		}
		float attenuation = 1 / rr;	//平方反比衰减
		return LightSample(l,EL.Multiply(attenuation));
	}

	Color PointLight::LightRender(Union& generations, IntersectResult& res)
	{
		initialize();
		Color color = Color::black;
		if (res.is_hit) {
			LightSample lightsample = sample(generations, res.position);
			float NdotL = res.normal.Dot(lightsample.L);

			if (NdotL >= 0) {	//夹角小于90度说明光源在物体前方
				color = color.Add(lightsample.EL.Multiply(NdotL));
			}
		}

		return Color(color.Multiply(2000));
	}

	SpotLight::SpotLight(const Vector3& _position, const Color& _intensity, const Vector3& _direction, float _theta, float _phi, float _falloff)
	{
		intensity = _intensity;
		position = _position;
		direction = _direction;
		theta = _theta;
		phi = _phi;
		falloff = _falloff;
		shadow = true;
	}

	void SpotLight::initialize()
	{
		L = direction.Normalize().Negate();
	}

	LightSample SpotLight::sample(Union& _generations, const Vector3& _position)
	{
		Vector3 delta = position.Subtract(_position);
		float rr = delta.SqrtLength();
		float r = Mathf::Sqrt(rr);
		Vector3 l = delta.Divide(r);
		
		float cosTheta = Mathf::Cos(theta * Mathf::deg2rad / 2);
		float cosPhi = Mathf::Cos(phi * Mathf::deg2rad / 2);
		float baseMultiplier = 1 / (cosTheta - cosPhi);
		
		float spot;
		float SdotL = L.Dot(l);
		if (SdotL >= cosTheta) {
			spot = 1;
		}
		else if (SdotL <= cosPhi) {
			spot = 0;
		}
		else {
			spot = Mathf::Pow((SdotL - cosPhi) * baseMultiplier, falloff);
		}

		if (shadow) {
			Ray3 shadowRay = Ray3(_position, l);
			IntersectResult shadowResult = _generations.intersect(shadowRay);

			if (shadowResult.is_hit && shadowResult.distance <= r) {
				return LightSample::zero();
			}
		}

		float attenuation = 1 / rr;
		return LightSample(l,intensity.Multiply(attenuation*spot));
	}

	Color SpotLight::LightRender(Union& _generations, IntersectResult& _res)
	{
		initialize();
		Color color = Color::black;
		if (_res.is_hit) {
			LightSample lightsample = sample(_generations, _res.position);
			float NdotL = _res.normal.Dot(lightsample.L);

			if (NdotL >= 0) {	//夹角小于90度说明光源在物体前方
				color = color.Add(lightsample.EL.Multiply(NdotL));
			}

		}

		return Color(color.Multiply(1000));
	}


}


