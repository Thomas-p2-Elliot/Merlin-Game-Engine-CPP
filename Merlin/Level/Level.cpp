#include "stdafx.h"
#include "Level.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "CubeMesh.h"


namespace Merlin {

	//Default camera position
	const glm::vec3 DefaultCameraPos(0,0,450);
	//Default Camera Clip Planes
	const float DefaultNearClipPlane = 0.1;
	const float DefaultFarClipPlane = 10000.0;

	//Constructor
	Level::Level(string name){
		//Set Name from Input
		this->name = name;

		//Create object list
		gameObjects = new LinkedList<GameObject>();

		//Create Shader
		Shader *materialShader = new Shader("Assets/Shaders/PointLight.vert", "Assets/Shaders/PointLight.frag");
		Material * redMaterial = new Material(materialShader, NULL, Material::redPlasticMaterial);

		//Create Main Camera (name Main Camera, tag camera) @ pos 3,3,3
		GameObject * camera = new GameObject("Main Camera", "camera", DefaultCameraPos);

		//Create camera component on 'camera' object, use near & far clip plane args
		Camera * cameraComponent = new Camera(camera, DefaultNearClipPlane, DefaultFarClipPlane);
		//Add component to the camera
		camera->AddComponent(cameraComponent);
		// Assign primary camera in graphics
		Graphics::SetMainCamera(cameraComponent);

		//Lighting only appears to work when first in the list for updating!!!
		GameObject * light = new GameObject("Light", "light", glm::vec3(0, 0, 100));
		Light * lightComponent = new Light(light, Light::duskLight);
		light->AddComponent(lightComponent);
		this->gameObjects->Insert(light);
		Graphics::SetLight(lightComponent);

		//Add Box
		GameObject * box = new GameObject("box", "level", glm::vec3(180.0, -90.0, -100.0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 50));
		box->AddComponent(new MeshRenderer(box, new CubeMesh(), redMaterial));
		gameObjects->Insert(box);

	}

	//Destructor deletes levels objects
	Level::~Level(void){ delete this->gameObjects; }

	//Level initialiser, initialises all objects in the level (incl. the main camera)
	void Level::Initialise(){
		//	Initialise all game objects
		//Get first obj
		GameObject *obj = this->gameObjects->first;
		//Iterate through linked list until no next obj found
		while (obj != NULL){ obj->Initialise(); obj = obj->next; }
		//Initialise camera
		Graphics::GetMainCamera()->Initialise();
	}

	//Level updater
	void Level::Update(){
		//Update the camera first
		Graphics::GetMainCamera()->gameObject->Update();
		//	Update all game objects within level (this also updates their components)
		//Get first obj
		GameObject *obj = this->gameObjects->first;
		//Iterate through objects running their update function and deleting inactive objects
		while (obj != NULL){
			//Run object update (also updates components)
			obj->Update();
			//Remove inactive GameObjects
			if (!obj->IsActive()){
				//Delete object from list
				this->gameObjects->Delete(obj);
				//Create temp pointer to next obj
				GameObject *temp = obj->next;
				//Delete inactive object
				delete obj;
				//Set obj as next (next-next?) obj
				obj = temp->next;
			} else {
				//Get next obj
				obj = obj->next;
			}
		}
	}

	//Returns level name
	std::string Level::GetName(){ return this->name; }
}