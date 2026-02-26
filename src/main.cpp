#include <iostream>
#include <cstring>
#include <algorithm>
#include "color.h"
#include "ray.h"
#include "objects.h"
#include "hit.h"
#include "stage.h"
#include "tracer.h"
#include "interval.h"

using namespace std;
color ray_color(const ray &r,const stage &stg);

int main(){
	const double aspect_ratio = 16.0/9.0;
	const int image_width = 400;
	const int image_height = max(1.0,image_width/aspect_ratio);

	const double viewport_height = 2.0;
	const double viewport_width = viewport_height * ((double)image_width/image_height);


	const double focal_length = 1.0;
	const vec3 camera_center(0,0,0);

	const vec3 viewport_u(viewport_width,0,0);
	const vec3 viewport_v(0,-viewport_height,0);

	const vec3 pixel_du = vec_div(viewport_u,image_width);
	const vec3 pixel_dv = vec_div(viewport_v,image_height);

	const vec3 viewport_top_left = vec_sub(camera_center,vec_add(vec_add(vec_div(viewport_u,2),vec_div(viewport_v,2)),vec3(0,0,focal_length)));
	const vec3 pixel00 = vec_add(viewport_top_left,vec_mul(vec_add(pixel_du,pixel_dv),0.5));


	
	cout << "image_width: " << image_width << endl << "image_height: " << image_height << endl;

	FILE *out_file = fopen("./output.ppm","w");
	fwrite("P3",1,2,out_file);
	fwrite("\n",1,1,out_file);
	fwrite(to_string(image_width).c_str(),1,to_string(image_width).length(),out_file);
	fwrite(" ",1,1,out_file);
	fwrite(to_string(image_height).c_str(),1,to_string(image_height).length(),out_file);
	fwrite("\n",1,1,out_file);
	fwrite("255",1,3,out_file);
	fwrite("\n",1,1,out_file);

	sphere s;
	s.position = vec3(0,0,-1);
	s.radius = 0.5;

	stage stg;

	stg.sphere_count = 2;

	stg.spheres = (sphere**)malloc(sizeof(sphere*)*stg.sphere_count);
	stg.spheres[0] = new sphere(vec3(0,0,-1),0.5);
	stg.spheres[1] = new sphere(vec3(0,-100.5,-1),100);

	
	for(int y=0;y<image_height;y++){
		for(int x=0;x<image_width;x++){
			vec3 pixel_pos = vec_add(pixel00,vec_add(vec_mul(pixel_du,x),vec_mul(pixel_dv,y)));
			vec3 ray_direction_vector = vec_sub(pixel_pos,camera_center);
			ray r(camera_center,ray_direction_vector);

			color pixel_color = ray_color(r,stg);

			hit_record record;

			write_color(out_file,pixel_color);

		}
		cout<< "line " << y << " completed"<< endl;
	}
	
	cout << "========DONE========" << endl;
	fclose(out_file);
}


color ray_color(const ray &r,const stage &stg){
	double part = (0.5*(r.direction.y/vec_length(r.direction)+1));
	double part_inverse = 1-part;

	hit_record record;
	
	bool hitS = hit(stg,r,interval(0,infinity),record);

	if(hitS){
		color pixel_color = color((record.normal.x+1)/2,(record.normal.y+1)/2,(record.normal.z+1)/2);
		return pixel_color;
	}

	color start(part_inverse,part_inverse,part_inverse);
	color end(part*0.5,part*0.7,part);

	return color((start.r+end.r)/255.0,(start.g+end.g)/255.0,(start.b+end.b)/255.0);
}
