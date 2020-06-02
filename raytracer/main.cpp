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
rt::Application* app;

void MainLoop();
rt::PerspectiveCamera* camera=new rt::PerspectiveCamera(rt::Vector3(0,10,20), rt::Vector3(0,-0.5,-1), rt::Vector3(0, 1, 0), 90);
//新建相机

float lastx = 256, lasty = 256;	//鼠标初始位置
float yaw = 0;
float pitch = 0;
bool firstMouse = true;	//是否第一次鼠标按下
rt::Union generations;

void get_generation() {
	rt::Sphere* global1 = new rt::Sphere(rt::Vector3(-5, 5, -5), 6.f);	//新建球1
	rt::Plane* plane = new rt::Plane(rt::Vector3(0, 1, 0), rt::Vector3(1, 1, 1), 1.0);	//新建平面
	rt::Sphere* global2 = new rt::Sphere(rt::Vector3(10, 5, -5),4.f);	//新建球2
	global1->material = new rt::PhongMaterial(rt::Color::red.Add(rt::Color::blue), rt::Color::white, 16.f, 0.25f);	//球1材质渲染
	global2->material = new rt::PhongMaterial(rt::Color::green.Add(rt::Color::red), rt::Color::white,16.f, 0.25f);	//球2材质渲染
	plane->material = new rt::CheckerMaterial(0.2, 0.5f);//平面材质

	generations.Add(global1);	//将几何体加入集合
	generations.Add(global2);
	generations.Add(plane);
}

int main(int argc, char *argv[])
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



void Course_Mouse_callback(GLFWwindow* window,double xpos,double ypos)	//鼠标互动实现镜头360旋转
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
	printf("xpos:%lf ypos:%lf lastx:%lf lasty:%lf xoffset:%lf yoffset:%lf\n",xpos,ypos,lastx,lasty,xoffset,yoffset);
	
	lastx = xpos;
	lasty = ypos;

	//yaw = yoffset;
	//pitch = xoffset;
	//pitch = rt::Mathf::Clamp(pitch, -89.0f, 89.0f);

	/*
	rt::Vector3 front;
	front.x = rt::Mathf::Cos(rt::Mathf::deg2rad * yaw) * rt::Mathf::Cos(rt::Mathf::deg2rad * pitch);
	front.y = rt::Mathf::Sin(rt::Mathf::deg2rad * pitch);
	front.z = rt::Mathf::Sin(rt::Mathf::deg2rad * yaw) * rt::Mathf::Cos(rt::Mathf::deg2rad * pitch);
	camera->getEye() = front.Add(camera->getEye());
	camera->Initialize();
	*/
	/*
	rt::Vector3 front;
	front.x = xoffset;// camera->getEye().x + xoffset;
	front.y = 0;//camera->getEye().y;
	front.z = //camera->getEye().z 
		rt::Mathf::Sqrt(rt::Mathf::Pow(camera->getEye().z, 2.0) -
			xoffset * xoffset - 2 * camera->getEye().x * xoffset)
		 - rt::Mathf::Abs(camera->getEye().z);
	*/
	generations.turn_location(pitch, yaw);
	//generations.move_loaction(front);
	//app->Submit();
	//camera->getEye() = camera->getEye().Add(front);
	//camera->getFront() = camera->getFront().Subtract(front);
	//camera->getUp() = camera->getUp().Add(front);
	//printf("frontx:%lf fronty:%lf frontz:%lf\n", front.x,front.y,front.z);
	//printf("eyex:%lf eyey:%lf eyez:%lf frontx:%lf fronty:%lf frontz:%lf\n",camera->getEye().x, camera->getEye().y,camera->getEye().z,camera->getFront().x, camera->getFront().y, camera->getFront().z );
	//camera->Initialize();

}
void Mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwSetCursorPosCallback(app->Getwindow(), Course_Mouse_callback);
	}
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

void MainLoop()
{
	app->Clear(rt::Color32::black);	//窗口清屏

	int w = app->GetWidth();	//窗口宽
	int h = app->GetHeight();	//窗口高

	long maxDepth = 10;
	
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
		}
		
	}

	app->Submit();
	glfwSetScrollCallback(app->Getwindow(),scrollfun);	//回调函数实现鼠标滚轮互动
	glfwSetKeyCallback(app->Getwindow(), key_callback);	//回调函数实现
	double xpos, ypos;
	if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		printf("1");
		app->getCurPos(&xpos, &ypos);
		Course_Mouse_callback(app->Getwindow(), xpos, ypos);
	}
	else if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		lastx = 256, lasty = 256;
		firstMouse = true;
	}
	
	//glfwSetMouseButtonCallback(app->Getwindow(), Mouse_callback);
	//glfwSetCursorPosCallback(app->Getwindow(), Mouse_callback);

	
}


