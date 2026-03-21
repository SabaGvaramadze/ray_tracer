#ifndef STAGE_H
#define STAGE_H

struct stage{
	sphere **spheres;
	object **objs;

	size_t sphere_count;
	size_t obj_count;
};

#endif
