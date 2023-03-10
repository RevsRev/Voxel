# include "gui/draw/ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(Chunk* chunk) {
	this->chunk = chunk;
	init();
}

//ChunkRenderer::~ChunkRenderer() {
//}

void ChunkRenderer::init() {
	initVao();
	initShaderProgram();
}

void ChunkRenderer::initVao() {
	vao = VAO();
	vao.init();

	vboCube = VBO();
	vboCube.init();

	vboPositionInstance = VBO();
	vboPositionInstance.init();

	vboColorInstance = VBO();
	vboColorInstance.init();

	vboCube.setBufferData(cubeVerticesWithNormalAndTex, 8 * 6 * 6 * sizeof(float));

	Attribute attrVertex = Attribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	Attribute attrNormal = Attribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	Attribute attrTex = Attribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	Attribute attrPositionInstance = Attribute(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attrPositionInstance.setDivisor(1);
	Attribute attributeColorInstance = Attribute(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attributeColorInstance.setDivisor(1);

	vao.addVBO(&vboCube);
	vboCube.addAttribute(&attrVertex);
	vboCube.addAttribute(&attrNormal);
	vboCube.addAttribute(&attrTex);
	vao.addVBO(&vboPositionInstance);
	vboPositionInstance.addAttribute(&attrPositionInstance);
	vao.addVBO(&vboColorInstance);
	vboColorInstance.addAttribute(&attributeColorInstance);
}

void ChunkRenderer::initShaderProgram() {

	std::string fragShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\fragment\\voxel.txt";
	std::string vertexShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\vertex\\voxel.txt";
	const char* fragShaderCStr = fragShaderPath.c_str();
	const char* vertexShaderCStr = vertexShaderPath.c_str();
	Shader* fragShader = Shader::fromFile(fragShaderCStr, GL_FRAGMENT_SHADER);
	Shader* vertexShader = Shader::fromFile(vertexShaderCStr, GL_VERTEX_SHADER);

	shaderProgram = ShaderProgram();
	shaderProgram.addShader(fragShader);
	shaderProgram.addShader(vertexShader);
	shaderProgram.compile();

	delete fragShader;
	delete vertexShader;
}

void ChunkRenderer::render() {

	std::pair<long, float*> positions = chunk->getVoxelPositionsToRender();
	vboPositionInstance.setBufferData(positions.second, positions.first * sizeof(float));

	std::pair<long, float*> colors = chunk->getVoxelColorsToRender();
	vboColorInstance.setBufferData(colors.second, colors.first * sizeof(float));

	shaderProgram.use();
	vao.bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, positions.first / 3);
}

ShaderProgram* ChunkRenderer::getShaderProgram() {
	return &shaderProgram;
}