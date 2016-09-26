#include "GravitationalForce.h"

GravitationalForce::GravitationalForce( const std::pair<int,int>& particles, const scalar& G )
: Force()
, m_particles(particles)
, m_G(G)
{
  assert( m_particles.first >= 0 );
  assert( m_particles.second >= 0 );
  assert( m_particles.first != m_particles.second );
  assert( m_G >= 0.0 );
}

GravitationalForce::~GravitationalForce()
{}
  
void GravitationalForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  //scalar r = (x.segment<2>(2*m_particles.second)-x.segment<2>(2*m_particles.first)).norm();
  //scalar m1 = m(2*m_particles.second);
  //scalar m2 = m(2*m_particles.first);
  //E += -m_G*m1*m2/r;
  
        E -= m_G*m(2*m_particles.first)*m(2*m_particles.second)/(x.segment<2>(2*m_particles.second) - x.segment<2>(2*m_particles.first)).norm();
}

void GravitationalForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  //scalar m1 = m(2*m_particles.second);
  //scalar m2 = m(2*m_particles.first);

  //Vector2s nhat = x.segment<2>(2*m_particles.second)-x.segment<2>(2*m_particles.first); 
  //scalar r = nhat.norm(); 
  //assert( r != 0.0 ); 
  //nhat /= r; //< TODO: Roll this division into nhat
  //nhat *= m_G*m1*m2/(r*r);
  
  //gradE.segment<2>(2*m_particles.first)  -= nhat;
  //gradE.segment<2>(2*m_particles.second) += nhat;
  
        Vector2s grav_vec = x.segment<2>(2*m_particles.second) - x.segment<2>(2*m_particles.first);
        Vector2s grav = m_G*m(2*m_particles.first)*m(2*m_particles.second)*grav_vec/pow(grav_vec.norm(),3.0);
        gradE.segment<2>(2*m_particles.first) -= grav;
        gradE.segment<2>(2*m_particles.second) += grav;
}

void GravitationalForce::addHessXToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == hessE.rows() );
  assert( x.size() == hessE.cols() );
  assert( x.size()%2 == 0 );

  // Compute the force Jacboian here!
}

void GravitationalForce::addHessVToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == hessE.rows() );
  assert( x.size() == hessE.cols() );
  assert( x.size()%2 == 0 );
  // Nothing to do.
}

Force* GravitationalForce::createNewCopy()
{
  return new GravitationalForce(*this);
}
