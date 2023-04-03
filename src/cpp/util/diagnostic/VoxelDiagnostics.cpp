#include <util/diagnostic/VoxelDiagnostics.h>

void VoxelDiagnostics::submitChunkGenTime(double time) {
	chunkGenTime.submit(time);
}
void VoxelDiagnostics::submitBufferLoadTime(double time) {
	bufferLoadTime.submit(time);
}
void VoxelDiagnostics::submitFrameTime(double time) {
	frameRate.submit(time);
}

void VoxelDiagnostics::dump() {
	std::cout << "ChunkGenTime:: ";
	chunkGenTime.dump();
	std::cout << std::endl;

	std::cout << "BufferLoadTime:: ";
	bufferLoadTime.dump();
	std::cout << std::endl;

	std::cout << "Frame time:: ";
	frameRate.dump();
	std::cout << std::endl;
}

VoxelDiagnostics& VoxelDiagnostics::the() {
	static VoxelDiagnostics* diagnostics = new VoxelDiagnostics();
	return *diagnostics;
}