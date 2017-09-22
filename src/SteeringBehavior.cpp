#include "SteeringBehavior.h"
#include <math.h>
#include <vector>
#include <iostream>


SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}


/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = target - agent->position;

	desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D seeringForce = desiredVelocity - agent->velocity;
	seeringForce /= agent->max_velocity;
	seeringForce *= agent->max_force;
	return seeringForce;

}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = agent->position - target;

	desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D seeringForce = desiredVelocity - agent->velocity;
	seeringForce /= agent->max_velocity;
	seeringForce *= agent->max_force;
	return seeringForce;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}


Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float dtime, float slowingRadius) {
	Vector2D desiredVelocity = target - agent->position;

	if (Vector2D::Distance(target, agent->position) > slowingRadius) {
		std::cout << Vector2D::Distance(target, agent->position);
		desiredVelocity.Normalize();
		desiredVelocity *= agent->max_velocity;

		Vector2D seeringForce = desiredVelocity - agent->velocity;
		seeringForce /= agent->max_velocity;
		seeringForce *= agent->max_force;
		return seeringForce;
	} else {

		float factor = (Vector2D::Distance(target, agent->position) / slowingRadius);

		desiredVelocity.Normalize();
		desiredVelocity *= agent->max_velocity * factor;

		Vector2D seeringForce = desiredVelocity - agent->velocity;
		seeringForce /= agent->max_velocity;
		seeringForce *= agent->max_force;
		return seeringForce;
	} 
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float dtime, float slowingRadius)
{
	return Arrive(agent, target->position, dtime, slowingRadius);
}