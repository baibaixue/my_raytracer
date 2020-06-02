#ifndef _RAYTRACER_UNION_H_
#define _RAYTRACER_UNION_H_
#include"ray/IntersectResult.h"
#include"base/mathf.h"
#include"ray/ray.h"
#include"material/Material.h"
namespace rt
{
	class Generation //几何体类
	{
	public:
		Generation()	
		{
			material = NULL;
		};
		virtual IntersectResult intersect(Ray3& _ray)	//初始化继承函数，几何体未与光线相交
		{
			IntersectResult res = IntersectResult::noHit();
			return res;
		};

		virtual void move_location(const Vector3& vec) {};		//变换几何体位置
		virtual void turn_location(const float& pitch, const float& yaw) {};	//几何体绕原点旋转

		Material* material;	//几何体体材料

	};
	 
	struct Union //几何体集合
	{
	public:
		Union()=default;
		Union(std::vector<rt::Generation*> generations);
		std::vector<rt::Generation*> generation;	//几何体数组，存放所有几何体
		IntersectResult intersect(Ray3& _ray);	//光线相交
		Color getcolor(Union generations,Ray3& ray,float maxReflect);	//得到当前光线相交处的像素颜色
		void Add(Generation* _generation);	//添加几何体
		void move_location(const Vector3& vec);
		void turn_location(const float& pitch, const float& yaw);
		//bool delect(Generation& _generation);
	};

}
#endif // !_RAYTRACER_UNION_H_
