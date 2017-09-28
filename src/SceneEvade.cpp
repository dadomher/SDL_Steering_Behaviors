#include "SceneEvade.h"

using namespace std;

SceneEvade::SceneEvade()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/zombie2.png", 8);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *enemy = new Agent;
	enemy->setPosition(Vector2D(500, 360));
	enemy->setTarget(agent->getPosition());
	//enemy->setMass(0.5);
	enemy->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(enemy);
}

SceneEvade::~SceneEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneEvade::update(float dtime, SDL_Event *event)
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
	//Human
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);

	//Zombie
	agents[1]->setTarget(agents[0]->getPosition());
	Vector2D steering_force_enemy = agents[1]->Behavior()->Evade(agents[1], agents[1]->getTarget(), agents[0]->getVelocity(), dtime);
	agents[1]->update(steering_force_enemy, dtime, event);
}

void SceneEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneEvade::getTitle()
{
	return "SDL Steering Behaviors :: Evade Demo";
}