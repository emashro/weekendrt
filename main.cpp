#include <iostream>
#include <float.h>
#include <assert.h>
#include <algorithm>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitablelist.h"
#include "bvh.h"
#include "material.h"
#include "camera.h"
#include "rect.h"
#include "box.h"
#include "constant_medium.h"
#include "stb_image.h"

vec3 color(const ray &r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return emitted + attenuation * color(scattered, world, depth + 1);
		} else {
			return emitted;
		}
	} else {
#if 0
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
#else
		return vec3(0.0f, 0.0f, 0.0f);
#endif
	}
}

hitable *simple_light()
{
	texture *partext = new noise_texture(4);
	hitable **list = new hitable *[4];
	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(partext));
	list[1] = new sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, new lambertian(partext));
	list[2] = new sphere(vec3(0.0f, 7.0f, 0.0f), 2.0f, new diffuse_light(new constant_texture(vec3(4.0f, 4.0f, 4.0f))));
	list[3] = new xy_rect(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, new diffuse_light(new constant_texture(vec3(4.0f, 4.0f, 4.0f))));
	return new hitable_list(list, 4);
}

hitable *earth()
{
	int nx, ny, nn;
	unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
	material *mat = new lambertian(new image_texture(tex_data, nx, ny));
	return new sphere(vec3(0.0f, 0.0f, 0.0f), 2.0f, mat);
}

hitable *two_spheres()
{
	texture *checker = new checker_texture(new constant_texture(vec3(0.2f, 0.3f, 0.2f)), new constant_texture(vec3(0.9f, 0.9f, 0.9f)));
	int n = 50;
	hitable **list = new hitable*[n + 1];
	int i = 0;
	list[i++] = new sphere(vec3(0.0f, -10.0f, 0.0f), 10.0f, new lambertian(checker));
	list[i++] = new sphere(vec3(0.0f, +10.0f, 0.0f), 10.0f, new lambertian(checker));
	return new hitable_list(list, 2);
}

hitable *two_perlin_spheres()
{
	texture *pertext = new noise_texture(4.0f);
	hitable **list = new hitable*[2];
	int i = 0;
	list[i++] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(pertext));
	list[i++] = new sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, new lambertian(pertext));
	return new hitable_list(list, i);
}

hitable *cornell_box()
{
	hitable **list = new hitable *[8];
	int i = 0;
	material *red = new lambertian(new constant_texture(vec3(0.65f, 0.05f, 0.05f)));
	material *white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material *green = new lambertian(new constant_texture(vec3(0.12f, 0.45f, 0.15f)));
	material *light = new diffuse_light(new constant_texture(vec3(15.0f, 15.0f, 15.0f)));
	list[i++] = new flip_normals(new yz_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, green));
	list[i++] = new yz_rect(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, red);
	list[i++] = new xz_rect(213.0f, 343.0f, 227.0f, 332.0f, 554.0f, light);
	list[i++] = new flip_normals(new xz_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));
	list[i++] = new xz_rect(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, white);
	list[i++] = new flip_normals(new xy_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));
	list[i++] = new translate(new rotate_y(new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 165.0f, 165.0f), white), -18.0f), vec3(130.0f, 0.0f, 65.0f));
	list[i++] = new translate(new rotate_y(new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 330.0f, 165.0f), white),  15.0f), vec3(265.0f, 0.0f, 295.0f));
	return new hitable_list(list, i);
}

hitable *cornell_smoke()
{
	hitable **list = new hitable *[8];
	int i = 0;
	material *red = new lambertian(new constant_texture(vec3(0.65f, 0.05f, 0.05f)));
	material *white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material *green = new lambertian(new constant_texture(vec3(0.12f, 0.45f, 0.15f)));
	material *light = new diffuse_light(new constant_texture(vec3(15.0f, 15.0f, 15.0f)));
	list[i++] = new flip_normals(new yz_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, green));
	list[i++] = new yz_rect(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, red);
	list[i++] = new xz_rect(213.0f, 343.0f, 227.0f, 332.0f, 554.0f, light);
	list[i++] = new flip_normals(new xz_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));
	list[i++] = new xz_rect(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, white);
	list[i++] = new flip_normals(new xy_rect(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));
	hitable *b1 = new translate(new rotate_y(new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 165.0f, 165.0f), white), -18.0f), vec3(130.0f, 0.0f, 65.0f));
	hitable *b2 = new translate(new rotate_y(new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 330.0f, 165.0f), white),  15.0f), vec3(265.0f, 0.0f, 295.0f));
	list[i++] = new constant_medium(b1, 0.01f, new constant_texture(vec3(1.0f, 1.0f, 1.0f)));
	list[i++] = new constant_medium(b2, 0.01f, new constant_texture(vec3(0.0f, 0.0f, 0.0f)));
	return new hitable_list(list, i);
}

