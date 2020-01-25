#include "textured_model.h"

TexturedModel::TexturedModel(shared_ptr<RawModel> _raw_model,
                             shared_ptr<ModelTexture> _model_texture)
: raw_model(_raw_model), model_texture(_model_texture)
{
}

TexturedModel::~TexturedModel()
{
}
