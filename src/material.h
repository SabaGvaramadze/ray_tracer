#ifndef MATERIAL_H
#define MATERIAL_H

enum material_type{
	none = -1,
	lambertian_type,
	metal_type,
	dielectric_type
};

struct material{
	
};

struct dielectric{
	double refraction_index;
	dielectric(double refraction_index){
		this->refraction_index = refraction_index;
	}
};

struct lambertian{
	color albedo;
	lambertian(color albedo){
		this->albedo = albedo;
	}
};

struct metal{
	color albedo;
	double fuzz;
	metal(color albedo,double fuzz){
		this->albedo = albedo;
		if(fuzz > 1)this->fuzz = 1;
		else this->fuzz = fuzz;
	}
};

inline double reflectance(double cos, double refraction_index){
	double r0 = (1-refraction_index) / (1 + refraction_index);
	r0 *= r0;
	return r0 + (1-r0)*std::pow((1-cos),5);
}

inline bool material_scatter(const dielectric &mat, const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	attenuation = color(1.0,1.0,1.0);
	double refraction_index;
	if(record.front_face){
		refraction_index =  1.0/mat.refraction_index;
	}
	else{
		refraction_index = mat.refraction_index;
	}


	vec3 unit_direction = vec_unit(r_in.direction);
	vec3 dir;

	double cos_theta = std::fmin(vec_dot(vec_mul(unit_direction,-1),record.normal),1.0);
	double sin_theta = std::sqrt(1-cos_theta*cos_theta);

	if(refraction_index * sin_theta > 1.0 || reflectance(cos_theta,refraction_index) > rand_double()){//cannot refract
		dir = vec_reflect(unit_direction,record.normal);
	}
	else{//should refract
		dir = vec_refract(unit_direction,record.normal,refraction_index);
	}
	
	scattered = ray(record.point,dir);
	return true;
}


inline bool material_scatter(const metal &mat, const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	vec3 reflected = vec_reflect(r_in.direction,record.normal);
	reflected = vec_add(vec_unit(reflected),vec_mul(vec_random_normal(),mat.fuzz));
	scattered = ray(record.point, reflected);
	attenuation = mat.albedo;
	return true;
}

inline bool material_scatter(const lambertian &mat, const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	vec3 scatter_dir = vec_add(record.normal, vec_random_normal());
	if(vec_near_zero(scatter_dir)){
		scatter_dir = record.normal;
	}
	scattered = ray(record.point, scatter_dir);
	attenuation = mat.albedo;
	return true;
}
inline bool material_scatter(const material &mat, const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	return false;
}

inline bool material_scatter(const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	if(record.type == lambertian_type)return material_scatter( *(struct lambertian*)(record.mat), r_in, record, attenuation, scattered);
	if(record.type == metal_type)return material_scatter(*(struct metal*)record.mat, r_in, record, attenuation, scattered);
	if(record.type == dielectric_type)return material_scatter(*(struct dielectric*)record.mat, r_in, record, attenuation, scattered);
	return false;
}

#endif
