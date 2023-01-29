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
	vboInstance = VBO();

	vboCube.setBufferData(cubeVerticesWithNormalAndTex, 8 * 6 * 6 * sizeof(float));

	Attribute* attrVertex = new Attribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	Attribute* attrNormal = new Attribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	Attribute* attrTex = new Attribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	Attribute* attrInst = new Attribute(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attrInst->setDivisor(1);

	vao.addVBO(&vboCube);
	vboCube.addAttribute(attrVertex);
	vboCube.addAttribute(attrNormal);
	vboCube.addAttribute(attrTex);
	vao.addVBO(&vboInstance);
	vboInstance.addAttribute(attrInst);
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

	std::vector<float>* vcs = chunk->getVoxelPositionsToRender();
	int size = vcs->size();
	float* voxelPositions = new float[size];
	for (int i = 0; i < size; i++) {
		voxelPositions[i] = vcs->at(i);
	}
	vboInstance.setBufferData(voxelPositions, vcs->size() * sizeof(float));

	shaderProgram.use();
	vao.bind();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, vcs->size() / 3);
}

ShaderProgram* ChunkRenderer::getShaderProgram() {
	return &shaderProgram;
}