#include <io/Mouse.h>

void HasMouseListener::addMouseListener(MouseListener* listener) {
	listeners.push_back(listener);
}

void HasMouseListener::removeMouseListener(MouseListener* listener) {
	for (int i = 0; i < listeners.size(); i++) {
		if (listeners.at(i) == listener) {
			listeners.erase(listeners.begin() + i);
			return;
		}
	}
}

void HasMouseListener::publishMouse(double xPos, double yPos) {
	for (int i = 0; i < listeners.size(); i++) {
		listeners.at(i)->processMouseEvent(xPos, yPos);
	}
}

