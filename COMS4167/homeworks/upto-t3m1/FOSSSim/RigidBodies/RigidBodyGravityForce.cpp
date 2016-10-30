#include "RigidBodyGravityForce.h"

RigidBodyGravityForce::RigidBodyGravityForce( const Vector2s& g )
: m_g(g)
{}

RigidBodyGravityForce::~RigidBodyGravityForce()
{}

bool RigidBodyGravityForce::isConservative() const
{
  return true;
}

scalar RigidBodyGravityForce::computePotentialEnergy( const std::vector<RigidBody>& rbs )
{
    scalar Ubody = 0.0;
    for( std::vector<RigidBody>::size_type i = 0; i < rbs.size(); ++i)
        Ubody -= rbs[i].getM() * m_g.dot(rbs[i].getX());
    return Ubody;
}

void RigidBodyGravityForce::computeForceAndTorque( std::vector<RigidBody>& rbs )
{
    for( std::vector<RigidBody>::size_type i = 0; i < rbs.size(); ++i)
    {
        rbs[i].getForce() += rbs[i].getM() * m_g;
        // gradient of angular vel with respect to regular vel is 0, so no torque
    }
    return;
}

RigidBodyForce* RigidBodyGravityForce::createNewCopy()
{
  return new RigidBodyGravityForce(m_g);
}
