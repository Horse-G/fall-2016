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
    int P = m_num_quadrature_points;
    scalar div_by_quad = 1.0/P;
    scalar beta_by_quad = m_beta * div_by_quad;

    for(std::vector<RigidBody>::size_type idx = 0; idx < rbs.size(); ++idx)
    {
        int N = rbs[idx].getNumEdges();
        Vector2s center_of_mass = rbs[idx].getX();

        for(int i = 0; i < N; ++i)
        {
            Vector2s v0 = rbs[idx].getWorldSpaceVertex(i);
            Vector2s e  = rbs[idx].computeWorldSpaceEdge(i);
            Vector2s n_hat(-e.y(),e.x());
            scalar length = n_hat.norm();
            assert(length != 0.0);
            n_hat /= length;

            for(int j = 0; j < P; ++j)
            {
                // position of center of section of edge
                Vector2s j_x = v0 + e * ((j+0.5) * div_by_quad);
                // velocity at that position
                Vector2s j_v = rbs[idx].computeWorldSpaceVelocity(j_x);
                
                // position relative to center of mass
                Vector2s rel_x = j_x - center_of_mass;
                // velocity relative to wind
                Vector2s rel_v = n_hat * (m_wind - j_v).dot(n_hat);

                Vector2s wind_force = (length * beta_by_quad) * rel_v;

                rbs[idx].getForce() += wind_force;
                rbs[idx].getTorque() += rel_x.x() * wind_force.y() - rel_x.y() * wind_force.x();
            }
        }
    }
    return;
}

RigidBodyForce* RigidBodyWindForce::createNewCopy()
{
  return new RigidBodyWindForce(m_num_quadrature_points,m_beta,m_wind);
}
