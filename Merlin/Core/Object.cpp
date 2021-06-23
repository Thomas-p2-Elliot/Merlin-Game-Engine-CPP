#include "stdafx.h"
#include "Object.h"

namespace Merlin {

	//Instances is a counter not an index, first object will have index 1
	int Object::instances = 0;

	//Returns object ID
	int Object::GetID(){ return this->id; }

	//Sets object ID on creation
	Object::Object(){ instances++;	this->id = instances; }

	//Destroys object
	Object::~Object(){ }
}
