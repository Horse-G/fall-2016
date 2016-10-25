#include "RigidBodyExplicitEuler.h"

RigidBodyExplicitEuler::~RigidBodyExplicitEuler()
{
}

bool RigidBodyExplicitEuler::stepScene( RigidBodyScene& scene, scalar dt )
{
  // Clear any previously computed forces in the rigid bodies
  std::vector<RigidBody>& rbs = scene.getRigidBodies();
  for( std::vector<RigidBody>::size_type i = 0; i < rbs.size(); ++i )
      rbs[i].getForce().setZero();
  for( std::vector<RigidBody>::size_type i = 0; i < rbs.size(); ++i )
      rbs[i].getTorque() = 0.0;
  
  // Add each force's contribution to each rigid body using previous step's state
  std::vector<RigidBodyForce*>& frcs = scene.getForces();
  for( std::vector<RigidBodyForce*>::size_type i = 0; i < frcs.size(); ++i )
      frcs[i]->computeForceAndTorque(rbs);
  
  // Useful method:
  //   RigidBody::getX()
  //   RigidBody::getV()
  //   RigidBody::getTheta()
  //   RigidBody::getOmega()
  //   RigidBody::getForce()
  //   RigidBody::getTorque()
  
  // For each rigid body
  for( std::vector<RigidBody>::size_type i = 0; i < rbs.size(); ++i )
  {
      Vector2s& i_ref_pos    = rbs[i].getX();
      Vector2s& i_ref_vel    = rbs[i].getV();
      scalar&   i_ref_theta  = rbs[i].getTheta();
      scalar&   i_ref_omega  = rbs[i].getOmega();
      Vector2s i_const_force  = rbs[i].getForce();
      scalar   i_const_torque = rbs[i].getTorque();
      scalar   i_const_mass   = rbs[i].getM();
      scalar   i_const_ang    = rbs[i].getI();

      i_ref_pos   += dt * i_ref_vel;
      i_ref_theta += dt * i_ref_omega;
      i_ref_vel   += dt * i_const_force / i_const_mass;
      i_ref_omega += dt * i_const_torque / i_const_ang;
      

      // why was this in another loop?
      rbs[i].updateDerivedQuantities();
  }
  //for( std::vector<RigidBodyForce*>::size_type i = 0; i < rbs.size(); ++i )
  //    rbs[i].updateDerivedQuantities();
  
  return true;
}

std::string RigidBodyExplicitEuler::getName() const
{
  return "Rigid Body Explicit Euler";
}
