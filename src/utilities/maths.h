#ifndef MATHS_H
#define MATHS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <cstdint>
#include <cmath>
using namespace std;

class FPPCamera;

mat4 createTransformationMatrix(vec3 translation, vec3 rotation, float scale);
mat4 createTransformationMatrix(vec2 translation, vec2 scale);
mat4 createViewMatrix(FPPCamera* camera);

// calculate barycentric coordinate on triangle
float baryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos);

// Lehmer pseudo random  number generator
namespace Random
{
  static uint32_t seed = 0;

  static void setSeed(uint32_t _seed){ seed = _seed; }
  static uint32_t getSeed(){ return seed; }

  static uint32_t random()
  {
    seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (int64_t)seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
  }

  static int randomInt(int min, int max)
  {
    return (random() % (max - min)) + min;
  }

  static float randomFloat(float min, float max)
  {
    return ((float)random() / (float)(0x7FFFFFFF)) * ((max - min)/2) + min;
  }
};

class PerlinNoise
{
private:
  uint32_t seed = 13487;
  int octaves = 2;
  float frequency = 0.3f;
  float amplitude = 1000.0f;
  float lacunarity = 1.0f;
  float presistence = 2.0f;

public:
  PerlinNoise() {}
  PerlinNoise(int _seed, int _octaves,
    float _frequency, float _amplitude,
    float _lacunarity, float _presistence)
  : seed((uint32_t)_seed), octaves(_octaves),
    frequency(_frequency), amplitude(_amplitude),
    lacunarity(_lacunarity), presistence(_presistence) {}

  float getPerlinNoise(int x, int z)
  {
    float total = 0.0f;
    float denom = 0.0f;
    float freq = frequency;
    float amp = amplitude;

    for(int i = 0; i < octaves; i++)
    {
      total += getInterpolatedNoise(abs(x) * freq, abs(z) * freq) * amp;
      denom += amp;

      freq *= lacunarity;
      amp *= presistence;
    }
    return total / denom;
  }

private:
  float getNoise(int x, int z)
  {
    Random::setSeed((uint32_t)x * 4931 + (uint32_t)z * 5827 + seed);
    return Random::randomFloat(-1.0f, 1.0f);
  }

  float getSmothNoise(int x, int z)
  {
    float corners = (getNoise(x-1,z-1) + getNoise(x+1,z-1) +
                     getNoise(x-1,z+1) + getNoise(x+1,z+1)) / 16.0f;
    float sides = (getNoise(x-1,z) + getNoise(x+1,z) +
                   getNoise(x,z-1) + getNoise(x,z+1)) / 8.0f;
    float center = getNoise(x,z) / 4.0f;
    return corners + sides + center;
  }

  float getInterpolatedNoise(float x, float z)
  {
    int intX = (int)x;
    int intZ = (int)z;
    float fractX = x - intX;
    float fractZ = z - intZ;

    float v1 = getSmothNoise(intX, intZ);
    float v2 = getSmothNoise(intX + 1, intZ);
    float v3 = getSmothNoise(intX, intZ + 1);
    float v4 = getSmothNoise(intX + 1, intZ + 1);

    float i1 = interpolate(v1, v2, fractX);
    float i2 = interpolate(v3, v4, fractX);

    return interpolate(i1, i2, fractZ);
  }

  float interpolate(float a, float b, float blend)
  {
    double theta = blend * 3.14159f;
    float f = (float)(1.0f - cos(theta)) * 0.5f;
    return a * (1.0f - f) + b * f;
  }

};

#endif
