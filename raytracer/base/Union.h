#ifndef _RAYTRACER_UNION_H_
#define _RAYTRACER_UNION_H_
#include"base/IntersectResult.h"
#include"base/mathf.h"
#include"base/ray.h"
#include"base/Material.h"
namespace rt
{
	class Generation
	{
	public:
		Generation()
		{
			material = NULL;
		};
		virtual IntersectResult intersect(Ray3& _ray)
		{
			IntersectResult res = IntersectResult::noHit();
			return res;
		};
		Material* material;

		~Generation();
	};
	 
	struct Union
	{
	public:
		Union()=default;
		Union(std::vector<rt::Generation*> generations);
		std::vector<rt::Generation*> generation;
		IntersectResult intersect(Ray3& _ray);
		Color getcolor(Union generations,Ray3& ray,float maxReflect);
		Color objs_color;
		void Add(Generation* _generation);
		//bool delect(Generation& _generation);
	};

}
#endif // !_RAYTRACER_UNION_H_
