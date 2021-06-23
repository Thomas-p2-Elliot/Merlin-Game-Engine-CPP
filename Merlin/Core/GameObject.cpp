#include "stdafx.h"
#include "LinkedList.h"
#include "GameObject.h"

namespace Merlin{
	
	//Name only constructor, name is set implicitly (PS: no transform component created)
	GameObject::GameObject(string name):name(name) {
		printf("Loading GameObject:[%d]:[%s] \n", this->GetID(), name.c_str());

		//Set active & tag value
		this->active = true; this->tag = "";
		//Create component list
		components = new LinkedList<Component>();
	}

	//Verbose Constructor
	GameObject::GameObject(
		string name,
		string tag,
		glm::vec3 position,
		glm::vec3 rotation,
		glm::vec3 scale
	) {
		printf("Loading GameObject:[%d]:[%s] \n", this->GetID(), name.c_str());

		//Set values from input & default values
		this->active = true; this->name = name;	this->tag = tag;
		components = new LinkedList<Component>();
		//Add default transform using inputs
		transform = new Transform(this, position, rotation, scale);
		transform->gameObject = this;
		//Add transform to component list
		components->Insert((Component*)transform);
	}

	//Deletes components list
	GameObject::~GameObject(){ delete components; }

	//Just sets active state
	void GameObject::Destroy(){ this->active = false; }

	//Runs initialise function on all components
	void GameObject::Initialise(){
		for(int i = 0; i < components->Count(); i++){ components->Get(i)->Initialise(); };
	}

	//Runs update function on all object components
	void GameObject::Update(){
		for(int i = 0; i < components->Count(); i++){ components->Get(i)->Update(); };
	}

	//Sets components game object value & adds component to gameobjects list
	void GameObject::AddComponent(Component* component){
		component->gameObject = this; components->Insert(component);
	}

	//Gets component by type
	/*template<typename T> Component* GameObject::GetComponent(){
		//Loop through component linked list
		for (int i = 0; i < components->Count(); i++){
			//Get component @ index i of list & if it matches given type then return it
			Component* component = components->Get(i);
			if (typeid(T) == typeid(*component)) return component;
		}

		//If we did not return already, no matching component was found, return null
		return NULL;
	}*/

	//Simple Getters
	std::string GameObject::GetName()		{ return name;		}
	std::string GameObject::GetTag()		{ return tag;			}
	bool		GameObject::IsActive()		{ return active;		}
	Transform*  GameObject::GetTransform()	{ return transform;	}

	//Simple setters
	void		GameObject::SetTag(std::string tag){ this->tag = tag;	}
}