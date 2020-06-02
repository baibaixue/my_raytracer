#ifndef _RAYTRACER_UNION_H_
#define _RAYTRACER_UNION_H_
#include"ray/IntersectResult.h"
#include"base/mathf.h"
#include"ray/ray.h"
#include"material/Material.h"
namespace rt
{
	class Generation //��������
	{
	public:
		Generation()	
		{
			material = NULL;
		};
		virtual IntersectResult intersect(Ray3& _ray)	//��ʼ���̳к�����������δ������ཻ
		{
			IntersectResult res = IntersectResult::noHit();
			return res;
		};

		virtual void move_location(const Vector3& vec) {};		//�任������λ��
		virtual void turn_location(const float& pitch, const float& yaw) {};	//��������ԭ����ת

		Material* material;	//�����������

	};
	 
	struct Union //�����弯��
	{
	public:
		Union()=default;
		Union(std::vector<rt::Generation*> generations);
		std::vector<rt::Generation*> generation;	//���������飬������м�����
		IntersectResult intersect(Ray3& _ray);	//�����ཻ
		Color getcolor(Union generations,Ray3& ray,float maxReflect);	//�õ���ǰ�����ཻ����������ɫ
		void Add(Generation* _generation);	//��Ӽ�����
		void move_location(const Vector3& vec);
		void turn_location(const float& pitch, const float& yaw);
		//bool delect(Generation& _generation);
	};

}
#endif // !_RAYTRACER_UNION_H_
