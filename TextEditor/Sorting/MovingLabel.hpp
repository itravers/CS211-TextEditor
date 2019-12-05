#ifndef MOVING_LABEL
#define MOVING_LABEL

#include <string>
#include "Vector2.hpp"

using std::string;

namespace TextEditorNamespace {
	class MovingLabel{
	private:
		string _text;
		Vector2 <float> _loc;
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

		void update(float timeElapsed) {
			int startX = _loc.x;
			_loc = _loc + (_vel * timeElapsed);

			int endX = _loc.x;
			if (startX != endX) {
				int x = 0;
			}
		}
	};
}
#endif