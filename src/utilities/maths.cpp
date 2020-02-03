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
