#pragma once
#include "glm/glm.hpp"

class IntersectData {
private:
	const bool doesIntersect;
	const float distance;
	const glm::vec3 direction;
public:
	IntersectData();
	IntersectData(const bool intersects, const float dist, const glm::vec3 dir);
	~IntersectData();

	inline bool GetDoesIntersect() const { return doesIntersect; }
	inline float GetDistance() const { return distance; }
	inline glm::vec3 GetDirection() const { return direction; }
};