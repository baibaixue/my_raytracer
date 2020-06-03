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
			//printf("is_hit:%d\n",shadowResult.is_hit);
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
			//printf("x:%lf y:%lf z:%lf\n", res.normal.x, res.normal.y, res.normal.z);
			//printf("x:%lf y:%lf z:%lf\n", lightsample.L.x, lightsample.L.y, lightsample.L.z);
			//printf("NdotL:%lf\n", NdotL);
			if (NdotL >= 0) {	//夹角小于90度说明光源在物体前方
				color = color.Add(lightsample.EL.Multiply(NdotL));
			}
			//printf("r:%lf g:%lf b:%lf\n", color.r, color.g, color.b);
		}
		
		return Color(color);
	}
}


