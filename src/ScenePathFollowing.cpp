#include "ScenePathFollowing.h"

using namespace std;

ScenePathFollowing::ScenePathFollowing() {

	path[0] = Vector2D(400.f, 500.f);
	path[1] = Vector2D(600.f, 525.f);
	path[2] = Vector2D(700.f, 450.f);
	path[3] = Vector2D(850.f, 600.f);
	path[4] = Vector2D(1000.f, 425.f);
	path[5] = Vector2D(1200.f, 400.f);

	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->indexCurrentAgent = GetParameter(agent->getPosition());
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

ScenePathFollowing::~ScenePathFollowing() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

int ScenePathFollowing::GetParameter(Vector2D position) {
	int minId = 0;
	float minDist = Vector2D::Distance(position, path[0]);
	for (int i = 1; i < 6; i++) {
		if (Vector2D::Distance(position, path[i]) <= minDist) {
			minDist = Vector2D::Distance(position, path[i]);
			minId = i;
		}
	}

	return minId;
}

void ScenePathFollowing::update(float dtime, SDL_Event *event) {
	
	target = path[agents[0]->indexCurrentAgent];
	if (Vector2D::Distance(agents[0]->getPosition(), target) < 10.f) {
		agents[0]->indexCurrentAgent++;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], target, dtime);
	agents[0]->update(steering_force, dtime, event);
	
}

void ScenePathFollowing::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

	draw_circle(TheApp::Instance()->getRenderer(), path[0].x, path[0].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[1].x, path[1].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[2].x, path[2].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[3].x, path[3].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[4].x, path[4].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), path[5].x, path[5].y, 15, 255, 255, 255, 255);
}

const char* ScenePathFollowing::getTitle() {
	return "SDL Steering Behaviors :: Path Following Demo";
}