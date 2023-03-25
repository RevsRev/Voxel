#include <gui/Color.h>

glm::vec3* Color::getAsGlmVec3(unsigned char* red) {
	char r = *red;
	char g = *++red;
	char b = *++red;
	return new glm::vec3(r/255.0f, g/255.0f, b/ 255.0f);
}