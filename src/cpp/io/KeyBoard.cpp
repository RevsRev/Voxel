#include "io/KeyBoard.h"

void HasKeyBoardListener::addKeyboardListener(KeyBoardListener* listener) {
	listeners.push_back(listener);
}

void HasKeyBoardListener::removeKeyboardListener(KeyBoardListener* listener) {
	for (int i = 0; i < listeners.size(); i++) {
		if (listeners.at(i) == listener) {
			listeners.erase(listeners.begin() + i);
			return;
		}
	}
}

void HasKeyBoardListener::publishKeyboard(int key, int scancode, int action, int mods) {
	for (int i = 0; i < listeners.size(); i++) {
		listeners.at(i)->processKeyEvent(key, scancode, action, mods);
	}
}