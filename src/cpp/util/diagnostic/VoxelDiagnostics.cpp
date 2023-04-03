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
	std::cout << "ChunkGenTime (ms): " << chunkGenTime.getAvg() << std::endl;
	std::cout << "BufferLoadTime (ms): " << bufferLoadTime.getAvg() << std::endl;
	std::cout << "Frame time (ms): " << frameRate.getAvg() << std::endl;
}

VoxelDiagnostics& VoxelDiagnostics::the() {
	static VoxelDiagnostics* diagnostics = new VoxelDiagnostics();
	return *diagnostics;
}