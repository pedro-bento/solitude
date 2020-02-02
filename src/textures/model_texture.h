#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

class ModelTexture
{
	GLuint textureID;
	float shineDamper = 1.0f;
	float reflectivity = 0.0f;
	bool hasTransparency = false;
	bool useFakeLighting = false;

public:
	ModelTexture(GLuint _textureID);
	~ModelTexture();

  GLuint getTextureID() { return textureID; }

	float getShineDamper() { return shineDamper; }
	float getReflectivity() { return reflectivity; }
	bool getHasTransparency() { return hasTransparency; }
	bool getUseFakeLighting() { return useFakeLighting; }

	void setShineDamper(float v) { shineDamper = v; }
	void setReflectivity(float v) { reflectivity = v; }
	void setHasTransparency(bool v) { hasTransparency = v; }
	void setUseFakeLighting(bool v) { useFakeLighting = v; }
};

#endif // MODEL_TEXTURE_H
