#pragma once
#include "glew.h"
#include "glut.h"
#include "glm.hpp"
#include "Object.h"
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Component.h"
#include "Transform.h"

using namespace std;

namespace Merlin {

    class GameObject: public Object {
        private: 
            //Vars
            bool         active;
            std::string  name;
            std::string  tag;
            Transform*   transform;
        public:
            //Vars
            GameObject*             next;
            LinkedList<Component>*  components;
            //Destructor
            ~GameObject();
            //Constructors
            GameObject(std::string objectName);
            GameObject(
                std::string name,
                std::string tag, 
                glm::vec3 position = glm::vec3(0, 0, 0),
                glm::vec3 rotation = glm::vec3(0, 0, 0),
                glm::vec3 scale    = glm::vec3(1, 1, 1)
            );
            //Funcs
            void        Initialise();
            void        Destroy();
            std::string GetName();
            std::string GetTag();
            bool        IsActive();
            void        SetTag(string objectTag);
            void        Update();
            void        AddComponent(Component* component);
            Transform*  GetTransform();
            //template<typename T> Component* GetComponent();

    };
}
