#ifndef TEXTURED_MODEL_H
#define TEXTURED_MODEL_H

#include "raw_model.h"
#include "../textures/model_texture.h"

#include <vector>
#include <memory>
using namespace std;

class TexturedModel
{
	shared_ptr<RawModel> raw_model;
	shared_ptr<ModelTexture> model_texture;

public:
	TexturedModel(shared_ptr<RawModel> _raw_model,
								shared_ptr<ModelTexture> _model_texture);
	~TexturedModel();

  shared_ptr<RawModel> getRawModel() { return raw_model; }
	shared_ptr<ModelTexture> getModelTexture() { return model_texture; }
};

#endif // TEXTURED_MODEL_H
