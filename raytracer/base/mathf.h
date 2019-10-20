#ifndef _RAYTRACER_MATHF_H_
#define _RAYTRACER_MATHF_H_

#include "header.h"

namespace rt
{

class Mathf
{
public:
	static const float epsilon;//无穷小
	static const float inifinity;//无穷大
	static const float PI;//Π
	static const float deg2rad;//角度制转换为弧度制的单位
	static const float rad2deg;//弧度制转换为角度制的单位

	static float Abs(float f);//取绝对值
	static float Sign(float f);//f<0返回负数,f>0返回正数
	static bool Approximately(float a, float b);//判断a,b是否近似相等

	static float Floor(float f);//向下取整，返回float类型
	static int FloorToInt(float f);//向下取整，返回int类型
	static float Ceil(float f);//向上取整，返回float类型
	static int CeilToInt(float f);//向上取整，返回int类型
	static float Round(float f);//四舍五入，返回float类型
	static int RoundToInt(float f);//四舍五入，返回int类型

	static int Clamp(int value, int min, int max);
	//判断value是否在min和max之间，
	//如果是返回value，否则返回min
	static float Clamp(float value, float min, float max);
	static float Clamp01(float value);

	static float Min(float a, float b);
	static float Min(const float* values, int count);
	static float Min(const std::vector<float>& values);
	static float Max(float a, float b);
	static float Max(const float* values, int count);
	static float Max(const std::vector<float>& values);

	static float Sqrt(float value);
	static float Pow(float f, float p);
	static float Exp(float f);//返回e的f次幂
	static float Log(float f);
	static float Log10(float f);

	static bool IsPowerOfTwo(int value);//能否被2开方
	static int NextPowerOfTwo(int value);//下一个能被2开方的整数

	static float Sin(float f);
	static float Cos(float f);
	static float Tan(float f);
	static float Asin(float f);
	static float Acos(float f);
	static float Atan(float f);
	static float Atan2(float y, float x);//返回y/x的反正切值

};

} // namespace rt

#endif //!_RAYTRACER_MATHF_H_