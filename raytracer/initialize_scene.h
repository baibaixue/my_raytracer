#pragma once
#ifndef INITIALIZE_SCENE_H
#define INITIALIZE_SCENE_H
#include "base/header.h"
#include "app/application.h"
#include "base/color.h"
#include "base/mathf.h"
#include "ray/ray.h"
#include "base/vector3.h"
#include "camer/camer.h"
#include "geometry/sphere.h"
#include "material/Material.h"
#include "geometry/Union.h"
#include "geometry/plane.h"
#include "geometry/triangle.h"
#include "light/light.h"
#include "light/LightUnion.h"

namespace rt 
{
	struct Init {

		static void get_planes_global(Union& _generations);	//初始化三个平面互相垂直，球

		static void get_plane_PhongGlobals(Union& _generations);	//格子材质平面，phong渲染球

		static void get_plane_DeepGlobals(Union& _generations);	//深度渲染平面，球
		
		static void get_Spotlights(LightUnion& _lights);	//初始化光线：聚光灯(三原色聚光灯测试)

		static void get_Directionlights(LightUnion& _lights);	//初始化光线：平行光

		static void get_Pointlights(LightUnion& _lights);	//初始化光线：点光源

		static void get_Lights(LightUnion& _lights);	//初始化多种光源

		static void get_generations(Union& _generations);

	};
	

	
}


#endif // !INITIALIZE_SCENE_H
