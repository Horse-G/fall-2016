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
  //scalar l = (x.segment<2>(2*m_endpoints.second)-x.segment<2>(2*m_endpoints.first)).norm();
  //E += 0.5*m_k*(l-m_l0)*(l-m_l0);
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

/*
  // Compute the elastic component
  Vector2s nhat = x.segment<2>(2*m_endpoints.second)-x.segment<2>(2*m_endpoints.first); 
  scalar l = nhat.norm(); 
  assert( l != 0.0 ); 
  nhat /= l;
  Vector2s fdamp = nhat;
  nhat *= m_k*(l-m_l0);
  gradE.segment<2>(2*m_endpoints.first)  -= nhat;
  gradE.segment<2>(2*m_endpoints.second) += nhat;

  // Compute the internal damping
  // Remember we are computing minus the force here
  fdamp *= m_b*fdamp.dot(v.segment<2>(2*m_endpoints.second)-v.segment<2>(2*m_endpoints.first));
  gradE.segment<2>(2*m_endpoints.first)  -= fdamp;
  gradE.segment<2>(2*m_endpoints.second) += fdamp;
 */
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        scalar length = spring_vec.norm();
		assert(length != 0);
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
/*
  // Contribution from elastic component
  Vector2s nhat = x.segment<2>(2*m_endpoints.second)-x.segment<2>(2*m_endpoints.first); 
  scalar l = nhat.norm();
  assert( l != 0 );
  nhat /= l;

  Matrix2s hess;
  hess = nhat*nhat.transpose();
  hess += (l-m_l0)*(Matrix2s::Identity()-hess)/l;
  hess *= m_k;
  
  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.first)   += hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.second) += hess;

  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.second) -= hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.first) -= hess;

  // Contribution from damping
  Vector2s dv = v.segment<2>(2*m_endpoints.second)-v.segment<2>(2*m_endpoints.first);
  hess = nhat*dv.transpose();
  hess.diagonal().array() += nhat.dot(dv);
  hess -= hess*(nhat*nhat.transpose());
  hess *= -m_b/l;

  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.first)   -= hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.second) -= hess;

  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.second) += hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.first) += hess;
*/
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
        Vector2s spring_vel = v.segment<2>(2*m_endpoints.second) - v.segment<2>(2*m_endpoints.first); 
        scalar length = spring_vec.norm();
        assert(length != 0);
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
/*
  // Contribution from damping
  Vector2s nhat = x.segment<2>(2*m_endpoints.second)-x.segment<2>(2*m_endpoints.first); 
  scalar l = nhat.norm();
  assert( l != 0 );
  nhat /= l;
  
  Matrix2s hess;
  hess = m_b*nhat*nhat.transpose();
  
  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.first)   += hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.second) += hess;
  
  hessE.block<2,2>(2*m_endpoints.first,2*m_endpoints.second) -= hess;
  hessE.block<2,2>(2*m_endpoints.second,2*m_endpoints.first) -= hess;  
*/
        Vector2s spring_vec = x.segment<2>(2*m_endpoints.second) - x.segment<2>(2*m_endpoints.first);
		scalar length = spring_vec.norm();
		assert(length != 0);
        Vector2s n_hat = spring_vec/length;
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
