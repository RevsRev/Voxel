#pragma once

#include <vector>

class MouseListener {
public:
	virtual void processMouseEvent(double xPos, double yPos) = 0;
};

class HasMouseListener {
private:
	std::vector<MouseListener*> listeners = std::vector<MouseListener*>{};

public:
	void addMouseListener(MouseListener* listener);
	void removeMouseListener(MouseListener* listener);
	void publishMouse(double xPos, double Pos);

};