#ifndef _RAYTRACER_MATHF_H_
#define _RAYTRACER_MATHF_H_

#include "header.h"

namespace rt
{

class Mathf
{
public:
	static const float epsilon;//����С
	static const float inifinity;//�����
	static const float PI;//��
	static const float deg2rad;//�Ƕ���ת��Ϊ�����Ƶĵ�λ
	static const float rad2deg;//������ת��Ϊ�Ƕ��Ƶĵ�λ

	static float Abs(float f);//ȡ����ֵ
	static float Sign(float f);//f<0���ظ���,f>0��������
	static bool Approximately(float a, float b);//�ж�a,b�Ƿ�������

	static float Floor(float f);//����ȡ��������float����
	static int FloorToInt(float f);//����ȡ��������int����
	static float Ceil(float f);//����ȡ��������float����
	static int CeilToInt(float f);//����ȡ��������int����
	static float Round(float f);//�������룬����float����
	static int RoundToInt(float f);//�������룬����int����

	static int Clamp(int value, int min, int max);
	//�ж�value�Ƿ���min��max֮�䣬
	//����Ƿ���value�����򷵻�min
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
	static float Exp(float f);//����e��f����
	static float Log(float f);
	static float Log10(float f);

	static bool IsPowerOfTwo(int value);//�ܷ�2����
	static int NextPowerOfTwo(int value);//��һ���ܱ�2����������

	static float Sin(float f);
	static float Cos(float f);
	static float Tan(float f);
	static float Asin(float f);
	static float Acos(float f);
	static float Atan(float f);
	static float Atan2(float y, float x);//����y/x�ķ�����ֵ

};

} // namespace rt

#endif //!_RAYTRACER_MATHF_H_