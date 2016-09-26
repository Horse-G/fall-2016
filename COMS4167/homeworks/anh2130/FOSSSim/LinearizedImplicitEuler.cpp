#include "LinearizedImplicitEuler.h"

LinearizedImplicitEuler::LinearizedImplicitEuler()
: SceneStepper()
{}

LinearizedImplicitEuler::~LinearizedImplicitEuler()
{}

bool LinearizedImplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
  VectorXs& x = scene.getX();
  VectorXs& v = scene.getV();
  const VectorXs& m = scene.getM();
  assert(x.size() == v.size());
  assert(x.size() == m.size());

  // Implement implicit euler here!
  
  return true;
}

std::string LinearizedImplicitEuler::getName() const
{
  return "Linearized Implicit Euler";
}
