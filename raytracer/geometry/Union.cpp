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

	Color Union::getcolor(Union generation,Ray3& ray, float maxReflect)	//�����ཻ��������ɫ,maxReflect:��������
	{
		IntersectResult result = generation.intersect(ray);
		if (result.is_hit)
		{
			float reflectiveness = result.material->reflectiveness;	//�����
			//printf("%lf\n", reflectiveness);
			rt::Color color = rt::Color::black;
			rt::Color material_color = result.material->prototype(ray, result.position, result.normal);	//���ʷ������
			material_color = material_color.Multiply(1.f- reflectiveness);	//����˥��
			
			if (reflectiveness > 0 && maxReflect > 0)
			{
				Vector3 r = result.normal.Mulitiply(-2 * result.normal.Dot(ray.direction)).Add(ray.direction);	//�������
				//Ray3 _ray = Ray3(result.position, r);
				ray =Ray3(result.position, r);
				Color reflectedColor = getcolor(generation, ray, maxReflect - 1);	//�ݹ����
				material_color = material_color.Add(reflectedColor.Multiply(reflectiveness));	//�����������
			}
			
			color = color.Add(material_color);
			//printf("r:%lf g:%lf b:%lf\n", color.r, color.g, color.b);
			return color;

		}
		else return Color::black;

	}

}