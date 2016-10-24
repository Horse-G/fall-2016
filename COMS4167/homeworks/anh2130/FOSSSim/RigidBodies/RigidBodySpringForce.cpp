#include "RigidBodySpringForce.h"

RigidBodySpringForce::RigidBodySpringForce( const scalar& k, const scalar& l0, int rb0, const Vector2s& vc0, int rb1, const Vector2s& vc1 )
: m_k(k)
, m_l0(l0)
, m_rb0(rb0)
, m_rb1(rb1)
, m_vc0(vc0)
, m_vc1(vc1)
{
  assert( m_k >= 0.0 );
  assert( m_l0 >= 0.0 );
  assert( m_rb0 >= -1 );
  assert( m_rb1 >= -1 );
}

RigidBodySpringForce::~RigidBodySpringForce()
{
}

bool RigidBodySpringForce::isConservative() const
{
  return true;
}

int RigidBodySpringForce::getFirstRigidBody() const
{
  return m_rb0;
}

int RigidBodySpringForce::getSecondRigidBody() const
{
  return m_rb1;
}

const Vector2s& RigidBodySpringForce::getFirstEndpoint() const
{
  return m_vc0;
}

const Vector2s& RigidBodySpringForce::getSecondEndpoint() const
{
  return m_vc1;
}


bool RigidBodySpringForce::firstEndpointIsFixed() const
{
  return m_rb0 == -1;
}

bool RigidBodySpringForce::secondEndpointIsFixed() const
{
  return m_rb1 == -1;
}  

Vector2s RigidBodySpringForce::computeFirstEndpoint( const std::vector<RigidBody>& rbs ) const
{
  assert( m_rb0 >= -1 ); assert( m_rb0 < (int) rbs.size() );
  // If the endpoint is fixed, we store its world space position. Otherwise we must compute the world space position.
  return firstEndpointIsFixed() ? m_vc0 : rbs[m_rb0].computeWorldSpacePosition(m_vc0);
}

Vector2s RigidBodySpringForce::computeSecondEndpoint( const std::vector<RigidBody>& rbs ) const
{
  assert( m_rb1 >= -1 ); assert( m_rb1 < (int) rbs.size() );
  // If the endpoint is fixed, we store its world space position. Otherwise we must compute the world space position.
  return secondEndpointIsFixed() ? m_vc1 : rbs[m_rb1].computeWorldSpacePosition(m_vc1);
}

scalar RigidBodySpringForce::computePotentialEnergy( const std::vector<RigidBody>& rbs )
{
  assert( m_rb0 >= -1 ); assert( m_rb0 < (int) rbs.size() );
  assert( m_rb1 >= -1 ); assert( m_rb1 < (int) rbs.size() );
  
  // COMPLETE THIS CODE
  
  return -1.0;
}

void RigidBodySpringForce::computeForceAndTorque( std::vector<RigidBody>& rbs )
{
  assert( m_rb0 >= -1 ); assert( m_rb0 < (int) rbs.size() );
  assert( m_rb1 >= -1 ); assert( m_rb1 < (int) rbs.size() );
  
  // COMPLETE THIS CODE
  // for all rigid bodies i rbs[i].getForce()  += ... some force you compute ...
  //                        rbs[i].getTorque() += ... some torque you compute ...
}

RigidBodyForce* RigidBodySpringForce::createNewCopy()
{
  return new RigidBodySpringForce( m_k, m_l0, m_rb0, m_vc0, m_rb1, m_vc1 );
}


