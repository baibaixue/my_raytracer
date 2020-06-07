#include "initialize_scene.h"
#include "render/render.h"
rt::Application* app;

void MainLoop();
void scrollfun(GLFWwindow* window, double x, double y);	//������ʵ��������Զ
void Course_Mouse_callback(GLFWwindow* window, double xpos, double ypos);	//��껥��ʵ��������ת
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);	//�����ʵ�־�ͷ�ƶ�

//�½����
rt::PerspectiveCamera* camera =
		new rt::PerspectiveCamera
		(rt::Vector3(0, 10, 10), rt::Vector3(0, 0, -1), rt::Vector3(0, 1, 0), 90);

rt::Union generations;
rt::LightUnion lights;

float lastx = 256, lasty = 256;	//����ʼλ��
bool firstMouse = true;	//�Ƿ��һ����갴��

int main(int argc, char *argv[])	//������
{
	app = rt::Application::GetInstance();
	
	camera->Initialize();//�����ʼ��
	app->CreateApplication("raytracer",450, 450);	//���ڱ��⼰�ֱ���
	rt::Init::get_planes_global(generations);
	rt::Init::get_Spotlights(lights);
	app->RunLoop(MainLoop);
	
	return 0;
}


void MainLoop()	//ѭ������
{
	app->Clear(rt::Color32::black);	//��������

	int w = app->GetWidth();	//���ڿ�
	int h = app->GetHeight();	//���ڸ�

	float dx = 1.f / w;
	float dy = 1.f / h;

	for (float y = 0.f; y < h; y+=1.f)	//��դɨ����䴰��
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
	glfwSetScrollCallback(app->Getwindow(), scrollfun);	//�ص�����ʵ�������ֻ���
	glfwSetKeyCallback(app->Getwindow(), key_callback);	//�ص�����ʵ�ַ������������ƶ�
	double xpos, ypos;	//�����קʵ��������ת
	if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		app->getCurPos(&xpos, &ypos);
		Course_Mouse_callback(app->Getwindow(), xpos, ypos);
	}
	else if (app->getMouse(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		lastx = 256, lasty = 256;
		firstMouse = true;
	}


}

void scrollfun(GLFWwindow* window, double x, double y)	//����ʵ��������Զ
{
	camera->getEye().z += (camera->getFront().z*y);
	camera->Initialize();
	return;
}

void Course_Mouse_callback(GLFWwindow* window,double xpos,double ypos)	//��껥��ʵ��������ת
{
	if(firstMouse)	//��ʼ������״ΰ���ʱ������
	{
		lastx = xpos;
		lasty = ypos;
		firstMouse = false;
	}
	
	float xoffset = lastx - xpos;	//ˮƽ����λ�ñ仯
	float yoffset = ypos - lasty;	//��ֱ����λ�ñ仯
	
	float xsensitivity = 0.3f;	//�ƶ����ж�
	float ysensitivity = 0.3f;
	xoffset *= xsensitivity;
	yoffset *= ysensitivity;

	float pitch = rt::Mathf::Clamp(xoffset, -179.0f, 179.0f);
	float yaw = rt::Mathf::Clamp(yoffset, -179.0f, 179.0f);
	lastx = xpos;
	lasty = ypos;

	generations.turn_location(pitch, yaw);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {	//�����ʵ������ƶ�
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



