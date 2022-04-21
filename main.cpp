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

#include "physics//render/opengl_helper/GLWrappers.h"
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
	GLPhysX::RenderManager* renderer = new GLPhysX::RenderManager();

	// Entities
	GLPhysX::Point* p1 = new GLPhysX::Point(Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(0, 0), Physics::BodyType::DYNAMIC));
	GLPhysX::Point* p2 = new GLPhysX::Point(Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(100, 0), Physics::BodyType::DYNAMIC));
	GLPhysX::Point* p3 = new GLPhysX::Point(Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(0, 100), Physics::BodyType::DYNAMIC));
	GLPhysX::Point* p4 = new GLPhysX::Point(Physics::PointFactory::GetInstance().MakePoint2D(PMath::init(100, 100), Physics::BodyType::DYNAMIC));
	GLPhysX::RadialEmitter* em = new GLPhysX::RadialEmitter(Physics::PointFactory::GetInstance().MakeRadialEmitter2D(-1000, PMath::init(-100, 0)));


	GLPhysX::RigidTriangle* triangle_A = new GLPhysX::RigidTriangle(new Physics::Geometry::RigidTriangle(p1->Get(), p2->Get(), p3->Get()));
	GLPhysX::RigidTriangle* triangle_B = new GLPhysX::RigidTriangle(new Physics::Geometry::RigidTriangle(p2->Get(), p3->Get(), p4->Get()));
	
	// Add to engines
	engine->world->AddEntity(triangle_A->Get());
	engine->world->AddEntity(triangle_B->Get());
	engine->world->AddEntity(em->Get());
	
	// Add entitites to emitters
	em->Get()->AddObject(triangle_A->Get());
	em->Get()->AddObject(triangle_B->Get());

	// Add to renderer
	renderer->Add(triangle_A);
	renderer->Add(triangle_B);
		
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

	GLPhysX::VertexManager* vertex_manager = new GLPhysX::VertexManager(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLPhysX::IndexBufferManager* index_manager = new GLPhysX::IndexBufferManager();

	vertex_manager->AddVertex(p1->Get());
	vertex_manager->AddVertex(p2->Get());
	vertex_manager->AddVertex(p3->Get());
	vertex_manager->AddVertex(p4->Get());

	index_manager->AddIndex3D(p1->Get()->GetId(), p2->Get()->GetId(), p3->Get()->GetId());
	index_manager->AddIndex3D(p3->Get()->GetId(), p4->Get()->GetId(), p2->Get()->GetId());

	
	vertex_manager->GenerateArrays();
	GL::VertexBufferObject vb(vertex_manager->GetVertices(), vertex_manager->GetLength() * 3 * sizeof(float));
	vertex_manager->SpecifyLayout();

	GL::IndexBufferObject* ib = index_manager->GenerateIB();

	while (!glfwWindowShouldClose(window)) {
		const auto start_time = std::chrono::high_resolution_clock::now();

		// Draw everything here
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader->Bind();
		vertex_manager->Bind();
		ib->Bind();

		// Physics stuff
		engine->Run();

		// Update the graphics

		vb.UnBind();

		vertex_manager->UpdateVertices();

		vb.Bind();
		vb.SubData(vertex_manager->GetVertices(), vertex_manager->GetLength() * 3 * sizeof(float));

		// Draw
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
