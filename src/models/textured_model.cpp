#include "textured_model.h"

TexturedModel::TexturedModel(RawModel* _raw_model, ModelTexture* _model_texture)
: raw_model(_raw_model), model_texture(_model_texture)
{
}

TexturedModel::~TexturedModel()
{
}
