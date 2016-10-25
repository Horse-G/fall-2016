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

  Vector2s spring_vec = (m_rb1 == -1? m_vc1 : rbs[m_rb1].computeWorldSpacePosition(m_vc1)) - (m_rb0 == -1? m_vc0: rbs[m_rb0].computeWorldSpacePosition(m_vc0));

  return 0.5 * m_k * pow(spring_vec.norm() - m_l0, 2.0); 
}

void RigidBodySpringForce::computeForceAndTorque( std::vector<RigidBody>& rbs )
{
  assert( m_rb0 >= -1 ); assert( m_rb0 < (int) rbs.size() );
  assert( m_rb1 >= -1 ); assert( m_rb1 < (int) rbs.size() );

  Vector2s rb_0 = Vector2s::Zero();
  Vector2s rb_1 = Vector2s::Zero();
  Vector2s spring_vec = Vector2s::Zero();
  scalar length = 0.0;
  Vector2s n_hat = Vector2s::Zero();
  Vector2s spring_force = Vector2s::Zero();
  
  if(m_rb0 == -1) // firstEndPointIsFixed
      rb_0 = m_vc0;
  else
      rb_0 = rbs[m_rb0].rotateIntoWorldSpace(m_vc0);
  if(m_rb1 == -1) // secondEndpointIsFixed
      rb_1 = m_vc1;
  else
      rb_1 = rbs[m_rb1].rotateIntoWorldSpace(m_vc1);

  spring_vec = rb_1 - rb_0;
  if(m_rb0 != -1) // !firstEndpointIsFixed
      spring_vec -= rbs[m_rb0].getX();
  if(m_rb1 != -1) // !secondEndpointIsFixed
      spring_vec += rbs[m_rb1].getX();
  length = spring_vec.norm();
  
  // need to check for zeros before assert so it returns correctly
  if(m_l0 == 0.0 && length == 0.0)
      return;
  assert(length != 0.0);

  n_hat = spring_vec/length;

  spring_force = m_k * (length - m_l0) * n_hat;

  if(m_rb0 != -1) // !firstEndpointIsFixed
  {
      rbs[m_rb0].getForce() += spring_force;
      rbs[m_rb0].getTorque() += rb_0.x() * spring_force.y() - rb_0.y() * spring_force.x();
  }
  if(m_rb1 != -1) // !firstEndpointIsFixed
  {
      rbs[m_rb1].getForce() += spring_force;
      rbs[m_rb1].getTorque() += rb_1.x() * spring_force.y() - rb_1.y() * spring_force.x();

  }
  return;
}

RigidBodyForce* RigidBodySpringForce::createNewCopy()
{
  return new RigidBodySpringForce( m_k, m_l0, m_rb0, m_vc0, m_rb1, m_vc1 );
}


