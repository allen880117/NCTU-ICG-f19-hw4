#include "Particle.h"
#include <algorithm>
using namespace std;

Element* generate_elements(int particle_number) {
	Element* elements = new Element[particle_number*4];
	return elements;
}

Particle* generate_particles(int particle_number) {
	Particle* particle = new Particle[particle_number];
	return particle;
}

void distribute_particles(Element* element, Particle* particle, int particle_number) {
	for (int i = 0; i < particle_number; i++) {
		particle[i].set_elements(
			&element[i * 4 + 0],
			&element[i * 4 + 1],
			&element[i * 4 + 2],
			&element[i * 4 + 3]
		);
	}
}

Element* generate_shader_sphere(float c[3], int slice, int stack, float radius) {
	Element* vertices;
	vertices = new Element[slice * (stack + 1) * 2];
	int counter = 0;
	float coordXCounter = 1.0f;
	float coordYCounter = 1.0f;
	float stepX = (float)1.0f / slice;
	float stepY = (float)1.0f / (stack + 1);
	double x, y, z;
	double slice_step = 2 * PI / slice, stack_step = PI / stack;
	float cx = c[0];
	float cy = c[1];
	float cz = c[2];
	for (int i = 0; i < slice; i++) {

		coordXCounter = 1.0f - i * stepX;
		coordYCounter = 1.0f;

		for (int j = 0; j < stack + 1; j++) {
			x = cx + radius * sin(j * stack_step) * cos(i * slice_step);
			y = cy + radius * cos(j * stack_step);
			z = cz + radius * sin(j * stack_step) * sin(i * slice_step);
			vertices[counter].set_position(x, y, z);
			vertices[counter].set_texcoord(coordXCounter, coordYCounter);
			vertices[counter].set_normal(x - cx, y - cy, z - cz);
			counter++;

			x = cx + radius * sin(j * stack_step) * cos(i * slice_step + slice_step);
			y = cy + radius * cos(j * stack_step);
			z = cz + radius * sin(j * stack_step) * sin(i * slice_step + slice_step);
			vertices[counter].set_position(x, y, z);
			vertices[counter].set_texcoord(coordXCounter - stepX, coordYCounter);
			vertices[counter].set_normal(x - cx, y - cy, z - cz);
			counter++;

			coordYCounter -= stepY;
			if (coordYCounter <= 0.0f) stepY = -stepY;
		}

		stepY = -stepY;
	}
	return vertices;
}

void set_sphere_explosion(RuntimeInfo* runtime_info, Particle* particle, int particle_number, float c[3], float radius) {
	int counter = 0;
	int slice = 36;
	int stack = 18;
	float stepX = (float)1.0f / slice;
	float stepY = (float)1.0f / (stack + 1);
	double x, y, z;
	double slice_step = 2 * PI / slice, stack_step = PI / stack;
	float cx = c[0];
	float cy = c[1];
	float cz = c[2];
	float multi, offx, offy, sup;

	if(runtime_info->shaking == 1)
	for (int i = 0; i < slice; i++) {
		for (int j = 0; j < stack + 1; j++) {
			multi = float(rand() % 100) / 100.0f + 0.5f;
			offx = (float(rand() % 100) / 100.0f - 0.5f) * 3.0f;
			offy = (float(rand() % 100) / 100.0f - 0.5f) * 3.0f;
			particle[counter].enable();
			particle[counter].reset_vector();
			x = cx + radius * sin(j * stack_step) * cos(i * slice_step);
			y = cy + radius * cos(j * stack_step);
			z = cz + radius * sin(j * stack_step) * sin(i * slice_step);
			particle[counter].set_middle(x, y, z);
			particle[counter].add_middle(offx, offy, 0);
			particle[counter].mult_middle(multi, multi, multi);
			particle[counter].set_scale(multi * 2.0f );
			particle[counter].rotate_clockwise(rand() % 4);
			
			if(runtime_info->reverse != 2)
			particle[counter].set_scale(multi * 5.0f / max(radius,2.0f));

			counter++;

			multi = float(rand() % 40) / 100.0f + 0.8f;
			offx = (float(rand() % 100) / 100.0f - 0.5f) * 3.0f;
			offy = (float(rand() % 100) / 100.0f - 0.5f) * 3.0f;
			particle[counter].enable();
			particle[counter].reset_vector();
			x = cx + radius * sin(j * stack_step) * cos(i * slice_step + slice_step);
			y = cy + radius * cos(j * stack_step);
			z = cz + radius * sin(j * stack_step) * sin(i * slice_step + slice_step);
			particle[counter].set_middle(x, y, z);
			particle[counter].add_middle(offx, offy, 0);
			particle[counter].mult_middle(multi, multi, multi);
			particle[counter].set_scale(multi * 2.0f );
			particle[counter].rotate_clockwise(rand() % 4);

			if (runtime_info->reverse != 2)
			particle[counter].set_scale(multi * 5.0f / max(radius, 2.0f));

			counter++;
		}
	}

}