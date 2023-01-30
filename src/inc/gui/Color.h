#pragma once

#include <glm/vec3.hpp>

namespace Color {
	static unsigned char BROWN[]{80, 35, 12};
	static unsigned char WHITE[]{ 255,255,255 };
	static unsigned char GREY[]{40,40,40};

	extern glm::vec3* getAsGlmVec3(unsigned char* red);
}