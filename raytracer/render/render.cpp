#include "render.h"

namespace rt {
	Color rt::Render::getcolor(Union& _generations, LightUnion& _lights, Ray3& _ray, float _maxReflect)
	{
		IntersectResult result = _generations.intersect(_ray);
		if (result.is_hit)
		{
			float reflectiveness = result.material->reflectiveness;	//反射度
			//printf("%lf\n", reflectiveness);
			Color color = rt::Color::black;
			Color material_color = result.material->prototype(_ray, result.position, result.normal);	//材质反射情况
			material_color = material_color.Multiply(1.f - reflectiveness);	//光线衰减
			Color light_color = _lights.LightRender(_generations, result);
			color = color.Add(material_color);
			color = color.Add(light_color);

			if (reflectiveness > 0 && _maxReflect > 0)
			{
				Vector3 r = result.normal.Mulitiply(-2 * result.normal.Dot(_ray.direction)).Add(_ray.direction);	//反射光线
				//Ray3 _ray = Ray3(result.position, r);
				Ray3 ray = Ray3(result.position, r);
				Color reflectedColor = getcolor(_generations,_lights, ray, _maxReflect - 1);	//递归调用
				color = color.Add(reflectedColor.Multiply(reflectiveness));	//反射情况叠加
			}


			//printf("r:%lf g:%lf b:%lf\n", color.r, color.g, color.b);
			return color;

		}
		else return Color::black;

	}
}

