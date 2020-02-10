#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Particle.h"
#include "ShaderUtil.h"
#include "TextureUtil.h"
#include "StateMachine.h"
#define PI 3.14159265358
#define SLICE (36)
#define STACK (18)
#define PARTICLE_NUMBER SLICE*(STACK+1)*2
using namespace std; 

int windowSize[2] = { 600, 600 };
//int windowSize[2] = { 720, 720 };
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);

GLuint program_particles;
GLuint program_earth;
GLuint vboName_particles;
GLuint vboName_earth;

// Time 
enum STATE time_line = STATE::P0_IDLE;
float earth_time = 0.0f;

// Texture
GLuint texture_fire_front;
GLuint texture_earth_texture;

// Number of particles that will be sent to shader
int particle_number = PARTICLE_NUMBER;
Particle* particle = generate_particles(particle_number);
Element* element = generate_elements(particle_number);

// Sphere
float center[3] = {0, 0, 0};
int earth_particle_number = 360 * (180+1) *2;
Element* earth = generate_shader_sphere(center, 360, 180, 5);

// RuntimeInfo
RuntimeInfo runtime_info;
float global_time = 0.0;

int main(int argc, char** argv) {
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("ComputerGraphicsDemo");

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();

	distribute_particles(element, particle, particle_number);

	shaderInit_Particles(&program_particles, &vboName_particles, element, particle_number);
	shaderInit_Earth(&program_earth, &vboName_earth, element, particle_number);
	textureInit(&texture_fire_front, "FIRE_FRONT_32x32.png");
	textureInit(&texture_earth_texture, "earth_texture_map.jpg");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void display() {   
	// viewing and modeling transformationc
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 30.0f,// eye
		0.0f, 0.0f, 0.0f,// center
		0.0f, 1.0f, 0.0f);// up

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);

	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmtx); // Get Projection-View Matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, mmtx); // Get Model-View Matrix

	enum STATE next_time_line;
	{
		next_time_line = ParticlesUpdate(time_line, &runtime_info, particle, &particle_number);
		SentVBO_Particles(&vboName_particles, element, particle_number);

		glUseProgram(program_particles);

		if (time_line == STATE::P6_RESET_DISABLE ||
			time_line == STATE::P6_SET_XPOS ||
			time_line == STATE::P6_SET_TIMER ||
			time_line == STATE::P6_WAIT_TIMER ||
			time_line == STATE::P6_EXPLOSION// ||
			//time_line == STATE::P3_RESET_DISABLE ||
			//time_line == STATE::P3_SET_TIMER ||
			//time_line == STATE::P3_EARTH_IS_ROTATING
		){
			if(runtime_info.reverse==2)
				glUniform1i(glGetUniformLocation(program_particles, "Opt"), 3);
			else
				glUniform1i(glGetUniformLocation(program_particles, "Opt"), 3);
		}
		else {
			glUniform1i(glGetUniformLocation(program_particles, "Opt"), 0);
		}

		glUniformMatrix4fv(glGetUniformLocation(program_particles, "Projection"), 1, GL_FALSE, pmtx);
		glUniformMatrix4fv(glGetUniformLocation(program_particles, "ModelView"), 1, GL_FALSE, mmtx);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_fire_front);
		glUniform1i(glGetUniformLocation(program_particles, "FireTexture"), 0);

		glDrawArrays(GL_QUADS, 0, particle_number * 4);

		glUseProgram(0);
	}
