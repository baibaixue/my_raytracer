#ifndef _RAYTRACER_INTERSECTRESULT_H_
#define _RAYTRACER_INTERSECTRESULT_H_
#include"base/vector3.h"
#include"base/header.h"
#include"material\Material.h"
namespace rt
{
	class IntersectResult	//光线和物体相交的类
	{
	public:
		/*
		bool is_hit = false;
		float distance = 0.f;//物体与光线交点的距离
		Vector3 position = Vector3::zero;//位置
		Vector3 normal = Vector3::zero;//法向量
		*/
		
		bool is_hit;	//是否接触
		Material* material;	//材质
		float distance;	//距离
		Vector3 position;	//位置
		Vector3 normal;		//法向量


		IntersectResult() = default;
		IntersectResult(bool _hit, float _d, const Vector3& _vp, const Vector3& _vn,Material* _material)
			:is_hit(_hit)
			, distance(_d)
			, position(_vp)
			, normal(_vn)
			,material(_material)
		{
		}
		static  IntersectResult noHit() { return IntersectResult(false, 0.f, Vector3::zero, Vector3::zero, NULL); };	//没有和几何体相交
	};
}
#endif // !_RAYTRACER_INTERSECTRESULT_H_
