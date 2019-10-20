#include "base/header.h"
#include "base/application.h"
#include "base/color.h"
#include "base/mathf.h"
#include "base/ray.h"
#include "base/vector3.h"
#include "base/camer.h"
#include "base/sphere.h"
#include "base/Material.h"
#include "base/Union.h"
#include "base/plane.h"
rt::Application* app;

void MainLoop();
rt::PerspectiveCamera* camera=new rt::PerspectiveCamera(rt::Vector3(0,10,20), rt::Vector3(0, -0.5, -1), rt::Vector3(0, 1, 0), 90);
float lastx = 256, lasty = 256;
float yaw = 0;
float pitch = 0;
bool firstMouse = true;
int main(int argc, char *argv[])
{
	app = rt::Application::GetInstance();
	
	camera->Initialize();//相机初始化
	app->CreateApplication("hello", 512, 512);
	app->RunLoop(MainLoop);
	
	return 0;
}
/*
void MainLoop()
{
	app->Clear(rt::Color32::black);
	
	int w = app->GetWidth();
	int h = app->GetHeight();

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			app->SetPixel(x, y,
				rt::Color(1.f, (float)x / w, (float)y / h, 0.f));
		}
	
	app->submit();
}
	*/
void scrollfun(GLFWwindow* window, double x, double y)
{
	//printf("scroll!");
	//printf("%lf  %lf\n", x, (float)y);
	if (camera->fov>= 10.0f && camera->fov <= 150.0f)
	{
		camera->fov -= (float)y;
	}
	if (camera->fov <= 10.0f)
	{
		camera->fov = 10.0f;
	}
	if (camera->fov >= 150.0f)
	{
		camera->fov = 150.0f;
	}
	camera->Initialize();
	return;
}
void Mouse_callback(GLFWwindow* window,double xpos,double ypos)
{
	if(firstMouse)
	{
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastx;
	float yoffset = ypos - lastx;
	lastx = xpos;
	lasty = ypos;

	printf("xpos:%lf ypos:%lf lastx:%lf lasty:%lf xoffset:%lf yoffset:%lf\n",xpos,ypos,lastx,lasty,xoffset,yoffset);

	float sensitivity = 0.02f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw = xoffset;
	pitch = yoffset;
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f)pitch = -89.0f;

	rt::Vector3 front;
	front.x = rt::Mathf::Cos(rt::Mathf::deg2rad * yaw) * rt::Mathf::Cos(rt::Mathf::deg2rad * pitch);
	front.y = rt::Mathf::Sin(rt::Mathf::deg2rad * pitch);
	front.z = rt::Mathf::Sin(rt::Mathf::deg2rad * yaw) * rt::Mathf::Cos(rt::Mathf::deg2rad * pitch);
	camera->getEye() = front.Add(camera->getEye());
	camera->Initialize();
}
/*
void mouse_callback(GLFWwindow* window, int button, int action,int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT&&action==GLFW_PRESS)
	{
		printf("1\n");
		Mouse_callback(window);
	}
	else {
		printf("0\n");
		return;
	}
}*/