#if 1
	{
		EarthUpdate(time_line, &runtime_info, earth, earth_particle_number);
		SentVBO_Earth(&vboName_earth, earth, earth_particle_number);

		glUseProgram(program_earth);
		
		glGetFloatv(GL_MODELVIEW_MATRIX, mmtx); // Get Model-View Matrix
		glUniformMatrix4fv(glGetUniformLocation(program_earth, "OriginModelView"), 1, GL_FALSE, mmtx);

		if (time_line == STATE::P3_EARTH_IS_ROTATING) {
			glTranslatef(0, 0, -30.0f-runtime_info.Timer);
			glRotatef(-runtime_info.Timer, 0, 1, 0);
			glUniform1i(glGetUniformLocation(program_earth, "Opt"), 0);
		} 
		else if (
			time_line == STATE::P4_RESET_DISABLE ||
			time_line == STATE::P4_SET_XPOS ||
			time_line == STATE::P4_SET_TIMER ||
			time_line == STATE::P4_WAIT_TIMER ||
			time_line == STATE::P4_EARTH_IS_SIDE
		){
			glTranslatef(7.0f, 0, 20.0f);
			glRotatef(global_time, 0, 1, 0);
			glUniform1f(glGetUniformLocation(program_earth, "Xpos"), runtime_info.Xpos);
			glUniform1i(glGetUniformLocation(program_earth, "Opt"), 1);
		}
		else if (
			time_line == STATE::P5_RESET_DISABLE ||
			time_line == STATE::P5_SET_XPOS ||
			time_line == STATE::P5_SET_TIMER ||
			time_line == STATE::P5_WAIT_TIMER ||
			time_line == STATE::P5_EARTH_IS_FAR
			) {
			glTranslatef(0.0f, 0, -15.0f);
			glRotatef(global_time, 0, 1, 0);
			glUniform1f(glGetUniformLocation(program_earth, "Xpos"), runtime_info.Xpos);
			glUniform1i(glGetUniformLocation(program_earth, "Opt"), 2);
		}
		else if (
			time_line == STATE::P5_5_SET_COUNTER || 
			time_line == STATE::P5_5_SET_TIMER ||
			time_line == STATE::P5_5_WAIT_TIMER ||
			time_line == STATE::P5_5_EARTH_IS_SHAKING
		){
			glTranslatef(0.0f, 0, -15.0f);
			if (runtime_info.counter >= 4) {
				float offx = float(50 - rand() % 100) / 20.0f;
				float offy = float(50 - rand() % 100) / 20.0f;
				glTranslatef(offx, offy, 0);
			}
			glRotatef(global_time, 0, 1, 0);
			glUniform1f(glGetUniformLocation(program_earth, "Xpos"), runtime_info.Xpos);
			glUniform1i(glGetUniformLocation(program_earth, "Opt"), 2);
		}
		else if (
			time_line == STATE::P6_RESET_DISABLE ||
			time_line == STATE::P6_SET_XPOS ||
			time_line == STATE::P6_SET_TIMER ||
			time_line == STATE::P6_WAIT_TIMER ||
			time_line == STATE::P6_EXPLOSION
		){
			glTranslatef(0.0f, 0, -15.0f);
			float offx = float(50 - rand() % 100) / 20.0f;
			float offy = float(50 - rand() % 100) / 20.0f;
			glTranslatef(offx, offy, 0);
			glRotatef(global_time, 0, 1, 0);
			glUniform1f(glGetUniformLocation(program_earth, "Xpos"), runtime_info.Xpos);
			glUniform1i(glGetUniformLocation(program_earth, "Opt"), 2);
		}
		
		glGetFloatv(GL_MODELVIEW_MATRIX, mmtx); // Get Model-View Matrix
		glUniformMatrix4fv(glGetUniformLocation(program_earth, "Projection"), 1, GL_FALSE, pmtx);
		glUniformMatrix4fv(glGetUniformLocation(program_earth, "ModelView"), 1, GL_FALSE, mmtx);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_earth_texture);
		glUniform1i(glGetUniformLocation(program_earth, "EarthTexture"), 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, earth_particle_number);

		glUseProgram(0);
	}
#endif

	time_line = next_time_line;

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y) {
}

void idle() {
	glutPostRedisplay();
	global_time += 0.01f;
	if (global_time > 360.0f) global_time -= 360.0f;
}

