#include "terrain.h"
#include "../utilities/maths.h"

Terrain::Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack, TerrainTexture* _blendMap)
: texturePack(_texturePack),
  blendMap(_blendMap)
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
    answer = barryCentric(
      vec3(0, heights[gridX * VERTEX_COUNT + gridZ], 0),
      vec3(1, heights[(gridX + 1) * VERTEX_COUNT + gridZ], 0),
      vec3(0, heights[gridX * VERTEX_COUNT + gridZ + 1], 1),
      vec2(xCoord, zCoord));
  }else{
    answer = barryCentric(
      vec3(1, heights[(gridX + 1) * VERTEX_COUNT + gridZ], 0),
      vec3(1, heights[(gridX + 1) * VERTEX_COUNT + gridZ + 1], 1),
      vec3(0, heights[gridX * VERTEX_COUNT + gridZ + 1], 1),
      vec2(xCoord, zCoord));
  }

  return answer;
}

float Terrain::fractal(size_t octaves, float x, float y)
{
  float output = 0.0f;
  float denom  = 0.0f;
  float frequency = mFrequency;
  float amplitude = mAmplitude;

  for (size_t i = 0; i < octaves; i++) {
      output += (amplitude * noise(x * frequency, y * frequency));
      denom += amplitude;

      frequency *= mLacunarity;
      amplitude *= mPersistence;
  }

  return (output / denom);
}

float Terrain::noise(float x, float y)
{
  float n0, n1, n2;
  const float F2 = 0.366025403f;
  const float G2 = 0.211324865f;

  float s = (x + y) * F2;
  float xs = x + s;
  float ys = y + s;
  int32_t i = fastfloor(xs);
  int32_t j = fastfloor(ys);

  float t = static_cast<float>(i + j) * G2;
  float X0 = i - t;
  float Y0 = j - t;
  float x0 = x - X0;
  float y0 = y - Y0;

  int32_t i1, j1;
  if(x0 > y0){
   i1 = 1;
   j1 = 0;
  }else{
   i1 = 0;
   j1 = 1;
  }

  float x1 = x0 - i1 + G2;
  float y1 = y0 - j1 + G2;
  float x2 = x0 - 1.0f + 2.0f * G2;
  float y2 = y0 - 1.0f + 2.0f * G2;

  int gi0 = hash(i + hash(j));
  int gi1 = hash(i + i1 + hash(j + j1));
  int gi2 = hash(i + 1 + hash(j + 1));

  float t0 = 0.5f - x0*x0 - y0*y0;
  if (t0 < 0.0f) {
     n0 = 0.0f;
  } else {
     t0 *= t0;
     n0 = t0 * t0 * grad(gi0, x0, y0);
  }

  float t1 = 0.5f - x1*x1 - y1*y1;
  if (t1 < 0.0f) {
     n1 = 0.0f;
  } else {
     t1 *= t1;
     n1 = t1 * t1 * grad(gi1, x1, y1);
  }

  float t2 = 0.5f - x2*x2 - y2*y2;
  if (t2 < 0.0f) {
     n2 = 0.0f;
  } else {
     t2 *= t2;
     n2 = t2 * t2 * grad(gi2, x2, y2);
  }

  return 45.23065f * (n0 + n1 + n2);
}

inline int32_t Terrain::fastfloor(float fp)
{
  int32_t i = static_cast<int32_t>(fp);
  return (fp < i) ? (i - 1) : (i);
}

inline uint8_t Terrain::hash(int32_t i) {
    return perm[static_cast<uint8_t>(i)];
}

float Terrain::grad(int32_t hash, float x, float y) {
    const int32_t h = hash & 0x3F;
    const float u = h < 4 ? x : y;
    const float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
}

shared_ptr<RawModel> Terrain::generateTerrain()
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
  heights.resize(count);
	vector<GLfloat> vertices; vertices.resize(count * 3);
	vector<GLfloat> normals; normals.resize(count * 3);
	vector<GLfloat> textureCoords; textureCoords.resize(count*2);
	vector<unsigned short> indices; indices.resize(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
	int vertexPointer = 0;
	for(int i=0;i<VERTEX_COUNT;i++){
		for(int j=0;j<VERTEX_COUNT;j++){
			vertices[vertexPointer*3] = (GLfloat)j/((GLfloat)VERTEX_COUNT - 1) * SIZE;
      float height = fractal(mOctaves, j, i) * MAX_HEIGHT;
      heights[j * VERTEX_COUNT + i] = height;
			vertices[vertexPointer*3+1] = height;
			vertices[vertexPointer*3+2] = (GLfloat)i/((GLfloat)VERTEX_COUNT - 1) * SIZE;
      vec3 normal = calculateNormal(j, i);
			normals[vertexPointer*3] = normal.x;
			normals[vertexPointer*3+1] = normal.y;
			normals[vertexPointer*3+2] = normal.z;
			textureCoords[vertexPointer*2] = (GLfloat)j/((GLfloat)VERTEX_COUNT - 1);
			textureCoords[vertexPointer*2+1] = (GLfloat)i/((GLfloat)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for(unsigned short gz=0;gz<VERTEX_COUNT-1;gz++){
		for(unsigned short gx=0;gx<VERTEX_COUNT-1;gx++){
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
  float heightL = fractal(mOctaves, x-1, z);
  float heightR = fractal(mOctaves, x+1, z);
  float heightD = fractal(mOctaves, x, z-1);
  float heightU = fractal(mOctaves, x, z+1);
  return normalize(vec3(heightL-heightR, 2.0f, heightD-heightU));
}
