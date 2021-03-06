#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>

#include "GL\glew.h"
#include "glut.h"
#include "glm\glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "shader.h"
#include "Triangle.h"
#include "Color.h"

using namespace std;
void renderScence();
void keyboardCallback(unsigned char key, int x, int y);
void idle();
void createFigure();
void createQuarter(GLfloat* trianglesVertices);

vector<shared_ptr<Triangle>> triangles;

glm::mat4 VP_MATRIX;
GLuint mvpID;
GLuint angleAroudOriginID;
GLuint colorInID;

float angleAroundOrigin = 0;
const float speedAroundOrigin = 0.02;

float angleAroundCenterOfMass = 0;
const float  speedAroundCenterOfMass = 0.001;

float flyAwayValue = 0;
const float flyAwaySpeed = 0.0003;


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);		
	int window = glutCreateWindow("Triangles Animation");

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.7f, 0.7f, 1.0f);

	glm::mat4 Projection = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, 0.0f, 10.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 3), // where is
		glm::vec3(0, 0, 0), // looks at origin
		glm::vec3(0, 1, 0)  // Head is up
		);
	VP_MATRIX = Projection * View;

	GLuint programID = LoadShaders("simpleVertexShader.vert", "simpleFragmentShader.frag");
	glUseProgram(programID);
	mvpID = glGetUniformLocation(programID, "MVP");
	angleAroudOriginID = glGetUniformLocation(programID, "angle");
	colorInID = glGetUniformLocation(programID, "colorIn");

	glutDisplayFunc(renderScence);		
	glutKeyboardFunc(keyboardCallback);		
	glutIdleFunc(idle);

	createFigure();

	glutMainLoop();			

	glDeleteProgram(programID);	
	return 0;
}

void renderScence()
{
/*

	glm::vec3 eulerEngles = glm::vec3(speedAroundCenterOfMass, speedAroundCenterOfMass, speedAroundCenterOfMass);
	glm::quat myQuat = glm::quat(eulerEngles);
	glm::mat4 rotationMatrix = glm::toMat4(myQuat);
*/

	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	glm::mat4 rotationAroundCenterOfMass = glm::rotate(glm::mat4(1.0), angleAroundCenterOfMass, glm::vec3(1.0, 1.0, 1.0));
	glm::vec3 flyVec = glm::vec3(flyAwayValue, flyAwayValue, 0);
	for(auto triangle : triangles)
	{
		int flyX = 1, flyY = 1;
		triangle->GetCenterOfMass().x > 0 ? flyX = 1 : flyX = -1;
		triangle->GetCenterOfMass().y > 0 ? flyY = 1 : flyY = -1;
		glm::mat4 flyAway = glm::translate(glm::mat4(1.0f), glm::vec3(flyVec.x * flyX, flyVec.y * flyY  , flyVec.z));
		glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0), triangle->GetCenterOfMass());
		glm::mat4 translateFromOrigin = glm::translate(glm::mat4(1.0), -triangle->GetCenterOfMass());
		glm::mat4 rotationMatrix = translateToOrigin * rotationAroundCenterOfMass * translateFromOrigin;
		triangle->ModelMatrix = flyAway * rotationMatrix;
		glm::mat4 MVP = VP_MATRIX * triangle->ModelMatrix;
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
		glUniform1f(angleAroudOriginID, angleAroundOrigin);
		glUniform4fv(colorInID, 1, &(triangle->getColor().value[0]));
		triangle->draw();
	}
	glutSwapBuffers();
}

void idle()
{
	angleAroundOrigin += speedAroundOrigin;
	if (angleAroundOrigin > 360)
		angleAroundOrigin -= 360;

	angleAroundCenterOfMass += speedAroundCenterOfMass;
	flyAwayValue += flyAwaySpeed;

	glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	const int escCode = 27;
	if (key == 'q' || (int)key == escCode)
		exit(EXIT_SUCCESS);
}

void createFigure() {

	const int trianglesNumber = 6;
	GLfloat trianglesVertices[] = {
		//blue
		0.0f, 0.0f, 0.0f,
		2.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		//greeen
		0.0f, 2.0f, 0.0f,
		0.0f, 4.0f, 0.0f,
		2.0f, 2.0f, 0.0f,
		//orange
		2.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 0.0f,
		//yellow
		2.0f, 4.0f, 0.0f,
		2.0f, 2.0f, 0.0f,
		4.0f, 2.0f, 0.0f,
		//pink
		4.0f, 2.0f, 0.0f,
		6.0f, 0.0f, 0.0f,
		4.0f, 0.0f, 0.0f,
		//red
		0.0f, 6.0f, 0.0f,
		0.0f, 4.0f, 0.0f,
		2.0f, 4.0f, 0.0f,
	};
	createQuarter(trianglesVertices);

	//flip vertical
	for (int i = 0; i < trianglesNumber * 9; i += 3)
	{
		trianglesVertices[i] *= -1;
	}
	createQuarter(trianglesVertices);

	//flip horizontall 
	for (int i = 1; i < trianglesNumber * 9; i += 3)
	{
		trianglesVertices[i] *= -1;
	}
	createQuarter(trianglesVertices);

	//flip vertical 
	for (int i = 0; i < trianglesNumber * 9; i += 3)
	{
		trianglesVertices[i] *= -1;
	}
	createQuarter(trianglesVertices);

}

void createQuarter (GLfloat* trianglesVertices)
{
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices, Color::blue())));
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices + 9, Color::green())));
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices + 18, Color::oragne())));
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices + 27, Color::yellow())));
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices + 36, Color::pink())));
	triangles.push_back(std::move(std::make_shared<Triangle>(trianglesVertices + 45, Color::red())));
}
