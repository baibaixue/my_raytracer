#pragma once
#ifndef LIGHTUNION_H
#define LIGHTUNION_H
#include"light.h"

namespace rt {

	struct LightUnion {
		LightUnion() = default;
		LightUnion(std::vector<rt::LightSample*> _lights);
		std::vector<rt::LightSample*> lights;	//光源数组，存放所有光源
		Color LightRender(Union& generations, IntersectResult& res);	//光渲染
		void Add(LightSample* _light);	//添加光源

	};
}

#endif // !LIGHTUNION_H
