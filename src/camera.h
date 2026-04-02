#ifndef CAMERA_H
#define CAMERA_H

#include "material.h"

struct camera{
	double aspect_ratio;
	int image_width;
	int image_height;

	double viewport_height;
	double viewport_width;


	double focal_length;
	vec3 camera_center;

	vec3 viewport_u;
	vec3 viewport_v;

	vec3 pixel_du;
	vec3 pixel_dv;

	vec3 viewport_top_left;
	vec3 pixel00;

	size_t samples_per_pixel;
	double pixel_sample_scale;

	size_t max_depth;

	double vfov;

	vec3 look_from;
	vec3 look_at;
	vec3 vup;

	vec3 u,v,w;

	double defocus_angle;
	double focus_dist;

	vec3 defocus_disk_u;
	vec3 defocus_disk_v;
};

inline vec3 sample_square() {
	return vec3(rand_double()-0.5,rand_double()-0.5,0);
}

inline vec3 defocus_disk_sample(const camera &cam){
	vec3 point = random_in_unit_disk();
	return vec_add(cam.camera_center,vec_add(vec_mul(cam.defocus_disk_u,point.x),vec_mul(cam.defocus_disk_v,point.y)));
}

ray get_ray(const camera &cam,int x,int y){
	vec3 offset = sample_square();
	vec3 pixel_sample_pos = vec_add(cam.pixel00, vec_add(vec_mul(cam.pixel_du, x+offset.x), vec_mul(cam.pixel_dv, y+offset.y)));

	//vec3 origin = cam.camera_center;
	vec3 origin;
	
	if(cam.defocus_angle<=0) origin = cam.camera_center;
	else origin = defocus_disk_sample(cam);

	vec3 direction = vec_sub(pixel_sample_pos,origin);

	return ray(origin,direction);
}

void camera_init(camera &cam){
	cam.aspect_ratio = 16.0/9.0;
	cam.image_width = 800;
	cam.image_height = std::max(1.0,cam.image_width/cam.aspect_ratio);

	cam.look_from = vec3(-3,0.4,3);
	cam.look_at = vec3(0,0,-1);
	cam.vup = vec3(0,1,0);
	
	//cam.look_from = vec3(0,0,0);
	//cam.look_at = vec3(0,0,-1);
	//cam.vup = vec3(0,1,0);
	
	//cam.focal_length = vec_length(vec_sub(cam.look_from,cam.look_at));
	

	cam.defocus_angle = 0;
	cam.focus_dist = 3.4;

	cam.vfov = 20;

	double theta = deg_to_rad(cam.vfov);
	double h = std::tan(theta/2);
	cam.viewport_height = 2 * h * cam.focus_dist;
	cam.viewport_width = cam.viewport_height * ((double)cam.image_width/cam.image_height);

	cam.camera_center = cam.look_from;

	cam.w = vec_unit(vec_sub(cam.look_from,cam.look_at));
	cam.u = vec_unit(vec_cross(cam.vup,cam.w));
	cam.v = vec_cross(cam.w,cam.u);

	cam.viewport_u = vec_mul(cam.u,cam.viewport_width);
	cam.viewport_v = vec_mul(vec_mul(cam.v,-1),cam.viewport_height);

	cam.pixel_du = vec_div(cam.viewport_u,cam.image_width);
	cam.pixel_dv = vec_div(cam.viewport_v,cam.image_height);

	//cam.viewport_top_left = vec_sub(cam.camera_center,vec_add(vec_add(vec_div(cam.viewport_u,2),vec_div(cam.viewport_v,2)),vec3(0,0,cam.focal_length)));

	cam.viewport_top_left = vec_sub(vec_sub(vec_sub(cam.camera_center,vec_mul(cam.w,cam.focus_dist)),vec_div(cam.viewport_u,2)),vec_div(cam.viewport_v,2));
	
	cam.pixel00 = vec_add(cam.viewport_top_left,vec_mul(vec_add(cam.pixel_du,cam.pixel_dv),0.5));

	cam.samples_per_pixel = 150;
	cam.pixel_sample_scale = 1.0 / cam.samples_per_pixel;

	cam.max_depth = 50;
	
	double defocus_radius = cam.focus_dist * std::tan(deg_to_rad(cam.defocus_angle/2));
	cam.defocus_disk_u = vec_mul(cam.u, cam.defocus_angle);
	cam.defocus_disk_v = vec_mul(cam.v, cam.defocus_angle);

}

color camera_ray_color(const ray& r,const int depth,const stage &stg){

	if(depth <= 0)return color(0.0,0.0,0.0);
	hit_record record;

	if(hit(stg,r,interval(0.001,infinity),record)){
		
		ray scattered;
		color attenuation;

		if(material_scatter(r,record,attenuation,scattered)){
			color ray_color = camera_ray_color(scattered,depth-1,stg);
			return color_8(vec_mul(color_normal(ray_color),color_normal(attenuation)));
		}
		return color(0.0,0.0,0.0);
		
		//vec3 direction = vec_random_on_hemisphere(record.normal); old
		vec3 direction = vec_add(record.normal,vec_random_on_hemisphere(record.normal)); // new
		
		color hit_color = camera_ray_color(ray(record.point,direction),depth-1,stg);
		color pixel_color = color((hit_color.r/256.0/2.0),(hit_color.g/256.0/2.0),(hit_color.b/256.0/2.0));
		//color pixel_color = color((record.normal.x+1)/2,(record.normal.y+1)/2,(record.normal.z+1)/2);

	}


	double part = (0.5*(r.direction.y/vec_length(r.direction)+1));
	double part_inverse = 1-part;

	color start(part_inverse,part_inverse,part_inverse);
	color end(part*0.5,part*0.7,part);

	return color((start.r+end.r)/255.0,(start.g+end.g)/255.0,(start.b+end.b)/255.0);
}


void camera_render(camera &cam,const stage &stg){
	camera_init(cam);

	std::cout << "cam.image_width: " << cam.image_width << std::endl << "cam.image_height: " << cam.image_height << std::endl;

	FILE *out_file = fopen("./output.ppm","w");
	fwrite("P3",1,2,out_file);
	fwrite("\n",1,1,out_file);
	fwrite(std::to_string(cam.image_width).c_str(),1,std::to_string(cam.image_width).length(),out_file);
	fwrite(" ",1,1,out_file);
	fwrite(std::to_string(cam.image_height).c_str(),1,std::to_string(cam.image_height).length(),out_file);
	fwrite("\n",1,1,out_file);
	fwrite("255",1,3,out_file);
	fwrite("\n",1,1,out_file);

	
	for(int y=0;y<cam.image_height;y++){
		for(int x=0;x<cam.image_width;x++){
			color pixel_color;
			double rc=0,g=0,b=0;
			for(int i =0;i<cam.samples_per_pixel;i++){
				ray r = get_ray(cam,x,y);
				color tmp_color = camera_ray_color(r,cam.max_depth,stg);
				pixel_color.r += tmp_color.r;
				pixel_color.g += tmp_color.g;
				pixel_color.b += tmp_color.b;
			}
			pixel_color.r *= cam.pixel_sample_scale;
			pixel_color.g *= cam.pixel_sample_scale;
			pixel_color.b *= cam.pixel_sample_scale;

			write_color(out_file,pixel_color);

		}
		std::cout<< "line " << y << " completed"<< std::endl;
	}
	
	std::cout << "========DONE========" << std::endl;
	fclose(out_file);
}
#endif
