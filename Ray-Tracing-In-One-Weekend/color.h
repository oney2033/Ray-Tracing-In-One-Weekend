#pragma once
#include<iostream>
#include"vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // �� [0,1] ��ֵת��Ϊ��Χ [0,255]��
    int rbyte = int(255.0f * r);
    int gbyte = int(255.0f * g);
    int bbyte = int(255.0f * b);

    // д��������ɫ�ķ���
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}