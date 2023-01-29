#pragma once

#include <glad/glad.h>
#include <vector>

class KeyBoardListener {
public:
	virtual void processKeyEvent(int key, int scancode, int action, int mods) = 0;
};

class HasKeyBoardListener {
private:
	std::vector<KeyBoardListener*> listeners = std::vector<KeyBoardListener*>{};

public:
	void addKeyboardListener(KeyBoardListener* listener);
	void removeKeyboardListener(KeyBoardListener* listener);
	void publishKeyboard(int key, int scancode, int action, int mods);

};