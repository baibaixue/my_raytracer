#include "initialize_scene.h"
#include "render/render.h"
rt::Application* app;

void MainLoop();
void scrollfun(GLFWwindow* window, double x, double y);	//鼠标滚轮实现拉近拉远
void Course_Mouse_callback(GLFWwindow* window, double xpos, double ypos);	//鼠标互动实现物体旋转
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);	//方向键实现镜头移动

//新建相机
rt::PerspectiveCamera* camera =
		new rt::PerspectiveCamera
		(rt::Vector3(0, 10, 10), rt::Vector3(0, 0, -1), rt::Vector3(0, 1, 0), 90);

rt::Union generations;
rt::LightUnion lights;

float lastx = 256, lasty = 256;	//鼠标初始位置
bool firstMouse = true;	//是否第一次鼠标按下

int main(int argc, char *argv[])	//主函数
{
	app = rt::Application::GetInstance();
	
	camera->Initialize();//相机初始化
	app->CreateApplication("raytracer",450, 450);	//窗口标题及分辨率
	rt::Init::get_planes_global(generations);
	rt::Init::get_Spotlights(lights);
	app->RunLoop(MainLoop);
	
	return 0;
}


void MainLoop()	//循环主体
{
	app->Clear(rt::Color32::black);	//窗口清屏

	int w = app->GetWidth();	//窗口宽
	int h = app->GetHeight();	//窗口高

	float dx = 1.f / w;
	float dy = 1.f / h;

	for (float y = 0.f; y < h; y+=1.f)	//光栅扫描填充窗口
	{
		float sy = 1 - dy * y;
		for (float x = 0.f; x < w; x+=1.f)
		{
			float sx = dx * x;
			
			rt::Ray3 ray = camera->GenerateRay(sx, sy);
			rt::IntersectResult result = generations.intersect(ray);
			rt::Color result_color = rt::Color::black;
			result_color = result_color.Add(rt::Render::getcolor(generations,lights, ray,3.f));

			if (result.is_hit)
			{
				
				app->SetPixel(x, y, result_color);

			}
		}

	}
	
	app->Submit();
	glfwSetScrollCallback(app->Getwindow(), scrollfun);	//回调函数实现鼠标滚轮互动
	glfwSetKeyCallback(app->Getwindow(), key_callback);	//回调函数实现方向键控制相机移动
	double xpos, ypos;	//鼠标拖拽实现物体旋转
	if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		app->getCurPos(&xpos, &ypos);
		Course_Mouse_callback(app->Getwindow(), xpos, ypos);
	}
	else if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		lastx = 256, lasty = 256;
		firstMouse = true;
	}


}

void scrollfun(GLFWwindow* window, double x, double y)	//滚轮实现拉近拉远
{
	camera->getEye().z += (camera->getFront().z*y);
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
	float ysensitivity = 0.3f;
	xoffset *= xsensitivity;
	yoffset *= ysensitivity;

	float pitch = rt::Mathf::Clamp(xoffset, -179.0f, 179.0f);
	float yaw = rt::Mathf::Clamp(yoffset, -179.0f, 179.0f);
	lastx = xpos;
	lasty = ypos;

	generations.turn_location(pitch, yaw);
}
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



