#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <vector>
#include "../../core/Object.h"

namespace Physics {
	namespace Geometry {;

		class Shape :public Object {
		protected:
			std::vector<Object*> points;

			void AddPoint(Point* pt) {
				points.push_back(pt);
			}

		public:
			Shape() {
				points = std::vector<Object*>();
			}

			std::vector<Object*> GetPrimitives() {
				return points;
			}

			void Update(float delta) override{
				for (Object* pt : points) {
					pt->Update(delta);
				}
			}

			void OnFrameStart(float delta) override{
				for (Object* pt : points) {
					pt->OnFrameStart(delta);
				}
			}

			void OnFrameEnd(float delta) override {
				for (Object* pt : points) {
					pt->OnFrameEnd(delta);
				}
			}

			void OnUpdate(float delta) override{
				for (Object* pt : points) {
					pt->OnUpdate(delta);
				}
			}

			void ApplyForce(PMath::Vector force) override{
				// Apply the force to all primitives
				for (Object* pt : points) {
					pt->ApplyForce(force);
				}
			}

			void Cleanup() override {
				for (Object* pt : points) {
					pt->Cleanup();
				}
			}

			void SetType(BodyType type) override{
				for (Object* pt : points) {
					pt->SetType(type);
				}
			}


		};
	}
}

#endif

