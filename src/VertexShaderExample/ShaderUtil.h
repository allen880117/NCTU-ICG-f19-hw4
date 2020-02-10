#pragma once
#include "Particle.h"
void shaderInit_Particles(GLuint *program, GLuint* vboName, Element *elements, int particle_number);
void shaderInit_Earth(GLuint *program, GLuint* vboName, Element *elements, int particle_number);

void SentVBO_Particles(GLuint *vboName, Element *elements, int particle_number);
void SentVBO_Earth(GLuint *vboName, Element *elements, int particle_number);