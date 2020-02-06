#include "terrain.h"
#include "../utilities/maths.h"
#include "../config.h"

Terrain::Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack,
  TerrainTexture* _blendMap, PerlinNoise* _noise)
: texturePack(_texturePack), blendMap(_blendMap),
  heights(config.bucketVertexCount, vector<float>(config.bucketVertexCount)),
  noise(_noise)
{
  x = gridX * config.bucketSize;
  z = gridZ * config.bucketSize;

  xOffset = gridX * (config.bucketVertexCount-1);
  zOffset = gridZ * (config.bucketVertexCount-1);

  raw_model = generateTerrain();
}

Terrain::~Terrain()
{
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
  float terrainX = worldX - x;
  float terrainZ = worldZ - z;
  float gridSquareSize = config.bucketSize / (config.bucketVertexCount - 1);
  int gridX = (int)floor(terrainX/gridSquareSize);
  int gridZ = (int)floor(terrainZ/gridSquareSize);

  float xCoord = fmod(terrainX,gridSquareSize)/gridSquareSize;
  float zCoord = fmod(terrainZ,gridSquareSize)/gridSquareSize;

  float answer;
  if(xCoord <= (1-zCoord)){
    answer = baryCentric(
      vec3(0, getHeight(gridX, gridZ),     0),
      vec3(1, getHeight(gridX + 1, gridZ), 0),
      vec3(0, getHeight(gridX, gridZ + 1), 1),
      vec2(xCoord, zCoord));
  }else{
    answer = baryCentric(
      vec3(1, getHeight(gridX + 1, gridZ),     0),
      vec3(1, getHeight(gridX + 1, gridZ + 1), 1),
      vec3(0, getHeight(gridX, gridZ + 1),     1),
      vec2(xCoord, zCoord));
  }

  return answer;
}

shared_ptr<RawModel> Terrain::generateTerrain()
{
	int count = config.bucketVertexCount * config.bucketVertexCount;
	vector<GLfloat> vertices(count * 3);
	vector<GLfloat> normals(count * 3);
	vector<GLfloat> textureCoords(count*2);
	vector<unsigned short> indices(6*(config.bucketVertexCount-1)*(config.bucketVertexCount-1));

	int vertexPointer = 0;
	for(int j = 0; j < config.bucketVertexCount; j++)
  {
		for(int i = 0; i < config.bucketVertexCount; i++)
    {
      float height = noise->getPerlinNoise(i+xOffset, j+zOffset) * config.bucketMaxHeight;
      heights[j][i] = height;

			vertices[vertexPointer*3] = (GLfloat)i / ((GLfloat)config.bucketVertexCount - 1) * config.bucketSize;
			vertices[vertexPointer*3+1] = height;
			vertices[vertexPointer*3+2] = (GLfloat)j / ((GLfloat)config.bucketVertexCount - 1) * config.bucketSize;

      vec3 normal = calculateNormal(i, j);
			normals[vertexPointer*3] = normal.x;
			normals[vertexPointer*3+1] = normal.y;
			normals[vertexPointer*3+2] = normal.z;

			textureCoords[vertexPointer*2] = (GLfloat)i / ((GLfloat)config.bucketVertexCount - 1);
			textureCoords[vertexPointer*2+1] = (GLfloat)j / ((GLfloat)config.bucketVertexCount - 1);

			vertexPointer++;
		}
	}

	int pointer = 0;
	for(unsigned short gz = 0; gz < config.bucketVertexCount-1; gz++)
  {
		for(unsigned short gx = 0; gx < config.bucketVertexCount-1; gx++)
    {
			unsigned short topLeft = (gz * config.bucketVertexCount) + gx;
			unsigned short topRight = topLeft + 1;
			unsigned short bottomLeft = ((gz + 1) * config.bucketVertexCount) + gx;
			unsigned short bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	return loadRawModel(vertices, indices, textureCoords, normals);
}

vec3 Terrain::calculateNormal(int x, int z)
{
  float heightL = getHeight(x-1,z) / config.bucketMaxHeight;
  float heightR = getHeight(x+1,z) / config.bucketMaxHeight;
  float heightD = getHeight(x,z-1) / config.bucketMaxHeight;
  float heightU = getHeight(x,z+1) / config.bucketMaxHeight;
  return normalize(vec3(heightL-heightR, 2.0f, heightD-heightU));
}

float Terrain::getHeight(int x, int z)
{
  x = x < 0 ? 0 : x;
	z = z < 0 ? 0 : z;
	x = x >= heights.size() ? heights.size() - 1 : x;
	z = z >= heights.size() ? heights.size() - 1 : z;
	return heights[z][x];
}
