#include"base/Union.h"

namespace rt
{
	Union::Union(std::vector<rt::Generation*> generations)
	{
		generation = generations;
	}

	IntersectResult Union::intersect(Ray3& _ray) 
	{
		float minDistance = Mathf::inifinity;
		IntersectResult minresult = IntersectResult::noHit();
		for (int i = 0; i < generation.size(); i++)
		{
			IntersectResult result = generation[i]->intersect(_ray);
			
			if (result.is_hit && result.distance < minDistance)
			{
				minDistance = result.distance;
				minresult = result;
				objs_color = generation[i]->material->prototype(_ray, result.position, result.normal);
			}
		}
		return minresult;
	}
	void Union::Add(Generation* _generation)
	{
		generation.push_back(_generation);
	}

	Color Union::getcolor(Union generation,Ray3& ray, float maxReflect)
	{
		IntersectResult result = generation.intersect(ray);
		if (result.is_hit)
		{
			float reflectiveness = result.material->reflectiveness;
			//printf("%lf\n", reflectiveness);
			rt::Color color = result.material->prototype(ray, result.position, result.normal);
			color = color.Multiply(1.f- reflectiveness);

			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.Mulitiply(-2 * result.normal.Dot(ray.direction)).Add(ray.direction);
				//Ray3 _ray = Ray3(result.position, r);
				ray =Ray3(result.position, r);
				Color reflectedColor = getcolor(generation, ray, maxReflect - 1);
				color = color.Add(reflectedColor.Multiply(reflectiveness));
			}
			return color;

		}
		else return Color::black;

	}

	Generation::~Generation() {};
}