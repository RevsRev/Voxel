#pragma once

#include <util/diagnostic/RollingAvg.h>
#include <iostream>

class VoxelDiagnostics {

private:
	RollingAvg chunkGenTime{};
	RollingAvg bufferLoadTime{};
	RollingAvg frameRate{};

	VoxelDiagnostics() {}

public:
	void submitChunkGenTime(double time);
	void submitBufferLoadTime(double time);
	void submitFrameTime(double time);

	void dump();

	static VoxelDiagnostics& the();
};