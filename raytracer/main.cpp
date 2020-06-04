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
#include "light/light.h"

rt::Application* app;

void MainLoop();
rt::PerspectiveCamera* camera = 
						new rt::PerspectiveCamera
						(rt::Vector3(0,10,20), rt::Vector3(0,-0.5,-1), rt::Vector3(0, 1, 0), 90);
//新建相机

float lastx = 256, lasty = 256;	//鼠标初始位置
bool firstMouse = true;	//是否第一次鼠标按下
rt::Union generations;
rt::DirectionalLight light1(rt::Vector3(20, -20, 20), rt::Color::blue);	//光源：平行光
rt::PointLight light2(rt::Vector3(0, 10, 0), rt::Color::red);	//光源：点光源
void get_generation() {	//初始化几何体
	rt::Sphere* global1 = new rt::Sphere(rt::Vector3(-5, 7, -5), 6.f);	//新建球1
	rt::Plane* plane = new rt::Plane(rt::Vector3(0, 1, 0), rt::Vector3(1, 1, 1), 1.0);	//新建平面
	rt::Sphere* global2 = new rt::Sphere(rt::Vector3(10, 5, -5),4.f);	//新建球2
	global1->material = new rt::PhongMaterial(rt::Color::red.Add(rt::Color::blue), rt::Color::white, 16.f, 0.25f);	//球1材质渲染
	global2->material = new rt::PhongMaterial(rt::Color::green.Add(rt::Color::red), rt::Color::white,16.f, 0.25f);	//球2材质渲染
	plane->material = new rt::CheckerMaterial(0.2, 0.5f);//平面格子材质
	//global1->material = new rt::ColorMaterial(rt::Color::red,0.25f);
	//global2->material = new rt::ColorMaterial(rt::Color::blue, 0.25f);
	//plane->material = new rt::ColorMaterial(rt::Color::white, 0.25f);

	generations.Add(global1);	//将几何体加入集合
	generations.Add(global2);
	generations.Add(plane);
}

int main(int argc, char *argv[])	//主函数
{
	app = rt::Application::GetInstance();
	
	camera->Initialize();//相机初始化
	app->CreateApplication("raytracer",450, 450);	//窗口标题及分辨率
	get_generation();
	app->RunLoop(MainLoop);
	
	return 0;
}
void scrollfun(GLFWwindow* window, double x, double y)	//滚轮实现拉近拉远
{
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



void Course_Mouse_callback(GLFWwindow* window,double xpos,double ypos)	//鼠标互动实现物体旋转
{
	if(firstMouse)	//初始化鼠标首次按下时的坐标
	{
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}
	
	float xoffset = lastx - xpos;	//水平方向位置变化
	float yoffset = ypos - lasty;	//竖直方向位置变化
	
	float xsensitivity = 0.3f;	//移动敏感度
	float ysensitivity = 0.1f;
	xoffset *= xsensitivity;
	yoffset *= ysensitivity;

	float pitch = rt::Mathf::Clamp(xoffset, -179.0f, 179.0f);
	float yaw = rt::Mathf::Clamp(yoffset, -179.0f, 179.0f);
	//printf("xpos:%lf ypos:%lf lastx:%lf lasty:%lf xoffset:%lf yoffset:%lf\n",xpos,ypos,lastx,lasty,xoffset,yoffset);
	
	lastx = xpos;
	lasty = ypos;

	generations.turn_location(pitch, yaw);

}
/*
void Mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwSetCursorPosCallback(app->Getwindow(), Course_Mouse_callback);
	}
}
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {	//方向键实现相机移动
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
		camera->getEye() = (camera->getEye()).Add(rt::Vector3::up);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
		camera->getEye() = (camera->getEye()).Add(rt::Vector3::down);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {

		camera->getEye() = (camera->getEye()).Add(rt::Vector3::left);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
		camera->getEye() = (camera->getEye()).Add(rt::Vector3::right);
	}
	camera->Initialize();
}

void MainLoop()	//循环主体
{
	app->Clear(rt::Color32::black);	//窗口清屏

	int w = app->GetWidth();	//窗口宽
	int h = app->GetHeight();	//窗口高

	long maxDepth = 30;
	
	float dx = 1.f / w;
	float dy = 1.f / h;
	float dD = 255.0f / maxDepth;

	
	for (int y = 0 ; y < h; ++y )	//光栅扫描填充窗口
	{
		float sy = 1 - dy * y;
		for (int x = 0 ; x < w ; ++x )
		{
			float sx = dx * x;
			
			rt::Ray3 ray = camera->GenerateRay((float)sx, (float)sy);
			rt::IntersectResult result = generations.intersect(ray);
			rt::Color result_color = generations.getcolor(generations,ray,1.f);
			
			if (result.is_hit)
			{
			
				result_color = result_color.Add(light2.LightRender(generations, result));
				app->SetPixel(x, y, result_color);
				
			}	
		}
		
	}
	app->Submit();
	glfwSetScrollCallback(app->Getwindow(),scrollfun);	//回调函数实现鼠标滚轮互动
	glfwSetKeyCallback(app->Getwindow(), key_callback);	//回调函数实现方向键控制相机移动
	double xpos, ypos;	//鼠标拖拽实现物体旋转
	if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//printf("1");
		app->getCurPos(&xpos, &ypos);
		Course_Mouse_callback(app->Getwindow(), xpos, ypos);
	}
	else if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		lastx = 256, lasty = 256;
		firstMouse = true;
	}
	
	
}


