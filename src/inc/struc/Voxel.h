#pragma once

//Keep as lightweight as possible, as there will be many of these.
struct Voxel {
public:
	char type;
	bool active = false;
};