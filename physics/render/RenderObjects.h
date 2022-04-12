#pragma once

#include "../core/points/Point.h"
#include "../core/points/Emitter.h"
#include "../core/points/RadialEmitter.h"

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
			shape.setPosition(r_x, r_y);
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
			shape.setPosition(r_x, r_y);
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
			shape.setPosition(r_x, r_y);
			shape.setFillColor(sf::Color::Yellow);
		}
	};
}