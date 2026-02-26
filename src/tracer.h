#ifndef TRACER_H
#define TRACER_H

#include <math.h>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

double deg_to_rad(double deg){
	return deg*pi/180;
}

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"

const interval empty(infinity,-infinity);
const interval world(-infinity,infinity);

#endif
