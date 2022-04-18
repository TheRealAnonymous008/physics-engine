#pragma comment(lib, "glu32.lib")	// Required for 3D.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "physics/core/points/Point.h"
#include "physics//core/points/RadialEmitter.h"
#include "physics/core/points/Emitter.h"
#include "physics/core/Engine.h"
#include "physics/math/Matrix.h"
#include "physics/core/geometry/Triangle.h"

#define FRAMERATE_LIMIT 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main()
{
	// Insert OpenGL code here.
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Physics Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error in creating window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return -1;
	}
	std::cout << "Successfully Loaded" << glGetString(GL_VERSION) << std::endl;

	// Physics Section
	Physics::Point* p1 = new Physics::Point();
	p1->transform.position = PMath::init(0, 0);
	
	Physics::Point* p2 = new Physics::Point();
	p2->transform.position = PMath::init(100, 0);

	Physics::Point* p3 = new Physics::Point();
	p3->transform.position = PMath::init(0, 100);

	Physics::Geometry::Triangle* triangle = new Physics::Geometry::Triangle(p1, p2, p3);

	// GL Proper
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// Draw everything here


	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}
