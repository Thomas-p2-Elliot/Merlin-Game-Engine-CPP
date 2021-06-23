#pragma once
#include "LinkedList.h"
#include "GameObject.h"
#include "Graphics.h"

namespace Merlin{
	class Level {
		private:
			string name;
			LinkedList<GameObject> * gameObjects;
		public:
			Level(){};
			Level(string name);
			~Level(void);
			void Initialise();
			void Update();
			std::string GetName();
	};
}