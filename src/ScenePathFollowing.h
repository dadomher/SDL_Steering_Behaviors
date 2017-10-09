#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class ScenePathFollowing :
	public Scene
{
public:
	ScenePathFollowing();
	~ScenePathFollowing();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

struct Path {
	Vector2D pathArray[5];
} c1;

Vector2D GetPosition(float parameter) {
	return c1.pathArray[parameter];
}