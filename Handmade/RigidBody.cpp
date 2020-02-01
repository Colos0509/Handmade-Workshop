#include "Game.h"
#include "RigidBody.h"

//------------------------------------------------------------------------------------------------------
//static function that calculates gravitational force using a formula 
//------------------------------------------------------------------------------------------------------
glm::vec3 RigidBody::GravityForce(double mass_1, double mass_2, glm::vec3 distance)
{

	//the formula uses scalar values, so first the scalar value is calculated
	//and then applied to the normalised distance value passed, to retain direction
	double gravityForce = (GRAVITY * mass_1 * mass_2) / glm::length(distance) * glm::length(distance);
	return glm::normalize(distance) * (float)gravityForce;
	
}
//------------------------------------------------------------------------------------------------------
//static function that calculates torque force using a formula 
//------------------------------------------------------------------------------------------------------
glm::vec3 RigidBody::TorqueForce(glm::vec3 force, glm::vec3 contactPosition, glm::vec3 centreOfMass)
{

	//the result produces a vector, used for the rotation axis and torque magnitude
	return glm::cross(force, (centreOfMass - contactPosition));

}
//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
RigidBody::RigidBody()
{

	m_mass = 0.0;
	m_angle = 0.0;
	m_angMass = 0.0;
	m_angVelocity = 0.0;
	m_angAcceleration = 0.0;

	m_force = glm::vec3(0.0f);
	m_torque = glm::vec3(0.0f);
	m_position = glm::vec3(0.0f);
	m_velocity = glm::vec3(0.0f);
	m_acceleration = glm::vec3(0.0f);

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to angle variable 
//------------------------------------------------------------------------------------------------------
double& RigidBody::Angle()
{

	return m_angle;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to angular velocity variable 
//------------------------------------------------------------------------------------------------------
double& RigidBody::AngVelocity()
{

	return m_angVelocity;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to force variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& RigidBody::Force()
{

	return m_force;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to torque variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& RigidBody::Torque()
{

	return m_torque;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to position variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& RigidBody::Position()
{

	return m_position;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns reference to velocity variable 
//------------------------------------------------------------------------------------------------------
glm::vec3& RigidBody::Velocity()
{

	return m_velocity;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets mass of object
//------------------------------------------------------------------------------------------------------
void RigidBody::SetMass(double mass)
{

	m_mass = mass;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets angular mass of object
//------------------------------------------------------------------------------------------------------
void RigidBody::SetAngMass(double mass)
{

	m_angMass = mass;

}
//------------------------------------------------------------------------------------------------------
//function that updates acceleration, velocity and position of object
//------------------------------------------------------------------------------------------------------
void RigidBody::Update()
{

	//variables for storing old velocity values for 
	//both displacement and rotational calculations below
	double oldVel = 0.0;
	glm::vec3 oldVelocity;

	//calculate the movement and rotational acceleration
	//the latter uses the torque vector's magnitude for scalar calculations below
	if(m_mass > 0.0) m_acceleration = (m_force / (float)m_mass);
	if(m_angMass > 0.0) m_angAcceleration = glm::length(m_torque) / m_angMass;

	//calculate the new position using Euler Integration
	//this formula is frame independent and uses time for accurate calculations
	oldVelocity = m_velocity;
	m_velocity += m_acceleration * 0.16f; // ((float)Game::Instance()->GetElapsedTime() / 1000);
	m_position += (m_velocity + oldVelocity) * 0.5f * 0.16f; // ((float)Game::Instance()->GetElapsedTime() / 1000);

	//calculate the new rotational angle using Euler Integration
	//this formula is frame independent and uses time for accurate calculations	
	oldVel = m_angVelocity;
	m_angVelocity += m_angAcceleration * 0.16f; // Game::Instance()->GetElapsedTime() / 1000; //temp!
	m_angle += (m_angVelocity + oldVel) * 0.5 * 0.16f; // Game::Instance()->GetElapsedTime() / 1000; //temp!

}