#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "../math/Vector.h"

namespace Physics {
	struct Transform {
		PMath::Vector position;
		PMath::Vector velocity;
		PMath::Vector acceleration;
	};

	class Object{ 
	public: 
		Transform transform;

		virtual void Update(float delta) {
			// Called per update 
		}

		virtual void OnFrameStart(float delta) {
			// Called at the start of a Physics frame.
		}

		virtual void OnFrameEnd(float delta){
			// Called at the end of a Physics frame.
		}

		virtual void OnUpdate(float delta) {
			// Called after an update
		}

	};
}

#endif 