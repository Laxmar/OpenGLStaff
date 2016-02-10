#include <stdio.h>
#include <iostream>
#include <memory>

#include "GL\glew.h"
#include "glut.h"

#include <glm\glm.hpp>
#include "glm/gtx/rotate_vector.hpp"

#include "shader.h"
#include "Triangle.h"
#include <vector>

using namespace std;
void createTriangle();
void renderScence();
void keyboardCallback(unsigned char key, int x, int y);
void idle();

vector<shared_ptr<Triangle>> triangles;

glm::mat4 MVP;
GLuint mvpID;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);		
	int window = glutCreateWindow("Triangles Animation");

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.7f, 0.7f, 1.0f);

	glm::mat4 Projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 10.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 3), // where is
		glm::vec3(0, 0, 0), // looks at origin
		glm::vec3(0, 1, 0)  // Head is up
		);
	glm::mat4 Model =  glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 0.0f , 1.0f ));
	MVP = Projection * View * Model;

	GLuint programID = LoadShaders("simpleVertexShader.vert", "simpleFragmentShader.frag");
	glUseProgram(programID);
	//theta = glGetUniformLocation(programID, "theta");
	mvpID = glGetUniformLocation(programID, "MVP");

	glutDisplayFunc(renderScence);		
	glutKeyboardFunc(keyboardCallback);		
	glutIdleFunc(idle);

	createTriangle();

	glutMainLoop();			

	glDeleteProgram(programID);	
	return 0;
}

void renderScence()
{
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
/*

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.0011f,  glm::vec3(1, 1, 1));
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.833, 0.833, 0));
	glm::mat4 translateMatrixReverese = glm::translate(glm::mat4(1.0f), glm::vec3(-0.833, -0.833, 0));
	glm::mat4 Model = translateMatrixReverese * rotationMatrix * translateMatrix;
*/
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.0011f, glm::vec3(1, 1, 1));

	for(auto triangle : triangles)
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), triangle->GetCenterOfMass());
		glm::mat4 translateReverseMatrix = glm::translate(glm::mat4(1.0f), -triangle->GetCenterOfMass());
		glm::mat4 ModelMatrix = translateMatrix * rotationMatrix * translateReverseMatrix;
		MVP *= ModelMatrix;
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

		triangle->Draw();
	}


	glutSwapBuffers();
	
}

void idle()
{
	glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	const int escCode = 27;
	if (key == 'q' || (int)key == escCode)
		exit(EXIT_SUCCESS);
}

void createTriangle() {

	 GLfloat firstTriangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
	};
	GLfloat secondTriangleVertices[] = {
		-1.0f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-1.0f, -0.5f, 0.0f,
	};
	GLfloat thirdTriangleVertices[] = {
		-0.0f, -0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	//triangles.push_back(std::move( std::make_shared<Triangle>(firstTriangleVertices)));
	//triangles.push_back(std::move( std::make_shared<Triangle>(secondTriangleVertices)));
	triangles.push_back(std::move( std::make_shared<Triangle>(thirdTriangleVertices)));
}
