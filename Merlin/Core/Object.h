#pragma once

namespace Merlin {
	class Object{
		private:
			int id;
			static int instances;
		public:
			Object();
			~Object();
			int GetID();

			//Comparison operand functions; they just use the object ID
			bool operator == (const Object& rightHandObject){ return (this->id == rightHandObject.id); }
			bool operator != (const Object& rightHandObject){ return (this->id != rightHandObject.id); }
	};
}
