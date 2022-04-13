#ifndef SPRING_H_INCLUDED
#define SPRING_H_INCLUDED

#include "../Object.h"

namespace Physics {
	class Spring : public Object{
	protected:
		Object* first; 
		Object* second;

	public:
		Spring(Object* first, Object* second) {
			this->first = first;
			this->second = second;
		}

		
	};
}


#endif