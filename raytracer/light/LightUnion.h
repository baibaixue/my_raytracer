#pragma once
#ifndef LIGHTUNION_H
#define LIGHTUNION_H
#include"light.h"

namespace rt {

	struct LightUnion {
		LightUnion() = default;
		LightUnion(std::vector<rt::LightSample*> _lights);
		std::vector<rt::LightSample*> lights;	//��Դ���飬������й�Դ
		Color LightRender(Union& generations, IntersectResult& res);	//����Ⱦ
		void Add(LightSample* _light);	//��ӹ�Դ

	};
}

#endif // !LIGHTUNION_H
