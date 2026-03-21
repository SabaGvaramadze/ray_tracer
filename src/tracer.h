#ifndef TRACER_H
#define TRACER_H

#include <cmath>
#include <cstdlib>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

inline double deg_to_rad(double deg){
	return deg*pi/180;
}

inline double rand_double(){
	return std::rand() / (RAND_MAX + 1.0);
}

inline double rand_double(double min, double max){
	return min + (max-min) * rand_double();
}

#include "vec3.h"
#include "interval.h"
#include "ray.h"
#include "objects.h"
#include "stage.h"
#include "hit.h"
#include "color.h"

const interval empty{infinity,-infinity};
const interval world{-infinity,infinity};

#endif
