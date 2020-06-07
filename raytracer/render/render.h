#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "geometry/Union.h"
#include "light/LightUnion.h"

namespace rt {
	class Render {
	public:
		static Color getcolor(Union& generations, LightUnion& lights, Ray3& ray, float maxReflect);
	};
}

#endif // !RENDER_H

