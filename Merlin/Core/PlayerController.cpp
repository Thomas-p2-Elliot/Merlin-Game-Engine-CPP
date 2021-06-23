#include "stdafx.h"
#include "PlayerController.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Physics.h"
#include "MeshRenderer.h"
#include "SphereMesh.h"
#include "Shader.h"
#include "Material.h"

namespace Merlin {

	//Player constructor
	PlayerController::PlayerController(LinkedList<GameObject>* objList, Physics* physObj){
		this->gameObject->SetPlayerController(this);
		this->canJump = true;
		this->physicsHandlerObj = physObj;
		this->physObjList = objList;
	}

	//Config of player
	const float PlayerController::JumpPower = 5;
	const float PlayerController::MaxVelo = 5;
	const float PlayerController::GravityPull = -1;
	const float PlayerController::MovePower = 2;

	//Shoots balls from player obj
	void PlayerController::ShootBalls(){

		//Create ball shader
		Shader *textureShader = new Shader("../Assets/Shaders/TexturedpointLight.vert", "../Assets/Shaders/TexturedPointLight.frag");

		//Create ball material
		Material * ballMaterial = new Material(textureShader, "../Assets/Textures/ball.bmp", Material::whiteMattMaterial);

		//Create ball
		GameObject * sphere = new GameObject("Sphere", "projectile", this->gameObject->GetTransform()->GetPosition(), glm::vec3(0, 0, 0), glm::vec3(15, 15, 15));
		sphere->AddComponent(new MeshRenderer(sphere, new SphereMesh(), ballMaterial));
		sphere->AddComponent(new RigidBody(sphere, new btSphereShape(btScalar(1.0)), this->physicsHandlerObj->GetPhysicsWorld(), 10));
		this->physObjList->Insert(sphere);

		//Add velocity to the ball, firing from the balls position
		sphere->GetRigidBody()->GetPhysicsRigidBody()->applyForce(btVector3(5,-5,5), btVector3(sphere->GetTransform()->GetPosition().x, sphere->GetTransform()->GetPosition().y, sphere->GetTransform()->GetPosition().z));
	}

	//Called from LUA, floats are acceleration values
	void PlayerController::MovePlayer(float forward, float sideways, bool jump){

		//Get object transform
		Transform* objTransform = this->gameObject->GetTransform();
	
		//Create current velocity value
		glm::vec3 velocity = glm::vec3(0,0,0);

		//Apply forward/backwards acceleration
		if (forward > 0){
			velocity.z += MovePower;	if(velocity.z > MaxVelo){ velocity.z = MaxVelo;	}
		} else {
			velocity.z -= MovePower;	if(velocity.z < -MaxVelo){ velocity.x = -MaxVelo; }
		}
		
		//Apply left/right acceleration
		if (sideways > 0){
			velocity.x += MovePower;	if(velocity.x > MaxVelo){ velocity.x = MaxVelo;	}
		} else {
			velocity.x -= MovePower;	if(velocity.x < -MaxVelo){ velocity.x = -MaxVelo; }
		}

		//Check if we can jump & want to jump
		if (this->canJump && jump){
			 velocity.y += JumpPower; //Apply jump power
		//Can't jump or does not want to jump, check if we are on the ground...
		} else if(objTransform->GetPosition().y <= 0.001) {
			canJump = true; //On ground, can jump again!
		//Not on ground, can jump is false OR jump command is false, apply gravity
		} else {
			velocity.y -= GravityPull;
		}

		//TODO: Modify velocity based on rotation

		//Apply velocity to position
		glm::vec3 curPos = objTransform->GetPosition();
		curPos.x = curPos.x + velocity.x * Physics::step;
		curPos.y = curPos.y + velocity.y * Physics::step;
		curPos.z = curPos.z + velocity.z * Physics::step;

		//Update position to new position
		objTransform->SetPosition(curPos);
	}

	void PlayerController::Register(lua_State* L) {
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<PlayerController>("PlayerController")
			.addFunction("MovePlayer", &PlayerController::MovePlayer)
			.endClass()
			.endNamespace();
	} 
}
