#pragma once
#include "lua.hpp"
#include "luabridge.h"
#include "Component.h"
#include "Transform.h"

namespace Merlin {
	
	class PlayerController: public Component {
		public:
			
			PlayerController(LinkedList<GameObject>* objList,Physics* physObj);
			~PlayerController(void){}
				

			static const float MovePower;
			static const float JumpPower;
			static const float MaxVelo;
			static const float GravityPull;		

			bool canJump = true;

			LinkedList<GameObject>* physObjList;
			Physics* physicsHandlerObj;
			

			void ShootBalls();

			void MovePlayer(float forward, float sideways, bool jump);

			void Update(){}
			void Initialise(){}

			static void Register(lua_State* L);
			
	};
}
