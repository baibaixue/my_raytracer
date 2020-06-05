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

		static void get_planes_global(Union& _generations);	//��ʼ������ƽ�滥�ഹֱ����

		static void get_plane_PhongGlobals(Union& _generations);	//���Ӳ���ƽ�棬phong��Ⱦ��

		static void get_plane_DeepGlobals(Union& _generations);	//�����Ⱦƽ�棬��
		
		static void get_Spotlights(LightUnion& _lights);	//��ʼ�����ߣ��۹��(��ԭɫ�۹�Ʋ���)

		static void get_Directionlights(LightUnion& _lights);	//��ʼ�����ߣ�ƽ�й�

		static void get_Pointlights(LightUnion& _lights);	//��ʼ�����ߣ����Դ

		static void get_Lights(LightUnion& _lights);	//��ʼ�����ֹ�Դ

		static void get_generations(Union& _generations);

	};
	

	
}


#endif // !INITIALIZE_SCENE_H
