#include"base/Union.h"

namespace rt
{
	Union::Union(std::vector<rt::Generation*> generations)
	{
		generation = generations;
	}

	IntersectResult Union::intersect(Ray3& _ray) 
	{
		float minDistance = Mathf::inifinity;	//最短距离无穷大
		IntersectResult minresult = IntersectResult::noHit();	//初始化光线未接触几何体
		for (int i = 0; i < generation.size(); i++)	
		{
			IntersectResult result = generation[i]->intersect(_ray);
			
			if (result.is_hit && result.distance < minDistance)	//从所有几何体中找到和光线相交并距离最近的几何体
			{
				minDistance = result.distance;	//更新距离
				minresult = result;	//更新光线相交情况
				//objs_color = generation[i]->material->prototype(_ray, result.position, result.normal);	//更新材质
			}
		}
		return minresult;
	}
	void Union::Add(Generation* _generation)
	{
		generation.push_back(_generation);
	}

	Color Union::getcolor(Union generation,Ray3& ray, float maxReflect)	//光线相交几何体颜色,maxReflect:最大反射次数
	{
		IntersectResult result = generation.intersect(ray);
		if (result.is_hit)
		{
			float reflectiveness = result.material->reflectiveness;	//反射度
			//printf("%lf\n", reflectiveness);
			rt::Color color = result.material->prototype(ray, result.position, result.normal);	//材质反射情况
			color = color.Multiply(1.f- reflectiveness);	//光线衰减

			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.Mulitiply(-2 * result.normal.Dot(ray.direction)).Add(ray.direction);	//反射光线
				//Ray3 _ray = Ray3(result.position, r);
				ray =Ray3(result.position, r);
				Color reflectedColor = getcolor(generation, ray, maxReflect - 1);	//递归调用
				color = color.Add(reflectedColor.Multiply(reflectiveness));	//反射情况叠加
			}
			return color;

		}
		else return Color::black;

	}

}