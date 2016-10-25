#include "RigidBody.h"

RigidBody::RigidBody( const Vector2s& v, const scalar& omega, const VectorXs& vertices, const VectorXs& masses, const scalar& radius )
: m_M(-1.0)
//, m_masses(masses)
, m_I(-1.0)
, m_vertices(vertices)
, m_r(radius)
, m_X(-1.0,-1.0)
, m_theta(0.0)
, m_V(v)
, m_omega(omega)
// theta == 0 => identity matrix
, m_R(Matrix2s::Identity())
, m_F(0.0,0.0)
, m_tau(0.0)
{
  m_M = computeTotalMass(masses);
  m_X = computeCenterOfMass(vertices,masses);
  m_I = computeMomentOfInertia(vertices,masses);
  
  assert( (masses.array()>0.0).all() );
  assert( m_M > 0.0 );
  assert( m_I > 0.0 );
  assert( m_vertices.size() >= 2 );
  assert( m_r >= 0.0 );

  // Translate the rigid body so the body space center of mass is the origin
  for( int i = 0; i < m_vertices.size()/2; ++i ) m_vertices.segment<2>(2*i) -= m_X;
}

void RigidBody::updateDerivedQuantities()
{
  // Update the rotation matrix representation of orientation
  m_R << cos(m_theta), -sin(m_theta), sin(m_theta), cos(m_theta);
}

Vector2s& RigidBody::getX()
{
  return m_X;
}

const Vector2s& RigidBody::getX() const
{
  return m_X;
}

scalar& RigidBody::getTheta()
{
  return m_theta;
}

const scalar& RigidBody::getTheta() const
{
  return m_theta;
}

Vector2s& RigidBody::getV()
{
  return m_V;
}

const Vector2s& RigidBody::getV() const
{
  return m_V;
}

scalar& RigidBody::getOmega()
{
  return m_omega;
}

const scalar& RigidBody::getOmega() const
{
  return m_omega;
}

const scalar& RigidBody::getM() const
{
  return m_M;
}

const scalar& RigidBody::getI() const
{
  return m_I;
}

const scalar& RigidBody::getRadius() const
{
  return m_r;
}

int RigidBody::getNumVertices() const
{
  assert( m_vertices.size()%2 == 0 );
  return m_vertices.size()/2;
}

int RigidBody::getNumEdges() const
{
  return getNumVertices();
}

Vector2s RigidBody::getWorldSpaceVertex( int i ) const
{
  assert( i >= 0 ); assert( i < getNumVertices() );
  // Rotate body-space coordinate about center of mass, then translate by center of mass
  return m_R*m_vertices.segment<2>(2*i)+m_X;
}

Vector2s RigidBody::rotateIntoWorldSpace( const Vector2s& bodyvec ) const
{
  return m_R*bodyvec;
}

Vector2s RigidBody::computeWorldSpacePosition( const Vector2s& bodyvec ) const
{
  return m_R*bodyvec+m_X;
}

Vector2s RigidBody::computeWorldSpaceVelocity( const Vector2s& worldposition ) const
{
  return m_V + m_omega*mathutils::rotateCounterClockwise90degrees(worldposition-m_X);
}

Vector2s RigidBody::computeWorldSpaceEdge( int i ) const
{
  assert( i >= 0 );
  assert( i < getNumEdges() );
  
  int i0 = i;
  int i1 = (i+1)%getNumVertices();
  
  return m_R*(m_vertices.segment<2>(2*i1)-m_vertices.segment<2>(2*i0));
}

Vector2s& RigidBody::getForce()
{
  return m_F;
}

scalar& RigidBody::getTorque()
{
  return m_tau;
}

Vector2s RigidBody::computeTotalMomentum() const
{
    return m_M * m_V;
}

scalar RigidBody::computeCenterOfMassAngularMomentum() const
{
    Vector2s total_momentum = m_M*m_V;

    return m_X.x()*total_momentum.y() - m_X.y()*total_momentum.x();
}

scalar RigidBody::computeSpinAngularMomentum() const
{
    return m_I * m_omega;
}

scalar RigidBody::computeTotalAngularMomentum() const
{
  // Linear and rotational components
  return computeCenterOfMassAngularMomentum() + computeSpinAngularMomentum();
}

scalar RigidBody::computeCenterOfMassKineticEnergy() const
{
    return 0.5 * m_M * m_V.dot(m_V);
}

scalar RigidBody::computeSpinKineticEnergy() const
{
    return 0.5 * m_I * m_omega * m_omega;
}

scalar RigidBody::computeKineticEnergy() const
{
  // Linear and rotational component
  return computeCenterOfMassKineticEnergy() + computeSpinKineticEnergy();
}



// !!!WARNING!!! DO NOT MODIFY THIS METHOD OR YOUR CODE WILL FAIL
void RigidBody::serialize( std::ofstream& outputstream ) const
{
  assert( outputstream.is_open() );

  // Serialize the center of mass
  outputstream.write((char*)m_X.data(),m_X.size()*sizeof(scalar));
  // Serialize the orientation
  outputstream.write((char*)&m_theta,sizeof(scalar));
  // Serialize the center of mass' velocity
  outputstream.write((char*)m_V.data(),m_V.size()*sizeof(scalar));
  // Serialize the angular velocity
  outputstream.write((char*)&m_omega,sizeof(scalar));
}

// !!!WARNING!!! DO NOT MODIFY THIS METHOD OR YOUR CODE WILL FAIL
void RigidBody::deserialize( std::ifstream& inputstream )
{
  assert( inputstream.is_open() );

  // Deserialize the center of mass
  inputstream.read((char*)m_X.data(),m_X.size()*sizeof(scalar));
  // Deserialize the orientation
  inputstream.read((char*)&m_theta,sizeof(scalar));
  // Deserialize the center of mass' velocity
  inputstream.read((char*)m_V.data(),m_V.size()*sizeof(scalar));
  // Deserialize the angular velocity
  inputstream.read((char*)&m_omega,sizeof(scalar));
  
  updateDerivedQuantities();
}



scalar RigidBody::computeTotalMass( const VectorXs& masses ) const
{
    scalar total_mass = 0.0;
    
    for(int i = 0; i < masses.size(); ++i)
        total_mass += masses(i);
    
    return total_mass;
}

Vector2s RigidBody::computeCenterOfMass( const VectorXs& vertices, const VectorXs& masses ) const
{
    assert(vertices.size()%2 == 0);
    assert(2*masses.size() == vertices.size());
    
    scalar total_mass = 0.0;
    Vector2s center_of_mass = Vector2s::Zero();
    
    for(int i = 0; i < masses.size(); ++i)
    {
        center_of_mass += vertices.segment<2>(2*i)*masses(i);
        total_mass += masses(i);
    }
    
    return center_of_mass*(1.0/total_mass);
}

scalar RigidBody::computeMomentOfInertia( const VectorXs& vertices, const VectorXs& masses ) const
{
  assert( vertices.size()%2 == 0 );
  assert( 2*masses.size() == vertices.size() );
  
  scalar moment_of_inertia = 0.0;
  Vector2s center_of_mass = computeCenterOfMass(vertices,masses);

  for(int i = 0; i < masses.size(); ++i)
  {
      Vector2s temp = vertices.segment<2>(2*i) - center_of_mass;
      moment_of_inertia += masses(i)* temp.dot(temp);
  }
  return moment_of_inertia;
}
