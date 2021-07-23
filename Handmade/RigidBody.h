#pragma once

/*===================================================================#
| 'RigidBody' source files last updated on 23 July 2021              |
#===================================================================*/

#include "glad.h"
#include <glm.hpp>

const GLdouble GRAVITY = 1.0000000000667;

class RigidBody
{

public:

	static glm::vec3 GravityForce(GLdouble mass_1,
		GLdouble mass_2, const glm::vec3& distance);
	static glm::vec3 TorqueForce(const glm::vec3& force,
		const glm::vec3& contactPosition, const glm::vec3& centreOfMass);

	RigidBody();

	GLdouble GetAngle() const;
	GLdouble GetAngularVelocity() const;

	const glm::vec3& GetForce() const;
	const glm::vec3& GetTorque() const;
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetVelocity() const;

	void SetMass(GLdouble mass);
	void SetAngle(GLdouble angle);
	void SetAngularMass(GLdouble mass);
	void SetAngularVelocity(GLdouble velocity);

	void SetForce(const glm::vec3& force);
	void SetTorque(const glm::vec3& torque);
	void SetPosition(const glm::vec3& position);
	void SetVelocity(const glm::vec3& velocity);

	void Update();

private:

	GLdouble m_mass;
	GLdouble m_angle;
	GLdouble m_angularMass;
	GLdouble m_angularVelocity;
	GLdouble m_angularAcceleration;

	glm::vec3 m_force;
	glm::vec3 m_torque;
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

};