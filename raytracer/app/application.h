#ifndef _RAYTRACER_APPLICATION_H_
#define _RAYTRACER_APPLICATION_H_


#include "base/header.h"
#include "base/color.h"
#include "camer/camer.h"

namespace rt
{

class Application
{
	Application();

public:
	static Application* GetInstance();
	typedef void(*LoopFunc)();
	bool CreateApplication(const char* title, int width, int height);//����Ӧ�ô���
	int GetWidth() const { return width; }//Ӧ�ô��ڿ�
	int GetHeight() const { return height; }//���ڸ�

	void RunLoop(LoopFunc loopFunc);//��������

	void Clear(Color32 color);//��մ�����ɫ
	void Submit();//����
	bool SetPixel(int x, int y, const Color32& color);//������Ϊ��x,y���ĵ����ص���Ϊcolor
	bool SetPixel(int x, int y, const Color& color);
	int getMouse(int bottom);
	void getCurPos(double* xpos, double* ypos);
	GLFWwindow* Getwindow();
private:
    GLFWwindow* window;

	std::vector<u32> pixels;

	int width;
	int height;
};

}

#endif // !_RAYTRACER_APPLICATION_H_
