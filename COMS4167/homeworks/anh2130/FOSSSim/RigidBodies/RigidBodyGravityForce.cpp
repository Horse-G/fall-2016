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
  // COMPLETE THIS CODE
  return -1.0;
}

void RigidBodyGravityForce::computeForceAndTorque( std::vector<RigidBody>& rbs )
{
  // COMPLETE THIS CODE
  // for all rigid bodies i rbs[i].getForce()  += ... some force you compute ...
  //                        rbs[i].getTorque() += ... some torque you compute ...
}

RigidBodyForce* RigidBodyGravityForce::createNewCopy()
{
  return new RigidBodyGravityForce(m_g);
}
