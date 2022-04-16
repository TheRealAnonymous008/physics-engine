#pragma once

#include "../core/points/Point.h"
#include "../core/points/Emitter.h"
#include "../core/points/RadialEmitter.h"
#include "../core/links/Spring.h"
#include "../core/links//HingeJoint.h"

#include <SFML/Graphics.hpp>

namespace Render {
	class Point : public Physics::Point {
	private:
		void OnUpdate() override {
			//Physics::Emitter::OnUpdate();
			move(this->transform.position.vec[0], this->transform.position.vec[1]);
		}

	public:
		sf::CircleShape shape = sf::CircleShape(5);

		void move(float x, float y) {
			this->transform.position = (PMath::init(x, y));
			float r_x = GetScaledPosition().vec[0];
			float r_y = GetScaledPosition().vec[1];
			shape.setPosition(r_x - 5, r_y - 5);
		}
	};


	class Emitter : public Physics::Emitter{
	private:
		void OnUpdate() override {
			//Physics::Emitter::OnUpdate();
			move(this->transform.position.vec[0], this->transform.position.vec[1]);
		}

	public:
		sf::CircleShape shape = sf::CircleShape(5);

		void move(float x, float y) {
			this->transform.position = (PMath::init(x, y));
			float r_x = GetScaledPosition().vec[0];
			float r_y = GetScaledPosition().vec[1];
			shape.setPosition(r_x - 5, r_y - 5);
			shape.setFillColor(sf::Color::Red);
		}
	};

	class RadialEmitter : public Physics::RadialEmitter{
	private:
		void OnUpdate() override {
			//Physics::Emitter::OnUpdate();
			move(this->transform.position.vec[0], this->transform.position.vec[1]);
		}

	public:
		sf::CircleShape shape = sf::CircleShape(5);

		void move(float x, float y) {
			this->transform.position = (PMath::init(x, y));
			float r_x = GetScaledPosition().vec[0];
			float r_y = GetScaledPosition().vec[1];
			shape.setPosition(r_x - 5, r_y - 5);
			shape.setFillColor(sf::Color::Yellow);
		}
	};

	class Spring : public Physics::Spring {
		using Physics::Spring::Spring;

	private:

	public:
		sf::Vertex* getShape() {
			float fx = first->transform.position.vec[0];
			float fy = first->transform.position.vec[1];
			float sx = second->transform.position.vec[0];
			float sy = second->transform.position.vec[1];

			sf::Vertex line[] = { sf::Vertex(sf::Vector2f(fx, fy)), sf::Vertex(sf::Vector2f(sx, sy))};
			return line;
		}
	};

	class HingeJoint : public Physics::HingeJoint {
		using Physics::HingeJoint::HingeJoint;

	private:

	public:
		sf::Vertex* getShape() {
			float fx = first->transform.position.vec[0];
			float fy = first->transform.position.vec[1];
			float sx = second->transform.position.vec[0];
			float sy = second->transform.position.vec[1];

			sf::Vertex line[] = { sf::Vertex(sf::Vector2f(fx, fy), sf::Color::Red), sf::Vertex(sf::Vector2f(sx, sy), sf::Color::Red) };

			return line;
		}
	};
}