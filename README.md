# my_raytracer
C++实现的光线追踪入门

## 系统结构图
![image](https://github.com/baibaixue/my_raytracer/blob/master/image/structure_chart.JPG)

## 系统流程图
![image](https://github.com/baibaixue/my_raytracer/blob/master/image/flow_chart.JPG)

## 详细设计
> ### 1. 基础函数库
> + Hearer : c++常用头文件
> + Vector3 : 空间三维向量
> + Color : argb颜色
> + Mathf : 基本数学函数库
---------------
> ### 2. 光线
> + Ray3 : 光线 
> + IntersectResult : 光线和物体相交结果
-----------------
> ### 3. 摄像机
> > camera : 相机
> > + PerspectiveCamera : 透视摄像机
------------------
> ### 4. 几何体
> Union : 几何体集合
> > Generations : 几何体接口
> > + Plane : 平面
> > + Sphere : 球
> > + Triangle : 三角形面
> > + Tetrahedron : 四面体
--------------
