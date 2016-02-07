#include <stdio.h>
#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glut.h>

#include "shader.h"

using namespace std;

void initVertexArray();
void createTriangle();
void renderScence();
void keyCallback(unsigned char key, int x, int y);

int main(int argc, char *argv[])
{
	int window;
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);		
	window = glutCreateWindow("Triangles Animation");	

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0.7, 0.7, 1);
	GLuint programID = LoadShaders("shaders/simpleVertexShader.vert", "shaders/simpleFragmentShader.frag");
	glUseProgram(programID);


	glutDisplayFunc(renderScence);		
	glutKeyboardFunc(keyCallback);		

	initVertexArray();
	createTriangle();

	glutMainLoop();			

	return 0;
}

void renderScence(void)
{
	glEnableVertexAttribArray(0);
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);


	glutSwapBuffers();
}

void keyCallback(unsigned char key, int x, int y)
{
	if (key == 'q') exit(0);
}

void initVertexArray() {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void createTriangle() {


	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT,  GL_FALSE, 0,(void*)0);
	glDisableVertexAttribArray(0);
}