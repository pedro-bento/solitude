#include "terrain.h"
#include "../utilities/maths.h"

Terrain::Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack, TerrainTexture* _blendMap)
: texturePack(_texturePack),
  blendMap(_blendMap),
  heights(VERTEX_COUNT + 1, vector<float>(VERTEX_COUNT + 1))
{
  x = gridX * SIZE;
  z = gridZ * SIZE;

  raw_model = generateTerrain();
}

Terrain::~Terrain()
{
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
  float terrainX = worldX - x;
  float terrainZ = worldZ - z;
  float gridSquareSize = SIZE / (VERTEX_COUNT - 1);
  int gridX = (int)floor(terrainX/gridSquareSize);
  int gridZ = (int)floor(terrainZ/gridSquareSize);

  if(gridX >= VERTEX_COUNT - 1 || gridZ >= VERTEX_COUNT - 1 || gridX < 0 || gridZ < 0)
  {
    return 0;
  }

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
	int count = VERTEX_COUNT * VERTEX_COUNT;
	vector<GLfloat> vertices; vertices.resize(count * 3);
	vector<GLfloat> normals; normals.resize(count * 3);
	vector<GLfloat> textureCoords; textureCoords.resize(count*2);
	vector<unsigned short> indices; indices.resize(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
	int vertexPointer = 0;

	for(int z = 0; z < VERTEX_COUNT; z++)
  {
		for(int x = 0; x < VERTEX_COUNT; x++)
    {
			vertices[vertexPointer*3] = (GLfloat)x/((GLfloat)VERTEX_COUNT - 1) * SIZE;
      float height = noise.getPerlinNoise(x, z) * MAX_HEIGHT;
      heights[z][x] = height;
			vertices[vertexPointer*3+1] = height;
			vertices[vertexPointer*3+2] = (GLfloat)z/((GLfloat)VERTEX_COUNT - 1) * SIZE;
      vec3 normal = calculateNormal(x, z);
			normals[vertexPointer*3] = normal.x;
			normals[vertexPointer*3+1] = normal.y;
			normals[vertexPointer*3+2] = normal.z;
			textureCoords[vertexPointer*2] = (GLfloat)x/((GLfloat)VERTEX_COUNT - 1);
			textureCoords[vertexPointer*2+1] = (GLfloat)z/((GLfloat)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for(unsigned short gz=0; gz<VERTEX_COUNT-1; gz++)
  {
		for(unsigned short gx=0; gx<VERTEX_COUNT-1; gx++)
    {
			unsigned short topLeft = (gz*VERTEX_COUNT)+gx;
			unsigned short topRight = topLeft + 1;
			unsigned short bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
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
  float heightL = getHeight(x-1,z) / MAX_HEIGHT;
  float heightR = getHeight(x+1,z) / MAX_HEIGHT;
  float heightD = getHeight(x,z-1) / MAX_HEIGHT;
  float heightU = getHeight(x,z+1) / MAX_HEIGHT;
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
