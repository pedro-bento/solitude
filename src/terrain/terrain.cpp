#include "terrain.h"

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

shared_ptr<RawModel> Terrain::generateTerrain()
{
		int count = VERTEX_COUNT * VERTEX_COUNT;
		vector<GLfloat> vertices;
    vertices.resize(count * 3);
		vector<GLfloat> normals;
    normals.resize(count * 3);
		vector<GLfloat> textureCoords;
    textureCoords.resize(count*2);
		vector<unsigned int> indices;
    indices.resize(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
		int vertexPointer = 0;
		for(int i=0;i<VERTEX_COUNT;i++){
			for(int j=0;j<VERTEX_COUNT;j++){
				vertices[vertexPointer*3] = (GLfloat)j/((GLfloat)VERTEX_COUNT - 1) * SIZE;
				vertices[vertexPointer*3+1] = 0;
				vertices[vertexPointer*3+2] = (GLfloat)i/((GLfloat)VERTEX_COUNT - 1) * SIZE;
				normals[vertexPointer*3] = 0;
				normals[vertexPointer*3+1] = 1;
				normals[vertexPointer*3+2] = 0;
				textureCoords[vertexPointer*2] = (GLfloat)j/((GLfloat)VERTEX_COUNT - 1);
				textureCoords[vertexPointer*2+1] = (GLfloat)i/((GLfloat)VERTEX_COUNT - 1);
				vertexPointer++;
			}
		}
		int pointer = 0;
		for(unsigned int gz=0;gz<VERTEX_COUNT-1;gz++){
			for(unsigned int gx=0;gx<VERTEX_COUNT-1;gx++){
				unsigned int topLeft = (gz*VERTEX_COUNT)+gx;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
				unsigned int bottomRight = bottomLeft + 1;
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
