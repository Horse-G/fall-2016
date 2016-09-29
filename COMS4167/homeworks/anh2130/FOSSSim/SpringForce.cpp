#include "SpringForce.h"

SpringForce::SpringForce( const std::pair<int,int>& endpoints, const scalar& k, const scalar& l0, const scalar& b )
: Force()
, m_endpoints(endpoints)
, m_k(k)
, m_l0(l0)
, m_b(b)
{
  assert( m_endpoints.first >= 0 );
  assert( m_endpoints.second >= 0 );
  assert( m_endpoints.first != m_endpoints.second );
  assert( m_k >= 0.0 );
  assert( m_l0 >= 0.0 );
  assert( m_b >= 0.0 );
}

SpringForce::~SpringForce()
{}
  
void SpringForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        E -= pow(spring_vec.norm() - m_l0,2.0)*m_k/2;
}

void SpringForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        scalar length = spring_vec.norm();
        Vector2s n_hat = spring_vec/length;
        Vector2s spring_force = n_hat*(
                // spring stiffness
                m_k*(length-m_l0)
                // damping
                + m_b*n_hat.dot(v.segment<2>(2*m_endpoints.second) - v.segment<2>(2*m_endpoints.first))
                );
        gradE.segment<2>(2*m_endpoints.first)  -= spring_force;
        gradE.segment<2>(2*m_endpoints.second) += spring_force;
}

void SpringForce::addHessXToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == hessE.rows() );
  assert( x.size() == hessE.cols() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        Vector2s spring_vel = v.segment<2>(2*m_endpoints.second) - v.segment<2>(2*m_endpoints.first); 
        scalar length = spring_vec.norm();
        Vector2s n_hat = spring_vec/length;
        Matrix2s id = Matrix2s::Identity();
        Matrix2s nnT = n_hat*n_hat.transpose();
        Matrix2s big_K =
            // spring stiffness
            m_k*(nnT + (length - m_l0)*(id - nnT)/length)
            // damping
            + (m_b/length)*(id*n_hat.dot(spring_vel) + n_hat*spring_vel.transpose())*(id - nnT);
        hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.first)   += big_K;
        hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.second) += big_K;
        hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.second)  -= big_K;
        hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.first)  -= big_K;
}

void SpringForce::addHessVToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, MatrixXs& hessE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == hessE.rows() );
  assert( x.size() == hessE.cols() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        Vector2s n_hat = spring_vec/spring_vec.norm();
        Matrix2s big_B = m_b*n_hat*n_hat.transpose();
        hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.first)   += big_B;
        hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.second) += big_B;
        hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.second)  -= big_B;
        hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.first)  -= big_B;
}

Force* SpringForce::createNewCopy()
{
  return new SpringForce(*this);
}
