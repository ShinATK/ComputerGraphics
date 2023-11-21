#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) //把相机位置移到原点
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate; // 初始化视角变换矩阵
    translate <<    1, 0, 0, -eye_pos[0], //点eye_pos（x, y, z, 1）：相机的位置
                    0, 1, 0, -eye_pos[1], 
                    0, 0, 1, -eye_pos[2], 
                    0, 0, 0, 1;

    view = translate * view; // 相机移动到原点

    return view;
}

//此函数中，你只需要实现三维中绕 z 轴旋转的变换矩阵，而不用处理平移与缩放。
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.

    float r = rotation_angle / 180.0 * MY_PI; // 旋转的弧度
    Eigen::Matrix4f rotation;// 初始化模型变换矩阵
    rotation << cos(r), -sin(r), 0, 0, 
                sin(r), cos(r), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1;
    
    model = rotation * model;

    return model;
}

//使用给定的参数逐个元素地构建透视投影矩阵并返回该矩阵。
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();//定义 4*4 单位矩阵

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    Eigen::Matrix4f persp_to_ortho = Eigen::Matrix4f::Identity();//透视->正交的“挤压”矩阵”
    persp_to_ortho << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -zNear * zFar,
        0, 0, 1, 0;

    float half_eye_fovY = eye_fov / 2 / 180.0 * MY_PI;

    float top = zNear * tan(half_eye_fovY);
    float bottom = -top;
    float right = aspect_ratio * top;
    float left = -right;//锥体已经变成了方块（长方体正方体都有可能）

    Eigen::Matrix4f ortho_translate = Eigen::Matrix4f::Identity();//将方块中心移到原点
    ortho_translate << 1, 0, 0, -(right + left) / 2,
        0, 1, 0, -(top + bottom) / 2,
        0, 0, 1, -(zNear + zFar) / 2,
        0, 0, 0, 1;

    Eigen::Matrix4f ortho_scale = Eigen::Matrix4f::Identity();//将方块长宽高全变成2
    ortho_scale << 2 / (right - left), 0, 0, 0,
        0, 2 / (top - bottom), 0, 0,
        0, 0, 2 / (zNear - zFar), 0,
        0, 0, 0, 1;

    projection = ortho_scale * ortho_translate * persp_to_ortho;

    return projection;
}


// TODO: Rotation by angle alpha around axis n
Eigen::Matrix4f get_rotation(Vector3f axis, float angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f axis_4 = Eigen::Matrix4f::Identity();
    axis_4 << axis.x(), 0, 0, 0,
        0, axis.y(), 0, 0,
        0, 0, axis.z(), 0,
        0, 0, 0, 1;
    Eigen::Matrix4f N = Eigen::Matrix4f::Identity();
    N << 0, -axis.z(), axis.y(), 0,
        axis.z(), 0, -axis.x(), 0,
        -axis.y(), axis.x(), 0, 0,
        0, 0, 0, 1;

    model = cos(angle)*model + (1-cos(angle))*axis_4*axis_4.transpose() + sin(angle) * N;

    return model;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
