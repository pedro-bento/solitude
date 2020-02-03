#include "maths.h"

mat4 createTransformationMatrix(vec3 translation, vec3 rotation, float scale)
{
	mat4 matrix(1.0f);
	matrix = translate(matrix, translation);
	matrix = rotate(matrix, radians(rotation.x), vec3(1, 0, 0));
	matrix = rotate(matrix, radians(rotation.y), vec3(0, 1, 0));
	matrix = rotate(matrix, radians(rotation.z), vec3(0, 0, 1));
	matrix = glm::scale(matrix, vec3(scale));
	return matrix;
}

mat4 createViewMatrix(FPPCamera* camera)
{
	vec3 direction(cos(camera->getPitch()) * sin(camera->getYaw()),
		sin(camera->getPitch()), cos(camera->getPitch()) * cos(camera->getYaw()));
	vec3 right(sin(camera->getYaw() - 3.14f / 2.0f), 0, cos(camera->getYaw() - 3.14f / 2.0f));
	vec3 up = cross(right, direction);
	return lookAt(camera->getPosition(), camera->getPosition() + direction, up);
}

float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos)
{
  float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
  float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
  float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
  float l3 = 1.0f - l1 - l2;
  return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
