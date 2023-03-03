#include <phys/Player.h>

Player::Player(double x, double y, double z) : GameObject(x, y, z) {
}

void Player::processKeyEvent(int key, int scanCode, int action, int mods) {
	//playerCam.processKeyEvent(key, scanCode, action, mods);
}
void Player::processMouseEvent(double xPos, double yPos) {
	//playerCam.processMouseEvent(xPos, yPos);
}