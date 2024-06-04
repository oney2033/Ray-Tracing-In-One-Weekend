#pragma once
#include<iostream>
#include"vec3.h"
#include"interval.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // �� [0,1] ��ֵת��Ϊ��Χ [0,255]��
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // д��������ɫ�ķ���
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}