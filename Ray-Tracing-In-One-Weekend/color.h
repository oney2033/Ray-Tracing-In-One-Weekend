#pragma once
#include<iostream>
#include"vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // 将 [0,1] 的值转换为范围 [0,255]。
    int rbyte = int(255.0f * r);
    int gbyte = int(255.0f * g);
    int bbyte = int(255.0f * b);

    // 写出像素颜色的分量
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}