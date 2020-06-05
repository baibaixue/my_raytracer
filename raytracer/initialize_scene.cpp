#include"initialize_scene.h"

namespace rt {
	
	void Init::get_planes_global(Union& _generations) {	//初始化三个平面互相垂直，球
		rt::Sphere* global = new rt::Sphere(rt::Vector3(0, 10, -10), 10);
		rt::Plane* plane1 = new rt::Plane(rt::Vector3(0, 1, 0), rt::Vector3(0, 0, 0), 0);
		rt::Plane* plane2 = new rt::Plane(rt::Vector3(0, 0, 1), rt::Vector3(0, 0, -50), -50);
		rt::Plane* plane3 = new rt::Plane(rt::Vector3(1, 0, 0), rt::Vector3(-20, 0, 0), -20);
		_generations.Add(global);
		_generations.Add(plane1);
		_generations.Add(plane2);
		_generations.Add(plane3);

	}
	void Init::get_plane_PhongGlobals(Union& _generations) {	//格子材质平面，phong渲染球
		Sphere* global1 = new Sphere(Vector3(-5, 7, -5), 6.f);	//新建球1
		Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(1, 1, 1), 1.0);	//新建平面
		Sphere* global2 = new Sphere(Vector3(10, 5, -5),4.f);	//新建球2
		global1->material = new PhongMaterial(Color::red.Add(Color::blue), Color::white, 16.f, 0.25f);	//球1材质渲染
		global2->material = new PhongMaterial(Color::green.Add(Color::red), Color::white,16.f, 0.25f);	//球2材质渲染
		plane->material = new CheckerMaterial(0.2f, 0.5f);//平面格子材质

		_generations.Add(global1);	//将几何体加入集合
		_generations.Add(global2);
		_generations.Add(plane);
	}
	void Init::get_plane_DeepGlobals(Union& _generations)
	{
		rt::Sphere* global1 = new Sphere(Vector3(-5, 7, -5), 6.f);	//新建球1
		rt::Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(1, 1, 1), 1.0);	//新建平面
		rt::Sphere* global2 = new Sphere(Vector3(10, 5, -5), 4.f);	//新建球2
		global1->material = new ColorMaterial(Color::red,0.25f);
		global2->material = new ColorMaterial(Color::blue, 0.25f);
		plane->material = new ColorMaterial(Color::white, 0.25f);

		_generations.Add(global1);	//将几何体加入集合
		_generations.Add(global2);
		_generations.Add(plane);
	}
	void Init::get_Spotlights(LightUnion& _lights)
	{
		LightSample* light = new PointLight
		(Vector3(30,40,20),Color::white);
		LightSample* light1 = new SpotLight
		(Vector3(0, 30, 10), Color::red, Vector3(0, -1, -1), 20, 30, 1);
		LightSample* light2 = new SpotLight
		(Vector3(6, 30, 20), Color::blue, Vector3(0, -1, -1), 20, 30, 1);
		LightSample* light3 = new SpotLight
		(Vector3(-6, 30, 20), Color::green, Vector3(0, -1, -1), 20, 30, 1);

		_lights.Add(light);
		_lights.Add(light1);
		_lights.Add(light2);
		_lights.Add(light3);
	}
	void Init::get_Directionlights(LightUnion& _lights)
	{
		LightSample* light = new DirectionalLight
		(Vector3(-30,-40,-20),Color::white);
		
		_lights.Add(light);
	}
	void Init::get_Pointlights(LightUnion& _lights)
	{
		LightSample* light = new PointLight
		(Vector3(30, 40, 20), Color::white);
		
		_lights.Add(light);

	}
	void Init::get_Lights(LightUnion& _lights)
	{
		for (float x = 10.f; x <= 30.f; x += 5.f) {
			for (float z = 20.f; z <= 40.f; z += 5.f) {
				_lights.Add(new PointLight(Vector3(x, 50.f, z), Color::white.Multiply(0.1f)));
			}
		}

		LightSample* fillLight = new DirectionalLight(Vector3(1.5, 1, 0.5), Color::blue.Multiply(0.25));
		
		_lights.Add(fillLight);
	}
	void Init::get_generations(Union& _generations)
	{
		Generation* triangle = new Triangle(Vector3(0, 0, 0), Vector3(30, 0, 0), Vector3(0, 40, 0));
		triangle->material = new rt::PhongMaterial(Color::red.Add(rt::Color::blue), Color::white, 16.f, 0.25f);
		//triangle->material = new rt::ColorMaterial(Color::blue, 0.25f);
		_generations.Add(triangle);
	}
}

