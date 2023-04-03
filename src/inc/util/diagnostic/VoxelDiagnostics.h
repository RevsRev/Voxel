#pragma once

#include <util/diagnostic/Diagnostic.h>
#include <iostream>

class VoxelDiagnostics {

private:
	Diagnostic chunkGenTime{};
	Diagnostic bufferLoadTime{};
	Diagnostic frameRate{};

	VoxelDiagnostics() {}

public:
	void submitChunkGenTime(double time);
	void submitBufferLoadTime(double time);
	void submitFrameTime(double time);

	void dump();

	static VoxelDiagnostics& the();
};