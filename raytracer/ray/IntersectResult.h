#ifndef _RAYTRACER_INTERSECTRESULT_H_
#define _RAYTRACER_INTERSECTRESULT_H_
#include"base/vector3.h"
#include"base/header.h"
#include"material\Material.h"
namespace rt
{
	class IntersectResult	//���ߺ������ཻ����
	{
	public:
		/*
		bool is_hit = false;
		float distance = 0.f;//��������߽���ľ���
		Vector3 position = Vector3::zero;//λ��
		Vector3 normal = Vector3::zero;//������
		*/
		
		bool is_hit;	//�Ƿ�Ӵ�
		Material* material;	//����
		float distance;	//����
		Vector3 position;	//λ��
		Vector3 normal;		//������


		IntersectResult() = default;
		IntersectResult(bool _hit, float _d, const Vector3& _vp, const Vector3& _vn,Material* _material)
			:is_hit(_hit)
			, distance(_d)
			, position(_vp)
			, normal(_vn)
			,material(_material)
		{
		}
		static  IntersectResult noHit() { return IntersectResult(false, 0.f, Vector3::zero, Vector3::zero, NULL); };	//û�кͼ������ཻ
	};
}
#endif // !_RAYTRACER_INTERSECTRESULT_H_
