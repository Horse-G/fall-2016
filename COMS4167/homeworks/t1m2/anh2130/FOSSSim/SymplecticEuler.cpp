#include "SymplecticEuler.h"

SymplecticEuler::SymplecticEuler()
: SceneStepper()
{}

SymplecticEuler::~SymplecticEuler()
{}

bool SymplecticEuler::stepScene( TwoDScene& scene, scalar dt )
{
  /* Add milestone 2 code here.      */
  
  return true;
}

std::string SymplecticEuler::getName() const
{
  return "Symplectic Euler";
}  





