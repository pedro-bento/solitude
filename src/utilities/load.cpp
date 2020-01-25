#include "load.h"

string readShaderFromFile(const char* filePath);
void compileShader(GLuint shaderID, string shaderCode);
GLuint createVAO();
GLuint bindDataBuffer(vector<GLfloat> data);
GLuint bindIndicesBuffer(vector<unsigned int> indices);

GLuint loadShader(const char* shaderPath, GLenum shader)
{
    GLuint shaderID = glCreateShader(shader);
    string shaderCode = readShaderFromFile(shaderPath);
    compileShader(shaderID, shaderCode);
	return shaderID;
}

shared_ptr<RawModel> loadRawModel(vector<GLfloat> vertices, vector<unsigned int> indices)
{
    return make_shared<RawModel>(
        createVAO(),
        bindDataBuffer(vertices),
        bindIndicesBuffer(indices),
        (GLsizei)indices.size());
}

shared_ptr<ModelTexture> loadModelTexture(vector<GLfloat> textureCoords, const char* texturePath)
{
    return make_shared<ModelTexture>(
      loadBMP(texturePath),
      bindDataBuffer(textureCoords));
}

shared_ptr<TexturedModel> loadTexturedModel(const char* objPath, const char* texturePath)
{
  vector<unsigned int> indices;
	vector<GLfloat> vertices;
	vector<GLfloat> uvs;
	vector<GLfloat> normals;
	if(!loadAssImp(objPath, indices, vertices, uvs, normals))
    fprintf(stderr, "Cloud not load: %s\n", objPath);

  return make_shared<TexturedModel>(
    loadRawModel(vertices, indices),
    loadModelTexture(uvs, texturePath));
}

GLuint loadBMP(const char* texturePath)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char* data;

    FILE* file;
    fopen_s(&file, texturePath, "rb");
    if(file == NULL)
    {
        fprintf(stderr, "Failed to open: %s\n", texturePath);
        return 0;
    }

    if(fread(header, 1, 54, file) != 54)
    {
        fprintf(stderr, "%s is not a BMP file.\n", texturePath);
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        fprintf(stderr, "%s is not a BMP file.\n", texturePath);
        fclose(file);
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0)
    {
        imageSize = width * height * 3;
    }

    if (dataPos == 0)
    {
        dataPos = 54;
    }

    data = new unsigned char[imageSize];

    if (!fread(data, 1, imageSize, file))
    {
        fprintf(stderr, "Could not read file: %s\n", texturePath);
        fclose(file);
        return 0;
    }

    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    delete[] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}

bool loadAssImp(const char * path,
	              vector<unsigned int> & indices,
	              vector<GLfloat> & vertices,
	              vector<GLfloat> & uvs,
                vector<GLfloat> & normals)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0);
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

GLuint bindIndicesBuffer(vector<unsigned int> indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return vboID;
}
