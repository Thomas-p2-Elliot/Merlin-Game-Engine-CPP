#include "Light.h"
#include "GameObject.h"

namespace Merlin{

	//Pos 0, 100% on all values
	LightInfo Light::noonLight = {
		{ 0.00, 0.00, 0.00 },		//Pos
		{ 1.00, 1.00, 1.00, 1.00 }, //Ambient
		{ 1.00, 1.00, 1.00, 1.00 }, //Specular
		{ 1.00, 1.00, 1.00, 1.00 }  //Diffuse
	};

	//Pos 0, 50% on all values except alpha @ 100%
	LightInfo Light::duskLight = {
		{ 0.00, 0.00, 0.00 },		//Pos
		{ 0.50, 0.50, 0.50, 1.00 }, //Ambient
		{ 0.50, 0.50, 0.50, 1.00 }, //Specular
		{ 0.50, 0.50, 0.50, 1.00 }  //Diffuse
	};

	//Static value
	int Light::lightIndex = GL_LIGHT0;

	//Constructor
	Light::Light(GameObject * gameObject, LightInfo info) :Component(gameObject){
		index = lightIndex++;
		glEnable(index);
		properties = info;
	}

	//Destructor
	Light::~Light(void){}

	//Initialiser
	void Light::Initialise(){}

	//Returns light properties (LightInfo)
	LightInfo Light::GetProperties(){
		//Update position in case it has moved via its transform
		properties.position = gameObject->GetTransform()->GetPosition();
		return properties;
	}
	
	//Update
	void Light::Update(){
		// REMOVE BELOW WHEN MIGRATING TO DIRECT MODE
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		GLfloat light_pos[] = { position.x, position.y, position.z, 1.0 };
		glLightfv(index, GL_POSITION, light_pos);
		GLfloat ambient[] = { 0.2, 0.2, 0.2 };
		glLightfv(index, GL_AMBIENT, ambient);
		GLfloat specular[] = { 0.4, 0.4, 0.4 };
		glLightfv(index, GL_SPECULAR, specular);
		GLfloat diffuse[] = { 0.7, 0.7, 0.7 };
		glLightfv(index, GL_DIFFUSE, diffuse);
	}
}