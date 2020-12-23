# Visualization Method

Python 三维可视化计算三种主要方法

1. 二维标量数据场
    * 颜色映射法，等值线方法，立体图法和层次分割法。
2. 三维标量数据场
    * 面绘制法、体绘制法。
3. 矢量数据场
    * 直接法、流线法。

## 1 Install Package

Download from https://www.lfd.uci.edu/~gohlke/pythonlibs/

* VTK
* numpy
* traits: trait为 Python 对象的属性增加了类型定义的功能
    1. 初始化：每个trait属性都定义有自己的缺省值，这个缺省值用来初始化属性。
    2. 验证：基于trait的属性都有明确的类型定义，只有满足定义的值才能赋值给属性。
    3. 委托：trait属性的值可以委托给其他对象的属性。
    4. 监听：trait属性的值的改变可以触发指定的函数的运行。
    5. 可视化：拥有trait属性的对象可以很方便地提供一个用户界面交互式地改变trait属性的值。
* mayavi
* PyQt4

## 2 Pipeline

* pipeline 技术：

    - tvtk.CubeSource：引入长方体三维数据源
    - tvtk.PolyDataMapper：转化为图形数据
    - tvtk.Actor：创建实体
    - tvtk.Renderer：创建渲染器
    - tvtk.RenderWindow：设置背景
    - tvtk.RenderWindowInteractor：创建交互窗口

* visualization pipeline
  ![visualization](Y:\code\python_study\science_cal\visualization_ppl.png)

- 可视化管线（Visualization Pipeline）：将原始数据加工成图形数据的过程
- 数据->数据预处理->数据映射。
- TVTK对象：CubeSource等（PolyData）、PloyDataMapper

* graphic pipeline
  ![graphic](Y:\code\python_study\science_cal\graphic_ppl.png)

- 图形管线（Graphics Pipeline）：图形数据加工为我们所看到的图像的过程。
- 数据映射->绘制(Rendering)->显示(Displaying)
- TVTK对象：Actor、Renderer、RenderWindow、RenderWindowInteractor
