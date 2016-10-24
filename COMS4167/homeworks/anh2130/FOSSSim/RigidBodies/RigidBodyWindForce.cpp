#include "RigidBodyWindForce.h"


RigidBodyWindForce::RigidBodyWindForce( int num_quad_points, const scalar& beta, const Vector2s& wind )
: m_num_quadrature_points(num_quad_points)
, m_beta(beta)
, m_wind(wind)
{
  assert( m_num_quadrature_points >= 2 );
  assert( beta >= 0.0 );
}

RigidBodyWindForce::~RigidBodyWindForce()
{
}

bool RigidBodyWindForce::isConservative() const
{
  return false;
}

scalar RigidBodyWindForce::computePotentialEnergy( const std::vector<RigidBody>& rbs )
{
  // TODO: Clean up this warning
  std::cout << "WARNING: TRYING TO COMPUTE POTENTIAL ENERGY FOR A NON-CONSERVATIVE FORCE." << std::endl;
  
  return 0.0;
}

void RigidBodyWindForce::computeForceAndTorque( std::vector<RigidBody>& rbs )
{
  // COMPLETE THIS CODE
  // for all rigid bodies i rbs[i].getForce()  += ... some force you compute ...
  //                        rbs[i].getTorque() += ... some torque you compute ...
}

RigidBodyForce* RigidBodyWindForce::createNewCopy()
{
  return new RigidBodyWindForce(m_num_quadrature_points,m_beta,m_wind);
}
