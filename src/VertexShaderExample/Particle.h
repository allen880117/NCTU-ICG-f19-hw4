#pragma once
#include "FreeImage.h"
#include "glew.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
constexpr auto PI = 3.14159265358;
using namespace std;

class Element {
public:
	GLfloat position[3];
	GLfloat texcoord[2];
	GLfloat normal[3];
	int     enable;

public:
	Element() {
		this->set_position(0.0, 0.0, 0.0);
		this->set_texcoord(0.0, 0.0);
		this->set_normal(0.0, 0.0, 0.0);
		this->enable = 0;
	}

	void set_position(float x, float y, float z) {
		this->position[0] = x;
		this->position[1] = y;
		this->position[2] = z;
	}

	void set_position(float x[3]) {
		this->set_position(x[0], x[1], x[2]);
	}

	void set_texcoord(float x, float y) {
		this->texcoord[0] = x;
		this->texcoord[1] = y;
	}

	void set_texcoord(float x[2]) {
		this->set_texcoord(x[0], x[1]);
	}

	void set_normal(float x, float y, float z) {
		this->normal[0] = x;
		this->normal[1] = y;
		this->normal[2] = z;
	}
};

class Particle {
public:
	Element* elements[4];
	GLfloat  middle[3];
	GLfloat  vector[3*4];
	GLfloat  scale;

public:
	Particle() {
		elements[0] = NULL;
		elements[1] = NULL;
		elements[2] = NULL;
		elements[3] = NULL;

		this->middle[0] = 0.0f;
		this->middle[1] = 0.0f;
		this->middle[2] = 0.0f;
		this->set_vector(0, -1, -1, 0);
		this->set_vector(1, +1, -1, 0);
		this->set_vector(2, +1, +1, 0);
		this->set_vector(3, -1, +1, 0);
		this->scale = 1.0f;
	}

	Particle(Element *a, Element *b, Element *c, Element *d) {
		this->middle[0] = 0.0f;
		this->middle[1] = 0.0f;
		this->middle[2] = 0.0f;
		this->set_vector(0, -1, -1, 0);
		this->set_vector(1, +1, -1, 0);
		this->set_vector(2, +1, +1, 0);
		this->set_vector(3, -1, +1, 0);
		this->scale = 1.0f;
		this->set_elements(a, b, c, d);

		elements[0]->set_texcoord(0, 0);
		elements[1]->set_texcoord(1, 0);
		elements[2]->set_texcoord(1, 1);
		elements[3]->set_texcoord(0, 1);
	};
	
	void set_middle(float x, float y, float z) {
		this->middle[0] = x;
		this->middle[1] = y;
		this->middle[2] = z;
		this->set_positions();
	}

	void reset_vector() {
		this->set_vector(0, -1, -1, 0);
		this->set_vector(1, +1, -1, 0);
		this->set_vector(2, +1, +1, 0);
		this->set_vector(3, -1, +1, 0);
		this->set_positions();
	}

	void set_vector(int idx, float x, float y, float z) {
		this->vector[idx * 3 + 0] = x;
		this->vector[idx * 3 + 1] = y;
		this->vector[idx * 3 + 2] = z;
	}

	void rotate_x(float angle) {
		float rad = angle * PI / 180.0f;
		for (int i = 0; i < 4; i++) {
			float x = vector[i * 3 + 0];
			float y = vector[i * 3 + 1];
			float z = vector[i * 3 + 2];
			float temp0 = x;
			float temp1 = cos(rad) * y - sin(rad) * z;
			float temp2 = sin(rad) * y + cos(rad) * z;
			this->vector[i * 3 + 0] = temp0;
			this->vector[i * 3 + 1] = temp1;
			this->vector[i * 3 + 2] = temp2;
		}
		this->set_positions();
	}

	void rotate_y(float angle) {
		float rad = angle * PI / 180.0f;
		for (int i = 0; i < 4; i++) {
			float x = vector[i * 3 + 0];
			float y = vector[i * 3 + 1];
			float z = vector[i * 3 + 2];
			float temp0 = cos(rad) * x + sin(rad) * z;
			float temp1 = y;
			float temp2 = -sin(rad) * x + cos(rad) * z;
			this->vector[i * 3 + 0] = temp0;
			this->vector[i * 3 + 1] = temp1;
			this->vector[i * 3 + 2] = temp2;
		}
		this->set_positions();
	}

	void rotate_z(float angle) {
		float rad = angle * PI / 180.0f;
		for (int i = 0; i < 4; i++) {
			float x = vector[i * 3 + 0];
			float y = vector[i * 3 + 1];
			float z = vector[i * 3 + 2];
			float temp0 = cos(rad) * x - sin(rad) * y;
			float temp1 = sin(rad) * x + cos(rad) * y;
			float temp2 = z;
			this->vector[i * 3 + 0] = temp0;
			this->vector[i * 3 + 1] = temp1;
			this->vector[i * 3 + 2] = temp2;
		}
		this->set_positions();

	}

