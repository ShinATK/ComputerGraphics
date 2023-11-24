# 作业4 Bezier曲线

# 问题

根据 de Casteljau 算法，完成两个函数，以实现绘制由4个控制点表示的Bezier曲线（正确实现之后，应该能够支持由更多的点来控制的Bezier曲线）

- `bezier`：该函数实现绘制Bezier曲线的功能。
  - 两个参数
    - `const std::vector<cv::Point2f> &control_points`：控制点序列
    - `cv::Mat &window`：在频幕上对应坐标绘制
  - 无返回值
  - 函数体：
    - 使t在0到1的范围内进行迭代，每次迭代中使t增加一个微小值。
    - 对于每一一个需要计算的t，将调用另一个函数 `recursive_bezier`，该函数将返回在Bezier曲线上t处的点
    - 最后，将返回的点绘制在 OpenCV::Mat 对象上
- `recursive_bezier`：使用一个控制点序列和一个浮点数t作为输入，实现de Casteljau算法来返回Bezier曲线上对应点的坐标
  - 参考：[Geometry笔记部分的Bezier曲线](../../../notes/games101notes/02-Geometry/Geometry%20几何图形.md)

# 确定思路

- `bezier`
  - 利用for循环以步长0.001遍历t在0到1取值
  - 循环内：将控制点序列和t传入函数 `recursive_bezier`，接收返回的点
  - 循环内：将返回的点传递给windows以在屏幕对应位置绘制点
  - 循环内：t更新取值，进行下一次循环
- `recursive_bezier`
  - 方法一：
    - 直接根据最后的n阶公式计算
  - 方法二：
    - 利用递归
    - for循环内每次取出相邻的两个点 `points.at(i)` 和 `points.at(i+1)`，带入公式 $p_i*(1-t)+p_{i+1}*t$ 计算
    - 计算得到的新点存入 `new_points` 中
    - 当此次传入的控制点序列迭代完毕后，进行递归 `recursive_bezier(new_points, t)`
    - 终止条件：`control_points.size() == 1`，返回 `control_points`

# 代码实现

`bezier`
```cpp
void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    auto& points = control_points;
    for (double t = 0.0; t <= 1.0; t += 0.001)
    {
        auto point = recursive_bezier(points, t);
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255; // RGB 绿色
    }
}
```

`recursive_bezier`
```cpp
cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
#ifdef METHOD01
    // Method 01:
    // factorial & formula
    auto& points = control_points;
    size_t n = points.size();
    cv::Point2f results;
    float C = 0.0f;
    for (size_t i = 0; i < n; i++) {
        C = factorialC(i, n-1) * pow((1 - t), n-1 - i) * pow(t, i);
        results += C* points.at(i);
    }
    return cv::Point2f(results);
#endif
#ifdef METHOD02
    // Method 02:
    // recursive
    std::vector<cv::Point2f> old_points = control_points;
    std::vector<cv::Point2f> new_points, point;
    size_t n = old_points.size();
    if (n == 1) {
        return cv::Point2f(old_points.at(0));
    }
    for (size_t i = 0; i < n - 1; i++) {
        new_points.push_back(old_points.at(i) * (1 - t) + old_points.at(i + 1) * t);
    }
    return recursive_bezier(new_points, t);
#endif
}
```

# 额外收获

## `recursive_bezier` 的方法一中的问题

正常情况下，输入四个控制点后的Bezier曲线为：
<img src=./img/normal_bezier_curve.png width=50% />

当我按照方法一完成函数后的运行结果为：
<img src=./img/abnormal_bezier_curve_method01.png width=50% />

- 对比两图可以发现，曲线在后边两个控制点处计算得到的曲线结果出现问题
- 问题代码：`C = factorialC(i, n) * pow((1 - t), n - i) * pow(t, i)`
- 由于这里的n为控制点个数，实际上公式中的n应该为控制点两两相邻点相连后的边的个数，应该为n-1
- 修改代码：`C = factorialC(i, n-1) * pow((1 - t), n-1 - i) * pow(t, i)`
- 再次运行图像正确

## `std::vector`

向量（vector）是一个封装了**动态大小数组*的顺序容器（Sequence Container），能够存放各种类型的对象。或者说，向量是一个能够存放任意类型的动态数组

参考链接：[菜鸟教程-C++ vector容器解析](https://www.runoob.com/w3cnote/cpp-vector-container-analysis.html)

- `push_back`：在数组最后添加一个数据
- `pop_back`：去掉数组的最后一个数据
- `at`：得到编号位置的数据
- `begin`：得到数组头的指针
- `end`：得到数组的最后一个单元+1的指针
  - **注意这里是最后一个单元+1的指针，最后一个单元的地址还需要对地址-1**

## `window.at<cv::Vec3b>(point.y, point.x)[1] = 255; // RGB 绿色`

- point.x 和 point.y 的顺序
- `window.at<cv::Vec3b>(point.y, point.x)[index] = 255;`
  - index for RGB 0R,1G,2B