#pragma comment(lib, "glu32.lib")	// Required for 3D.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>

#include "physics/core/points/Point.h"
#include "physics//core/points/RadialEmitter.h"
#include "physics/core/points/Emitter.h"
#include "physics/core/Engine.h"
#include "physics/math/Matrix.h"
#include "physics/core/geometry/Triangle.h"

#include "physics/render/opengl_helper/Scaler.h"

#include "AbstractGL.h"

#define FRAMERATE_LIMIT 60
#define SECONDS_PER_FRAME 1.0f / (FRAMERATE_LIMIT * 1.0f)
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

	Physics::Engine* engine = new Physics::Engine((1.0f / (2 * FRAMERATE_LIMIT)), (1.0f / FRAMERATE_LIMIT));
	engine->world->AddEntity(p1);
	engine->world->AddEntity(p2);
	engine->world->AddEntity(p3);
	engine->world->ApplyGravity();

	// GL Proper
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Shaders
	GL::VertexShader* vertex_shader = new GL::VertexShader("physics/render/shaders/Vertex.txt");
	GL::FragmentShader* fragment_shader = new GL::FragmentShader("physics/render/shaders/Fragment.txt");
	GL::ShaderProgram* shader = new GL::ShaderProgram(vertex_shader, fragment_shader);

	//VBO and Indices 

	GL::VertexArrayObject* VAO = new GL::VertexArrayObject();
	VAO->AddVertex3D(GLPhysX::Scale(p1->transform.position, WINDOW_WIDTH, WINDOW_HEIGHT).vec);
	VAO->AddVertex3D(GLPhysX::Scale(p2->transform.position, WINDOW_WIDTH, WINDOW_HEIGHT).vec);
	VAO->AddVertex3D(GLPhysX::Scale(p3->transform.position, WINDOW_WIDTH, WINDOW_HEIGHT).vec);

	unsigned int indices[] = {
		0, 1, 2
	};

	VAO->GenerateArrays();
	GL::VertexBufferObject vb(VAO->GetVertices(), VAO->GetLength() * 3 * sizeof(float));
	VAO->SpecifyLayout();

	GL::IndexBufferObject ib(indices, 3); 

	while (!glfwWindowShouldClose(window)) {
		const auto start_time = std::chrono::high_resolution_clock::now();

		// Draw everything here
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader->Bind();
		VAO->Bind();
		ib.Bind();

		// Physics stuff
		engine->Run();

		// Update the graphics

		VAO->Clear();
		vb.UnBind();

		for (Physics::Object* obj : engine->world->GetEntitites()) {
			VAO->AddVertex3D(GLPhysX::Scale(obj->transform.position, WINDOW_WIDTH, WINDOW_HEIGHT).vec);
		}

		VAO->Bind();
		vb.Bind();
		vb.SubData(VAO->GetVertices(), VAO->GetLength() * 3 * sizeof(float));

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		// Ensure the frame rate is correct
		const auto end_time = std::chrono::high_resolution_clock::now();
		auto wait = 1000 * SECONDS_PER_FRAME - std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
		if(wait > 0)
			_sleep(wait);
		

	}

	shader->Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}