void MainLoop()
{
	//printf("%lf\n", camera->fov);
	//clock_t start, finish;
	//start = clock();
	app->Clear(rt::Color32::black);

	int w = app->GetWidth();
	int h = app->GetHeight();

	long maxDepth = 20;
	rt::Sphere* global1= new rt::Sphere(rt::Vector3(-5, 5, -5), 6.f);
	rt::Plane* plane = new rt:: Plane(rt::Vector3(0, 1, 0), rt::Vector3(0, 0, 0), 1.0);
	rt::Sphere* global2 = new rt::Sphere(rt::Vector3(5, 5, -5),4.f);
	global1->material = new rt::PhongMaterial(rt::Color::red.Add(rt::Color::blue), rt::Color::white, 16.f, 0.25f);
	global2->material = new rt::PhongMaterial(rt::Color::green.Add(rt::Color::blue), rt::Color::white,16.f, 0.25f);
	plane->material = new rt::CheckerMaterial(0.2,0.5f);
	rt::Union generations;
	generations.Add(global1);
	generations.Add(global2);
	generations.Add(plane);
	float dx = 1.f / w;
	float dy = 1.f / h;
	float dD = 255.0f / maxDepth;

	


	for (int y = 0 ; y < h; ++y )
	{
		float sy = 1 - dy * y;
		for (int x = 0 ; x < w ; ++x )
		{
			float sx = dx * x;
			
			rt::Ray3 ray = camera->GenerateRay((float)sx, (float)sy);
			rt::IntersectResult result = generations.intersect(ray);
			//rt::IntersectResult result = plane.intersect(ray);
			rt::Color result_color = generations.getcolor(generations,ray,1.f);
			//rt::Color result_color = generations.objs_color;
			if (result.is_hit)
			{
				/*
				//深度渲染
				double t = rt::Mathf::Min(result.distance * dD, 255.f);
				float depth = (float)(255.f - t);
				//app->SetPixel(x,y,
				//	rt::Color32(1.f, depth, depth, depth));
				app->SetPixel(x, y,
					rt::Color32(1.f, ((result.normal.x + 1)*10+depth), ((result.normal.y + 1)*10+depth) ,((result.normal.z + 1)*10+depth)));
				*/
				
				app->SetPixel(x, y, result_color);
				
			}
			
			/*
			rt::Ray3 ray = camera.GenerateRay((float)sx,(float)sy);//形成光线
 			//printf("%lf %lf\n\n", (float)(x*1.f), (float)(y*1.f));
			rt::IntersectResult result = global.instersect(ray);//交点的位置
			float dis = global.instersect(ray).distance;
			//printf("%lf %lf\n", vec.y,vec.x);
			//printf("%lf %lf\n\n", (float)rt::Mathf::Abs(x) / w, (float)rt::Mathf::Abs(y) / h);
			//printf("%d", vec.is_hit);
			if (result.is_hit)
			{
				//深度渲染
				double t = rt::Mathf::Min(result.distance * dD, 255.f);
				float depth = (float)(255.f - t);
				//app->SetPixel(x,y,
				//	rt::Color32(1.f, depth, depth, depth));
				
				//渲染法向量+渲染深度
				//app->SetPixel(x, y,
				//	rt::Color32(1.f, ((result.normal.x + 1)*10+depth), ((result.normal.y + 1)*10+depth) ,((result.normal.z + 1)*10+depth)));

				//格子材质
				//rt::CheckerMaterial check(7.5f, rt::Vector3(0, 0, 0));
				//app->SetPixel(x, y,
				//	rt::Color32(check.prototype(ray, result.position, result.normal)));
				//Phong材质
				rt::PhongMaterial shine(rt::Color::white, rt::Color::white, 1000.f, rt::Vector3::zero);
				rt::Color _color = rt::Color::Color(1.f, ((result.normal.x + 1) * 10 + depth), ((result.normal.y + 1) * 10 + depth), ((result.normal.z + 1) * 10 + depth));
				app->SetPixel(x, y,
					rt::Color32(shine.prototype(ray, result.position, result.normal).Add(_color)));

			

			}
			*/
			
		}
	}
	//finish = clock();
	//double duration;
	//duration = (double)(finish-start)/ CLOCKS_PER_SEC;
	//printf("%f seconds\n", duration);
	//printf("time:%u\n", clock() / CLOCKS_PER_SEC);
	
	int s = app->getMouse(GLFW_MOUSE_BUTTON_LEFT);
	//printf("%d\n", s);
	//double xpos, ypos;
	//if (s == 1) {
	//	app->getCurPos(&xpos, &ypos);
	//	Mouse_callback(app->Getwindow(), xpos, ypos);
	//}
	//printf("(%lf,%lf)\n", xpos, ypos);
	//glfwSetInputMode(app->Getwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	
	//printf("%lf\n", camera->fov);
	app->Submit();
	glfwSetScrollCallback(app->Getwindow(),scrollfun);
	//glfwSetMouseButtonCallback(app->Getwindow(), mouse_callback);
	
}


