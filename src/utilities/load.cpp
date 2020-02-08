#include "load.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

string readShaderFromFile(const char* filePath);
void compileShader(GLuint shaderID, string shaderCode);
GLuint createVAO();
GLuint bindDataBuffer(vector<GLfloat> data);
GLuint bindIndicesBuffer(vector<unsigned short> indices);

GLuint loadShader(const char* shaderPath, GLenum shader)
{
    GLuint shaderID = glCreateShader(shader);
    string shaderCode = readShaderFromFile(shaderPath);
    compileShader(shaderID, shaderCode);
	return shaderID;
}

shared_ptr<RawModel> loadRawModel(
  vector<GLfloat> vertices, vector<unsigned short> indices,
  vector<GLfloat> uvs, vector<GLfloat> normals)
{
    return make_shared<RawModel>(
        createVAO(),
        bindDataBuffer(vertices),
        bindIndicesBuffer(indices),
        bindDataBuffer(uvs),
        bindDataBuffer(normals),
        (GLsizei)indices.size());
}

SimpleModel loadSimpleModel(vector<GLfloat> vertices, int dimentions)
{
  return SimpleModel(
    createVAO(),
    bindDataBuffer(vertices),
    (GLsizei)(vertices.size()/dimentions));
}

shared_ptr<ModelTexture> loadModelTexture(const char* texturePath)
{
    return make_shared<ModelTexture>(loadDDS(texturePath));
}

shared_ptr<TexturedModel> loadTexturedModel(const char* objPath, const char* texturePath)
{
  vector<unsigned short> indices;
	vector<GLfloat> vertices;
	vector<GLfloat> uvs;
	vector<GLfloat> normals;
	if(!loadAssImp(objPath, indices, vertices, uvs, normals))
    fprintf(stderr, "Cloud not load: %s\n", objPath);

  return make_shared<TexturedModel>(
    loadRawModel(vertices, indices, uvs, normals),
    loadModelTexture(texturePath));
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char * imagepath)
{
	unsigned char header[124];

  FILE* fp;
  fopen_s(&fp, imagepath, "rb");
	if (fp == NULL){
		printf("%s could not be opened.\n", imagepath);
		return 0;
	}

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	fread(&header, 124, 1, fp);

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);

	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width  /= 2;
		height /= 2;

		if(width < 1) width = 1;
		if(height < 1) height = 1;
	}

	free(buffer);

	return textureID;
}

bool loadAssImp(const char * path,
	              vector<unsigned short> & indices,
	              vector<GLfloat> & vertices,
	              vector<GLfloat> & uvs,
                vector<GLfloat> & normals)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,
    aiProcess_Triangulate | aiProcess_FlipUVs);
	if(!scene)
  {
		fprintf(stderr, importer.GetErrorString());
		return false;
	}

	const aiMesh* mesh = scene->mMeshes[0];

	vertices.reserve(mesh->mNumVertices*3);
	for(unsigned int i=0; i<mesh->mNumVertices; i++)
  {
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.z);
	}

	uvs.reserve(mesh->mNumVertices*2);
	for(unsigned int i=0; i<mesh->mNumVertices; i++)
  {
		aiVector3D UVW = mesh->mTextureCoords[0][i];
		uvs.push_back(UVW.x);
    uvs.push_back(UVW.y);
	}

	normals.reserve(mesh->mNumVertices*3);
	for(unsigned int i=0; i<mesh->mNumVertices; i++)
  {
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(n.x);
    normals.push_back(n.y);
    normals.push_back(n.z);
	}

	indices.reserve(mesh->mNumFaces*3);
	for (unsigned int i=0; i<mesh->mNumFaces; i++)
  {
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}

	return true;
}

GLuint loadCubeMap(vector<char*> texturePath)
{
  GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width;
  int height;
  int n;
  unsigned char* data;

  for(int i = 0; i < 6; i++)
  {
    data = stbi_load(texturePath[i], &width, &height, &n, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
      (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}

string readShaderFromFile(const char* filePath)
{
	string shaderCode;
	ifstream shaderStream(filePath, ios::in);

	if (shaderStream.is_open())
	{
		stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		fprintf(stderr, "Failed to open %s\n", filePath);
    cin.get();
	}

	return shaderCode;
}

void compileShader(GLuint shaderID, string shaderCode)
{
	const GLchar* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, 0);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> shaderErrorMessage((size_t)infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		glDeleteShader(shaderID);
		fprintf(stderr, "Failed to compile shader %s\n", &shaderErrorMessage[0]);
    cin.get();
	}

}

GLuint createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	return vaoID;
}

GLuint bindDataBuffer(vector<GLfloat> data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboID;
}

GLuint bindIndicesBuffer(vector<unsigned short> indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return vboID;
}
