# my_raytracer
C++实现的光线追踪入门

## 系统结构图
![image](https://github.com/baibaixue/my_raytracer/blob/master/image/structure_chart.JPG)

## 系统流程图
![image](https://github.com/baibaixue/my_raytracer/blob/master/image/flow_chart.JPG)

## 详细设计
> ### 1. 基础函数库
> + Header : c++常用头文件
> + Vector3 : 空间三维向量
> + Color : argb颜色
> + Mathf : 基本数学函数库  

> ### 2. 光线
> + Ray3 : 光线 
> + IntersectResult : 光线和物体相交结果  

> ### 3. 摄像机
> > camera : 相机
> > + PerspectiveCamera : 透视摄像机  

> ### 4. 几何体
> Union : 几何体集合
> > Generations : 几何体接口
> > + Plane : 平面
> > + Sphere : 球
> > + Triangle : 三角形面
> > + Tetrahedron : 四面体    

> ### 5. 材质
> > Material : 材质接口
> > + ColorMaterial : 颜色加深度渲染
> > + CheckMaterial : 格子材质
> > + PhongMaterial : 高光材质  

> ### 6. 光源
> LightUnion : 光源集合
> > LightSample : 光源接口
> > + DirectionLight : 平行光
> > + PointLight : 点光
> > + SpotLight : 聚光灯  

> ### 7. 用户交互
> + `glfwSetScollCallback(glfwWindow,scorllfun)` 鼠标滚轮控制镜头拉近拉远
> + `glfwSetKeyCallback(glfwWindow,key_callback)` 方向键控制镜头移动
> + `Course_Mouse_callback(glfwWindow,xpos,ypos)` 鼠标左键拖拽实现物体绕原点旋转  

> ### 8.其他
> + Init : 初始化场景
> + Render : 整体渲染
