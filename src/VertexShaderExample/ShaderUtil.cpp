#include "Particle.h"
#include "ShaderUtil.h"
#include "shader.h"

void shaderInit_Particles(GLuint* program, GLuint* vboName, Element* elements, int particle_number){
	GLuint vert = createShader("Shaders/fire.vert", "vertex");
	GLuint frag = createShader("Shaders/fire.frag", "fragment");
	*program = createProgram(vert, frag);

	//Generate a new buffer object
	glGenBuffers(1, vboName);

	//Copy vertex data to the buffer object
	SentVBO_Particles(vboName, elements, particle_number);
}

void shaderInit_Earth(GLuint *program, GLuint* vboName, Element* elements, int particle_number) {
	GLuint vert = createShader("Shaders/earth.vert", "vertex");
	GLuint frag = createShader("Shaders/earth.frag", "fragment");
	*program = createProgram(vert, frag);

	//Generate a new buffer object
	glGenBuffers(1, vboName);

	//Copy vertex data to the buffer object
	SentVBO_Earth(vboName, elements, particle_number);
}

void SentVBO_Particles(GLuint* vboName, Element* elements, int particle_number){
	glBindBuffer(GL_ARRAY_BUFFER, *vboName);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Element) * particle_number * 4, elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, texcoord)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, enable)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SentVBO_Earth(GLuint* vboName, Element* elements, int particle_number){
	glBindBuffer(GL_ARRAY_BUFFER, *vboName);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Element) * particle_number, elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, texcoord)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, enable)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Element), (void*)(offsetof(Element, normal)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}