#ifndef _RAYTRACER_MATHF_H_
#define _RAYTRACER_MATHF_H_

#include "header.h"

namespace rt
{

class Mathf //数学类
{
public:
	static const float epsilon;	//无穷小
	static const float inifinity;	//无穷大
	static const float PI;	//Π
	static const float deg2rad;	//角度制转换为弧度制的单位
	static const float rad2deg;	//弧度制转换为角度制的单位

	static float Abs(float f);	//取绝对值
	static float Sign(float f);	//f<0返回负数,f>0返回正数
	static bool Approximately(float a, float b);	//判断a,b是否近似相等

	static float Floor(float f);	//向下取整，返回float类型
	static int FloorToInt(float f);	//向下取整，返回int类型
	static float Ceil(float f);	//向上取整，返回float类型
	static int CeilToInt(float f);	//向上取整，返回int类型
	static float Round(float f);	//四舍五入，返回float类型
	static int RoundToInt(float f);	//四舍五入，返回int类型

	static int Clamp(int value, int min, int max);
		//区间控制函数，判断value是否在min和max之间，
		//不在min和max之间的话，小于min，输出min,大于max，输出max
	static float Clamp(float value, float min, float max); //浮点类型的区间控制函数
	static float Clamp01(float value);	//是否在01之间的区间控制函数

	static float Min(float a, float b);	//最小值
	static float Min(const float* values, int count);	//最小值
	static float Min(const std::vector<float>& values);	//求vector数组的最小值
	static float Max(float a, float b);	//最大值
	static float Max(const float* values, int count);	//最大值
	static float Max(const std::vector<float>& values);	//最大值

	static float Sqrt(float value);	//开方
	static float Pow(float f, float p);	//求指数
	static float Exp(float f);	//返回e的f次幂
	static float Log(float f);	//求对数
	static float Log10(float f);	//求10的对数

	static bool IsPowerOfTwo(int value);	//能否被2开方
	static int NextPowerOfTwo(int value);	//下一个能被2开方的整数

	static float Sin(float f);	//求正弦
	static float Cos(float f);	//求余弦
	static float Tan(float f);	//求正切
	static float Asin(float f);	//求反正弦
	static float Acos(float f);	//反余弦
	static float Atan(float f);	//反正切
	static float Atan2(float y, float x);	//返回y/x的反正切值

};

} // namespace rt

#endif //!_RAYTRACER_MATHF_H_