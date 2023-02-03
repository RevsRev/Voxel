# include "gui/draw/ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(Chunk* chunk) {
	this->chunk = chunk;
	init();
}

void ChunkRenderer::init() {
	initVao();
	initShaderProgram();
}

void ChunkRenderer::initVao() {
	vao = VAO();
	vboCube = VBO();
	vboPositionInstance = VBO();
	vboColorInstance = VBO();

	vboCube.setBufferData(cubeVerticesWithNormalAndTex, 8 * 6 * 6 * sizeof(float));

	Attribute* attrVertex = new Attribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	Attribute* attrNormal = new Attribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	Attribute* attrTex = new Attribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	Attribute* attrPositionInstance = new Attribute(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attrPositionInstance->setDivisor(1);
	Attribute* attributeColorInstance = new Attribute(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attributeColorInstance->setDivisor(1);

	vao.addVBO(&vboCube);
	vboCube.addAttribute(attrVertex);
	vboCube.addAttribute(attrNormal);
	vboCube.addAttribute(attrTex);
	vao.addVBO(&vboPositionInstance);
	vboPositionInstance.addAttribute(attrPositionInstance);
	vao.addVBO(&vboColorInstance);
	vboColorInstance.addAttribute(attributeColorInstance);
}

void ChunkRenderer::initShaderProgram() {

	std::string fragShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\fragment\\voxel.txt";
	std::string vertexShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\vertex\\voxel.txt";
	Shader* fragShader = Shader::fromFile(fragShaderPath.c_str(), GL_FRAGMENT_SHADER);
	Shader* vertexShader = Shader::fromFile(vertexShaderPath.c_str(), GL_VERTEX_SHADER);

	shaderProgram = ShaderProgram();
	shaderProgram.addShader(fragShader);
	shaderProgram.addShader(vertexShader);
	shaderProgram.compile();
}

void ChunkRenderer::render() {

	//TODO - REFACTOR - should actually cache these vectors somewhere.
	std::vector<float>* vcs = chunk->getVoxelPositionsToRender();
	int size = vcs->size();
	float* voxelPositions = new float[size];
	for (int i = 0; i < size; i++) {
		voxelPositions[i] = vcs->at(i);
	}
	vboPositionInstance.setBufferData(voxelPositions, vcs->size() * sizeof(float));
	delete[] voxelPositions;

	std::vector<float>* colors = chunk->getVoxelColorsToRender();
	int colorsSize = colors->size();
	float* voxelColors = new float[colorsSize];
	for (int i = 0; i < colorsSize; i++) {
		voxelColors[i] = colors->at(i);
	}
	vboColorInstance.setBufferData(voxelColors, colors->size() * sizeof(float));
	delete[] voxelColors;

	shaderProgram.use();
	vao.bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, vcs->size() / 3);
}

ShaderProgram* ChunkRenderer::getShaderProgram() {
	return &shaderProgram;
}