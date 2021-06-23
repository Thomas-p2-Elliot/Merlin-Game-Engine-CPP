#pragma once
#include "Object.h"
#include "glm.hpp"
#include "matrix_transform.hpp"

namespace Merlin {
	class GameObject; //Prevent circular reference from inclusion

	class Component:public Object {
		public:
			GameObject* gameObject;
			Component*  next;
			Component(){};
			~Component();
			Component(GameObject* gameObject);
			virtual void Initialise() = 0;
			virtual void Update() = 0;
	};
}
