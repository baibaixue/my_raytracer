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
	bool CreateApplication(const char* title, int width, int height);//创建应用窗口
	int GetWidth() const { return width; }//应用窗口宽
	int GetHeight() const { return height; }//窗口高

	void RunLoop(LoopFunc loopFunc);//窗口运行

	void Clear(Color32 color);//清空窗口颜色
	void Submit();//运行
	bool SetPixel(int x, int y, const Color32& color);//将坐标为（x,y）的点像素调整为color
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