	float get_middle_x() {
		return this->middle[0];
	}

	float get_middle_y() {
		return this->middle[1];
	}

	float get_middle_z() {
		return this->middle[2];
	}

	void set_middle_x(float x) {
		this->middle[0] = x;
		this->set_positions();
	}

	void set_middle_y(float y) {
		this->middle[1] = y;
		this->set_positions();
	}
	
	void set_middle_z(float z) {
		this->middle[2] = z;
		this->set_positions();
	}

	void add_middle(float x, float y, float z) {
		this->middle[0] += x;
		this->middle[1] += y;
		this->middle[2] += z;
		this->set_positions();
	}

	void mult_middle(float x, float y, float z) {
		this->middle[0] *= x;
		this->middle[1] *= y;
		this->middle[2] *= z;
		this->set_positions();
	}

	void set_scale(float _scale) {
		this->scale = _scale;
		this->set_positions();
	}

	void mult_scale(float _scale) {
		this->scale *= _scale;
		this->set_positions();
	}

	void set_elements(Element* a, Element* b, Element* c, Element* d) {
		elements[0] = a;
		elements[1] = b;
		elements[2] = c;
		elements[3] = d;

		elements[0]->set_texcoord(0, 0);
		elements[1]->set_texcoord(1, 0);
		elements[2]->set_texcoord(1, 1);
		elements[3]->set_texcoord(0, 1);

		this->set_positions();
	}

	void set_positions() {
		for (int i = 0; i < 4; i++) {
			elements[i]->set_position(
				middle[0] + scale * vector[i * 3 + 0], 
				middle[1] + scale * vector[i * 3 + 1],
				middle[2] + scale * vector[i * 3 + 2]
			);
		}
	}

	void enable() {
		for (int i = 0; i < 4; i++)
			elements[i]->enable = 1;
	}

	void disable() {
		for (int i = 0; i < 4; i++)
			elements[i]->enable = 0;
	}

	void rotate_clockwise() {
		float temp[2];
		temp[0] = elements[0]->texcoord[0];
		temp[1] = elements[0]->texcoord[1];
		elements[0]->set_texcoord(elements[1]->texcoord);
		elements[1]->set_texcoord(elements[2]->texcoord);
		elements[2]->set_texcoord(elements[3]->texcoord);
		elements[3]->set_texcoord(temp);
	}

	void rotate_clockwise(int n) {
		for (int i = 0; i < n; i++)
			this->rotate_clockwise();
	}

	~Particle() {
		delete elements[0];
		delete elements[1];
		delete elements[2];
		delete elements[3];
	};
};

struct RuntimeInfo {
	float Timer;
	float Timer_Down;
	float Xpos;
	float Xpos_Down;
	int   counter;
	int   reverse;
	int   shaking;

	RuntimeInfo() {
		this->Timer = 0.0f;
		this->Timer_Down = 0.0f;
		this->Xpos = 0.0f;
		this->counter = 0;
		this->reverse = 0;
		this->Xpos_Down = 0.0f;
		this->shaking = 1;
	};
};

enum class STATE {
	P0_IDLE = 0,

	P1_RESET_DISABLE, //J
	P1_SET_XPOS,
	P1_X_MOVEMENT,

	P2_RESET_DISABLE,
	P2_SET_XPOS,
	P2_SET_TIMER,
	P2_WAIT_TIMER,
	P2_X_MOVEMENT,

	P2_5_SET_TIMER,
	P2_5_WAIT_TIMER,

	P3_RESET_DISABLE,
	P3_SET_TIMER,
	P3_EARTH_IS_ROTATING,

	P4_RESET_DISABLE, // J
	P4_SET_XPOS,
	P4_SET_TIMER,
	P4_WAIT_TIMER,
	P4_EARTH_IS_SIDE,

	P5_RESET_DISABLE,
	P5_SET_XPOS,
	P5_SET_TIMER,
	P5_WAIT_TIMER,
	P5_EARTH_IS_FAR,

	P5_5_SET_COUNTER,
	P5_5_SET_TIMER,
	P5_5_WAIT_TIMER,
	P5_5_EARTH_IS_SHAKING,

	P6_RESET_DISABLE,
	P6_SET_XPOS,
	P6_SET_TIMER,
	P6_WAIT_TIMER,
	P6_EXPLOSION,

	P7_END
};

Element* generate_elements(int particle_number);

Particle* generate_particles(int particle_number);

void distribute_particles(Element * element, Particle * particle, int particle_number);

Element* generate_shader_sphere(float c[3], int slice, int stack, float radius);

void set_sphere_explosion(RuntimeInfo* runtime_info,Particle* particle, int particle_number, float c[3], float radius);