hitable *final()
{
	int nb = 20;
	hitable **list = new hitable *[30];
	hitable **boxlist = new hitable *[10000];
	hitable **boxlist2 = new hitable *[10000];
	material *white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material *ground = new lambertian(new constant_texture(vec3(0.48f, 0.83f, 0.53f)));
	int b = 0;
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < nb; j++) {
			float w = 100.0f;
			float x0 = -1000.0f + float(i) * w;
			float z0 = -1000.0f + float(j) * w;
			float y0 = 0;
			float x1 = x0 + w;
			float y1 = 100.0f * (drand48() + 0.01f);
			float z1 = z0 + w;
			boxlist[b++] = new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
		}
	}
	int l = 0;
	list[l++] = new bvh_node(boxlist, b, 0.0f, 1.0f);
	material *light = new diffuse_light(new constant_texture(vec3(7.0f, 7.0f, 7.0f)));
	list[l++] = new xz_rect(123.0f, 423.0f, 147.0f, 412.0f, 554.0f, light);
	vec3 center(400.0f, 400.0f, 200.0f);
	list[l++] = new moving_sphere(center, center + vec3(30.0f, 0.0f, 0.0f), 0.0f, 1.0f, 50.0f, new lambertian(new constant_texture(vec3(0.7f, 0.3f, 0.1f))));
	list[l++] = new sphere(vec3(260.0f, 150.0f, 45.0f), 50.0f, new dielectric(1.5f));
	list[l++] = new sphere(vec3(0.0f, 150.0f, 145.0f), 50.0f, new metal(vec3(0.8f, 0.8f, 0.9f), 10.0f));
	hitable *boundary = new sphere(vec3(360.0f, 150.0f, 145.0f), 70.0f, new dielectric(1.5f));
	list[l++] = boundary;
	list[l++] = new constant_medium(boundary, 0.2f, new constant_texture(vec3(0.2f, 0.4f, 0.9f)));
	boundary = new sphere(vec3(0.0f, 0.0f, 0.0f), 5000.0f, new dielectric(1.5f));
	list[l++] = new constant_medium(boundary, 0.0001f, new constant_texture(vec3(1.0f, 1.0f, 1.0f)));
	int nx, ny, nn;
	unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
	material *emat = new lambertian(new image_texture(tex_data, nx, ny));
	list[l++] = new sphere(vec3(400.0f, 200.0f, 400.0f), 100.0f, emat);
	texture *pertext = new noise_texture(0.1f);
	list[l++] = new sphere(vec3(220.0f, 280.0f, 300.0f), 80.0f, new lambertian(pertext));
	int ns = 1000;
	for (int j = 0; j < ns; j++) {
		boxlist2[j] = new sphere(vec3(165.0f * drand48(), 165.0f * drand48(), 165.0f * drand48()), 10.0f, white);
	}
	list[l++] = new translate(new rotate_y(new bvh_node(boxlist2, ns, 0.0f, 1.0f), 15.0f), vec3(-100.0f, 270.0f, 395.0f));
	return new hitable_list(list, l);
}

hitable *random_scene()
{
	int n = 50000;
	hitable **list = new hitable *[n + 1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2f, 0.3f, 0.2f)), new constant_texture(vec3(0.9f, 0.9f, 0.9f)));
	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(checker));
	int i = 1;
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			float choose_mat = drand48();
			vec3 center(a + 0.9f * drand48(), 0.2f, b + 0.9f + drand48());
			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
				if (choose_mat < 0.8f) { // diffuse
					list[i++] = new moving_sphere(center, center + vec3(0.0f, 0.5f * drand48(), 0.0f), 0.0f, 1.0f, 0.2f, new lambertian(new constant_texture(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()))));
				} else if (choose_mat < 0.95f) { // metal
					list[i++] = new sphere(center, 0.2f, new metal(vec3(0.5f * (1.0f + drand48()), 0.5f * (1.0f + drand48()), 0.5f * (1.0f + drand48())), 0.5 * drand48()));
				} else { // glass
					list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f));
	list[i++] = new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(new constant_texture(vec3(0.4f, 0.2f, 0.1f))));
	list[i++] = new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));
	//return new hitable_list(list, i);
	return new bvh_node(list, i, 0.0f, 1.0f);
}

int main()
{
#if 0
	int nx = 200;
	int ny = 100;
	int ns = 100;
#else
	int nx = 1200;
	int ny = 800;
	int ns = 10;
#endif
#if 0
	hitable *list[5];
	list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3(0.1f, 0.2f, 0.5f)));
	list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));
	list[4] = new sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, new dielectric(1.5f));
	hitable *world = new hitable_list(list, 5);
	vec3 lookfrom(3.0f, 3.0f, 2.0f);
	vec3 lookat(0.0f, 0.0f, -1.0f);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2.0f;
#endif
#if 0
	hitable *world = simple_light();
	vec3 lookfrom(13.0f * 2.0f, 2.0f * 2.0f, 3.0f * 2.0f);
	vec3 lookat(0.0f, 2.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 20.0f;
#endif
#if 0
	hitable *world = earth();
	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
#endif
#if 0
	//ns = 100;
	hitable *world = two_spheres();
	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
#endif
#if 0
	//ns = 100;
	hitable *world = two_perlin_spheres();
	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
#endif
#if 0
	hitable *world = random_scene();
	vec3 lookfrom(13.0f, 2.0f, 3.0f);
	vec3 lookat(0.0f, 0.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.1f;
	float vfov = 20.0f;
#endif
#if 0
	nx = 512;
	ny = 512;
	ns = 200;
	hitable *world = cornell_box();
	vec3 lookfrom(278.0f, 278.0f, -800.0f);
	vec3 lookat(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;
#endif
#if 0
	nx = 512;
	ny = 512;
	ns = 500;
	hitable *world = cornell_smoke();
	vec3 lookfrom(278.0f, 278.0f, -800.0f);
	vec3 lookat(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;
#endif
#if 1
	nx = 512;
	ny = 512;
	ns = 2000;
	hitable *world = final();
	vec3 lookfrom(478.0f, 278.0f, -600.0f);
	vec3 lookat(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;
#endif
	camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), vfov, float(nx) / float(ny), aperture, dist_to_focus, 0.0f, 1.0f);
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2]));
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);
			if (ir > 255) ir = 255;
			if (ig > 255) ig = 255;
			if (ib > 255) ib = 255;
			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
