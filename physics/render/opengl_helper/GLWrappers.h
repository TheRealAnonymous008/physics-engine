#ifndef GLWRAPPERS_H_INCLUDED
#define GLWRAPPERS_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "../../core/Object.h"
#include "../../core/points/Point.h"
#include "../../core/points/Emitter.h"
#include "../../core/points/RadialEmitter.h"
#include "../../core/geometry/Triangle.h"
#include "../../core/geometry/Line.h"
#include "../../core/geometry/Quad.h"

// Wrappers to render Physics Objects using OpenGL
namespace GLPhysX {

	class Object{
	public:
		Object() {
			
		}

		virtual void Render(unsigned long long int* index) {

		}
	};

	class Point : public GLPhysX::Object{
	private:
		Physics::Point* pt;
	public: 
		Point(Physics::Point* pt){
			this->pt = pt;
		}

		void Render(unsigned long long int* index) override{
			glDrawElementsBaseVertex(GL_POINTS, 1, GL_UNSIGNED_INT, NULL, *index);
			*index++;
		}

		Physics::Point* Get(){
			return this->pt;
		}
	};

	class Emitter : public GLPhysX::Object{
	private:
		Physics::Emitter* pt;

	public:
		Emitter(Physics::Emitter* pt){
			this->pt = pt;
		}

		void Render(unsigned long long int* index) override {
			glDrawElementsBaseVertex(GL_POINTS, 1, GL_UNSIGNED_INT, NULL, *index);
			*index++;
		}

		Physics::Emitter* Get() {
			return this->pt;
		}
	};


	class RadialEmitter : public GLPhysX::Object{
	private:
		Physics::RadialEmitter* pt;

	public:
		RadialEmitter(Physics::RadialEmitter* pt){
			this->pt = pt;
		}

		void Render(unsigned long long int* index) override {
			glDrawElementsBaseVertex(GL_POINTS, 1, GL_UNSIGNED_INT, NULL, *index);
			*index++;
		}

		Physics::RadialEmitter* Get() {
			return this->pt;
		}
	};

	class Triangle : public GLPhysX::Object{
	protected:
		Physics::Geometry::Triangle* triangle;

	public:
		Triangle(Physics::Geometry::Triangle* triangle){
			this->triangle = triangle;
		}

		void Render(unsigned long long int* index) override {
			glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, NULL, *index);
			*index+=3;
		}

		Physics::Geometry::Triangle* Get() {
			return this->triangle;
		}
	};

	class Line : public GLPhysX::Object {
	protected:
		Physics::Geometry::Line* line;

	public:
		Line(Physics::Geometry::Line* line) {
			this->line = line;
		}

		void Render(unsigned long long int* index) override {
			glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, NULL, *index);
			*index += 2;
		}

		Physics::Geometry::Line* Get() {
			return this->line;
		}
	};

	class Quad : public GLPhysX::Object {
	protected:
		Physics::Geometry::Quad* quad;

	public:
		Quad(Physics::Geometry::Quad* quad) {
			this->quad = quad;
		}

		void Render(unsigned long long int* index) override {
			glDrawElementsBaseVertex(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, NULL, *index);
			*index += 4;
		}

		Physics::Geometry::Quad* Get() {
			return this->quad;
		}
	};

}

#endif