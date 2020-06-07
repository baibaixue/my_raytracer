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
		float minDistance = Mathf::inifinity;	//��̾��������
		IntersectResult minresult = IntersectResult::noHit();	//��ʼ������δ�Ӵ�������
		for (int i = 0; i < generation.size(); i++)	
		{
			
			IntersectResult result = generation[i]->intersect(_ray);
			
			if (result.is_hit && result.distance < minDistance)	//�����м��������ҵ��͹����ཻ����������ļ�����
			{
				minDistance = result.distance;	//���¾���
				minresult = result;	//���¹����ཻ���
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