#ifndef MATERIAL_H
#define MATERIAL_H

enum material_type{
	none = -1,
	lambertian_type,
	metal_type
};

struct material{
	
};

struct lambertian{
	color albedo;
	lambertian(color albedo){
		this->albedo = albedo;
	}
};

struct metal{
	color albedo;
	metal(color albedo){
		this->albedo = albedo;
	}
};

inline bool material_scatter(const metal &mat, const ray& r_in, const hit_record &record, color &attenuation, ray &scattered){
	vec3 reflected = vec_reflect(r_in.direction,record.normal);
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
	if(record.type == lambertian_type)return material_scatter( *(struct metal*)(record.mat), r_in, record, attenuation, scattered);
	if(record.type == metal_type)return material_scatter(*(struct metal*)record.mat, r_in, record, attenuation, scattered);
	return false;
}

#endif
