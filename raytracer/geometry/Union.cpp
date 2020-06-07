#include"geometry/Union.h"


namespace rt
{
	Union::Union(std::vector<rt::Generation*> generations)
	{
		generation = generations;
	}

	IntersectResult Union::intersect(Ray3& _ray) 
	{
		//printf("x:%lf y:%lf z:%lf\n", _ray.origin.x, _ray.origin.y, _ray.origin.z);
		float minDistance = Mathf::inifinity;	//最短距离无穷大
		IntersectResult minresult = IntersectResult::noHit();	//初始化光线未接触几何体
		for (int i = 0; i < generation.size(); i++)	
		{
			
			IntersectResult result = generation[i]->intersect(_ray);
			
			if (result.is_hit && result.distance < minDistance)	//从所有几何体中找到和光线相交并距离最近的几何体
			{
				minDistance = result.distance;	//更新距离
				minresult = result;	//更新光线相交情况
			}
		}
		
		return minresult;
	}
	void Union::Add(Generation* _generation)
	{
		generation.push_back(_generation);
	}

	void Union::move_location(const Vector3& vec)
	{
		for (unsigned int i = 0; i < generation.size(); i++) {
			generation[i]->move_location(vec);
		}
		return;
	}

	void Union::turn_location(const float& xoffset, const float& yoffset)
	{
		for (unsigned int i = 0; i < generation.size(); i++) {
			generation[i]->turn_location(xoffset,yoffset);
		}
		return;
	}


}