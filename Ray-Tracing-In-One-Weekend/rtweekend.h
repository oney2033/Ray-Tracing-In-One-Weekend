#pragma once
#include <cmath>
#include <limits>
#include <memory>
#include "ray.h"
#include "vec3.h"
#include"interval.h"
#include <cstdlib>

const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

inline double random_double()
{
	//返回0-1内的随机数
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	//返回min-max内的随机数
	return min + (max - min) * random_double();
}
