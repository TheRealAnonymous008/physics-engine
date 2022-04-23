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
#include "physics/core/links/DistanceJoint.h"

#include "physics/render/opengl_helper/Scaler.h"

#include "AbstractGL.h"
#include "physics/render/opengl_helper/VertexManager.h"
#include "physics/render/opengl_helper/IndexBufferManager.h"

#include "physics/core/factories/PointFactory.h"
#include "physics//render/opengl_helper/RenderManager.h"

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

	// Engine 
	Physics::Engine* engine = new Physics::Engine((1.0f / (2 * FRAMERATE_LIMIT)), (1.0f / FRAMERATE_LIMIT));

	// Renderer
	GLPhysX::VertexManager* vertex_manager = new GLPhysX::VertexManager(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLPhysX::RenderManager* renderer = new GLPhysX::RenderManager(vertex_manager);

	// Entities
	Physics::Point* p1 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(0, 0), Physics::BodyType::DYNAMIC);
	Physics::Point* p2 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(100, 0), Physics::BodyType::DYNAMIC);
	Physics::Point* p3 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(0, 100), Physics::BodyType::DYNAMIC);
	Physics::Point* p4 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(-5, -50), Physics::BodyType::DYNAMIC);
	Physics::Point* p5 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(0, -10), Physics::BodyType::DYNAMIC);
	Physics::Point* p6 = Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(-100, -100), Physics::BodyType::DYNAMIC);
	Physics::RadialEmitter* em = Physics::PointFactory::GetInstance().MakeRadialEmitter2D(-1000, PMath::init(-100, -100), Physics::BodyType::DYNAMIC);


	Physics::Geometry::RigidTriangle* triangle_A = new Physics::Geometry::RigidTriangle(p1, p2, p3);
	Physics::Geometry::RigidTriangle* triangle_B = new Physics::Geometry::RigidTriangle(p4, p5, p6);

	// Add to engine
	engine->world->AddEntity(triangle_A);
	engine->world->AddEntity(triangle_B);
	engine->world->AddEntity(em);
	
	// Add entitites to emitters
	em->AddObject(triangle_A);	
	em->AddObject(triangle_B);	

	// Add to renderer
	renderer->AddTriangle(triangle_A);
	renderer->AddTriangle(triangle_B);
		
	//engine->world->ApplyGravity();


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


	
	vertex_manager->GenerateArrays();
	GL::VertexBufferObject vb(vertex_manager->GetVertices(), vertex_manager->GetLength() * 3 * sizeof(float));
	vertex_manager->SpecifyLayout();
/*
	GL::IndexBufferObject* ib = index_manager->GenerateIB();*/

	while (!glfwWindowShouldClose(window)) {
		const auto start_time = std::chrono::high_resolution_clock::now();

		// Draw everything here
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader->Bind();
		vertex_manager->Bind();

		// Physics stuff
		engine->Run();

		// Update the graphics

		vb.UnBind();

		vertex_manager->UpdateVertices();

		vb.Bind();
		vb.SubData(vertex_manager->GetVertices(), vertex_manager->GetLength() * 3 * sizeof(float));

		renderer->Render();
		
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
