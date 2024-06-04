#pragma once
#include"rtweekend.h"
#include"color.h"
#include"hittable.h"
#include<iostream>

class camera
{
public:
    double aspect_ratio = 1.0;  // 图像宽度与高度的比值
    int    image_width = 100;  // 渲染图像宽度（以像素数为单位
    int    samples_per_pixel = 10;//每个像素的随机样本总数

    void render(const hittable& world) 
    {
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) 
        {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) 
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;   // 渲染图像高度
    double pixel_samples_scale;  // 像素颜色的比例
    point3 center;         // 相机的中心
    point3 pixel00_loc;    // 像素 0, 0 的位置
    vec3   pixel_delta_u;  // 像素向右的偏移量
    vec3   pixel_delta_v;  // 像素向下的偏移量


    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3(0, 0, 0);

        // 确定视口尺寸
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width) / image_height);

        // 计算沿水平和垂直视口边缘向下的向量
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // 计算从像素到像素的水平和垂直增量向量
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // 计算左上角像素的位置
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j)const
    {
        //构造一条来自原点并指向随机采样的光线
        //在i和j的周围
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                             + ((i + offset.x()) * pixel_delta_u)
                             + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square()const
    {
        //返回[-0.5, 0-.5] - [+0.5, +0.5] 单位正方形中的随机点
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

	color ray_color(const ray& r, const hittable& world)const
	{
		hit_record rec;
		if (world.hit(r, interval(0, infinity), rec))
		{
			return 0.5 * (rec.normal + (color(1, 1, 1)));
		}

		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

};