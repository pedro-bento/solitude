#ifndef TEXTURED_MODEL_H
#define TEXTURED_MODEL_H

#include "raw_model.h"
#include "../textures/model_texture.h"
#include "../utilities/load.h"

#include <vector>
using namespace std;

class TexturedModel
{
	RawModel* raw_model;
	ModelTexture* model_texture;

public:
	TexturedModel(RawModel* _raw_model, ModelTexture* _model_texture);
	~TexturedModel();

  RawModel* getRawModel() { return raw_model; }
	ModelTexture* getModelTexture() { return model_texture; }
};

#endif // TEXTURED_MODEL_H
