#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) //�����λ���Ƶ�ԭ��
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate; // ��ʼ���ӽǱ任����
    translate <<    1, 0, 0, -eye_pos[0], //��eye_pos��x, y, z, 1���������λ��
                    0, 1, 0, -eye_pos[1], 
                    0, 0, 1, -eye_pos[2], 
                    0, 0, 0, 1;

    view = translate * view; // ����ƶ���ԭ��

    return view;
}

//�˺����У���ֻ��Ҫʵ����ά���� z ����ת�ı任���󣬶����ô���ƽ�������š�
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.

    float r = rotation_angle / 180.0 * MY_PI; // ��ת�Ļ���
    Eigen::Matrix4f rotation;// ��ʼ��ģ�ͱ任����
    rotation << cos(r), -sin(r), 0, 0, 
                sin(r), cos(r), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1;
    
    model = rotation * model;

    return model;
}

//ʹ�ø����Ĳ������Ԫ�صع���͸��ͶӰ���󲢷��ظþ���
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();//���� 4*4 ��λ����

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    Eigen::Matrix4f persp_to_ortho = Eigen::Matrix4f::Identity();//͸��->�����ġ���ѹ������
    persp_to_ortho << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -zNear * zFar,
        0, 0, 1, 0;

    float half_eye_fovY = eye_fov / 2 / 180.0 * MY_PI;

    float top = zNear * tan(half_eye_fovY);
    float bottom = -top;
    float right = aspect_ratio * top;
    float left = -right;//׶���Ѿ�����˷��飨�����������嶼�п��ܣ�

    Eigen::Matrix4f ortho_translate = Eigen::Matrix4f::Identity();//�����������Ƶ�ԭ��
    ortho_translate << 1, 0, 0, -(right + left) / 2,
        0, 1, 0, -(top + bottom) / 2,
        0, 0, 1, -(zNear + zFar) / 2,
        0, 0, 0, 1;

    Eigen::Matrix4f ortho_scale = Eigen::Matrix4f::Identity();//�����鳤���ȫ���2
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
