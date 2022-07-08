//
// Created by LEI XU on 4/11/19.
//
//条件宏
#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

#include <Eigen/Eigen>

using namespace Eigen;
class Triangle {

public:
    Vector3f v[3]; //三角形的原始坐标，v0, v1, v2 逆时针顺序

    //每个顶点的属性
    Vector3f color[3]; //color at each vertex;
    Vector2f tex_coords[3]; //texture u,v
    Vector3f normal[3]; //normal vector for each vertex

    //Texture *tex;
    Triangle();

    void setVertex(int ind, Vector3f ver); /*set i-th vertex coordinates */
    void setNormal(int ind, Vector3f n); /*set i-th vertex normal vector*/
    void setColor(int ind, float r, float g, float b); /*set i-th vertex color*/
    Vector3f getColor() const { return color[0] * 255; } // Only one color per triangle.
    void setTexCoord(int ind, float s, float t); /*设置第 i 个顶点纹理坐标*/
    std::array<Vector4f, 3> toVector4() const;
};


#endif //RASTERIZER_TRIANGLE_H
