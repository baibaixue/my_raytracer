#include "LightUnion.h"


namespace rt {
	rt::LightUnion::LightUnion(std::vector<rt::LightSample*> _lights)
	{
		lights = _lights;
	}

	Color LightUnion::LightRender(Union& _generations, IntersectResult& _res)
	{
		Color lightcolor = Color::black.Add(Color(0.f,0.1f,0.1f,0.1f));
		for (int i = 0; i < lights.size(); i++) {
			lightcolor = lightcolor.Add(lights[i]->LightRender(_generations, _res));
		}
		return Color(lightcolor);
	}
	void LightUnion::Add(LightSample* _light)
	{
		lights.push_back(_light);
	}
}





