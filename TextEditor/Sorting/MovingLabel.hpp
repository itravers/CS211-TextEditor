#ifndef MOVING_LABEL
#define MOVING_LABEL

#include <string>
#include "Vector2.hpp"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace TextEditorNamespace {
	class MovingLabel{
	private:
		string _text;
		Vector2 <float> _loc;
		Vector2 <float> _movingTo;
		Vector2 <float> _vel;

	public:
		MovingLabel(string text, Vector2<float> loc){
			_text = text;
			_loc = loc;
		}

		string getText() {
			return _text;
		}

		Vector2<float> getLoc() {
			return _loc;
		}

		Vector2<float> getVel() {
			return _vel;
		}

		void setVel(Vector2<float> vel) {
			_vel = vel;
		}

		void setMovingTo(Vector2<float> movingTo) {
			_movingTo = movingTo;
		}

		bool arrived() {
			bool returnVal = false;

			if (arrivedX() && arrivedY()) {
				returnVal = true;
			}

			return returnVal;
		}

		bool arrivedX() {
			int toX = _movingTo.x;
			int currX = _loc.x;
			bool returnVal = false;

			if (toX = currX) {
				//set vel.x to 0
				_vel.x = 0;
				returnVal = true;
			}

			return returnVal;
		}

		bool arrivedY() {
			int toY = _movingTo.y;
			int currY = _loc.y;
			bool returnVal = false;

			if (toY = currY) {
				//set vel.y to 0
				_vel.y = 0;
				returnVal = true;
			}

			return returnVal;
		}

		void update(float timeElapsed) {
			int startX = _loc.x;
			_loc = _loc + (_vel * timeElapsed);

			int endX = _loc.x;
			if (startX != endX) {
				int x = 0;
			}

			//cout << "update time elapsed: " << timeElapsed << endl;

			//check arrival, which will stop the movement if it has arrived.
			arrived();
		}
	};
}
#endif