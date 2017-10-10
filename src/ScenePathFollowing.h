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
	int GetParameter(Vector2D position);
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D path[6];
};