#include "ScenePursue.h"

using namespace std;

ScenePursue::ScenePursue()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *enemy = new Agent;
	enemy->setPosition(Vector2D(300, 200));
	enemy->setTarget(agent->getPosition());
	enemy->loadSpriteTexture("../res/zombie2.png", 8);
	agents.push_back(enemy);
}

ScenePursue::~ScenePursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePursue::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
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
	Vector2D steering_force2 = agents[0]->Behavior()->Pursue(agents[1], agents[0], dtime);
	agents[0]->update(steering_force, dtime, event);
	agents[1]->update(steering_force2, dtime, event);
}

void ScenePursue::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

	agents[1]->draw();
}

const char* ScenePursue::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}