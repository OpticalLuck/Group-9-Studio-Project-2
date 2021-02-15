#include "Collision.h"
#include <sstream>
Collision::Collision(Vector3 position, float length, float width, float height):
	position(position),
	length(length),
	width(width),
	height(height)
{
}
bool Collision::TestRayOBBIntersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 aabb_min, Vector3 aabb_max, Mtx44 ModelMatrix, float& intersection_distance)
{
}
