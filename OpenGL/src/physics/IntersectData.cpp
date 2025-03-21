#include "IntersectData.h"

IntersectData::IntersectData()
	: doesIntersect(false), distance(0.0f)
{
}

IntersectData::IntersectData(const bool intersects, const float dist, const glm::vec3 dir)
	: doesIntersect(intersects), distance(dist), direction(dir)
{

}

IntersectData::~IntersectData()
{
}
