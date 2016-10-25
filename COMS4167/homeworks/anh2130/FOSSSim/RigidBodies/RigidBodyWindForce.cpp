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
    for(std::vector<RigidBody>::size_type idx = 0; idx < rbs.size(); ++idx)
    {
        int N = rbs[idx].getNumEdges();
        for(int i = 0; i < N; ++i)
        {
            Vector2s v0 = rbs[i].getWorldSpaceVertex(i);
            Vector2s e  = rbs[idx].computeWorldSpaceEdge(i);
            Vector2s n_hat(-e.y(),e.x());
            scalar length = n_hat.norm();
            assert(length != 0.0);
            n_hat /= length;

            for(int j = 0; j < m_num_quadrature_points; ++j)
            {
                Vector2s j_x = v0 + e * (j+0.5)/m_num_quadrature_points;
                Vector2s j_v = rbs[i].computeWorldSpaceVelocity(j_x);
                Vector2s rel_vel = n_hat * (m_wind - j_v).dot(n_hat);
                Vector2s wind_force = (m_beta * length) / m_num_quadrature_points * rel_vel;

                rbs[i].getForce() += wind_force;
            }
        }
    }
    return;
}

RigidBodyForce* RigidBodyWindForce::createNewCopy()
{
  return new RigidBodyWindForce(m_num_quadrature_points,m_beta,m_wind);
}
