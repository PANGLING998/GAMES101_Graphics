#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 
        0, 1, 0, -eye_pos[1],
        0, 0, 1, -eye_pos[2], 
        0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    auto angle = rotation_angle * MY_PI / 180;
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    Eigen::Matrix4f translate;
    translate << cos, -sin, 0, 0,
        sin, cos, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    model = translate * model;
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
    Eigen::Matrix4f persp_ortho;
    persp_ortho << 1 / (aspect_ratio * tan(eye_fov / 2)), 0, 0, 0,
        0, 1 / tan(eye_fov / 2), 0, 0,
        0, 0, (zNear + zFar) / (zNear - zFar), -((2 * zNear * zFar) / (zNear - zFar)),
        0, 0, 1, 0;

    projection = persp_ortho * projection;
    return projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;//定义命令行开关标志，默认为关
    std::string filename = "output.png";

    //接收到的参数大于三个，即检测到通过命令行传入参数时
    if (argc >= 3) {
        command_line = true;
        //从命令行获取角度参数
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            //接收到的参数为四个，那么说明命令行输入了文件名参数
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);//设定700*700像素的光栅器视口

    Eigen::Vector3f eye_pos = { 0, 0, 5 };//设定相机位置

    std::vector<Eigen::Vector3f> pos{ {2, 0, -2}, {0, 2, -2}, {-2, 0, -2} };
    //设定三顶点序号,用于画图时确定需要处理几个顶点，这里表示的是三个顶点
    std::vector<Eigen::Vector3i> ind{ {0, 1, 2} };

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);
    //键盘输入
    int key = 0;
    int frame_count = 0;//帧序号
    //如果命令行开关标志为开（这一段if代码是为了应用命令行传入的参数，比如初始角度和文件名
    if (command_line) {
        //初始化帧缓存和深度缓存
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, -0.1, -50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }
    //只要没有检测到按下ESC就循环(ESC的ASCII码是27)
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
