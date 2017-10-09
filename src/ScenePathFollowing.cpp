#include "ScenePathFollowing.h"

using namespace std;

ScenePathFollowing::ScenePathFollowing() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	c1.pathArray[0] = { Vector2D(400.f, 500.f) };
	c1.pathArray[1] = { Vector2D(600.f, 525.f) }; 
	c1.pathArray[2] = { Vector2D(700.f, 450.f) };
	c1.pathArray[3] = { Vector2D(850.f, 600.f) };
	c1.pathArray[4] = { Vector2D(1000.f, 425.f) };
	c1.pathArray[5] = { Vector2D(1200.f, 400.f) };
}

ScenePathFollowing::~ScenePathFollowing() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

void ScenePathFollowing::update(float dtime, SDL_Event *event) {
	/* Keyboard & Mouse events */
	/*switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);*/

	switch (event->type) {
		target = c1.pathArray[agents[0]->indexCurrentAgent];
		if (Vector2D::Distance(agents[0]->getPosition, target) < 10.f) {
			parameter = GetParameter(agent.position);
			parameter += path_offset;
			currentTarget = GetPosition(parameter);
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
	
}

void ScenePathFollowing::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[0].x, c1.pathArray[0].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[1].x, c1.pathArray[1].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[2].x, c1.pathArray[2].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[3].x, c1.pathArray[3].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[4].x, c1.pathArray[4].y, 15, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), c1.pathArray[5].x, c1.pathArray[5].y, 15, 255, 255, 255, 255);
}

const char* ScenePathFollowing::getTitle() {
	return "SDL Steering Behaviors :: Path Following Demo";
}