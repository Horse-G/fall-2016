#include "SymplecticEuler.h"

SymplecticEuler::SymplecticEuler()
: SceneStepper()
{}

SymplecticEuler::~SymplecticEuler()
{}

bool SymplecticEuler::stepScene( TwoDScene& scene, scalar dt )
{
        VectorXs& x = scene.getX();
        VectorXs& v = scene.getV();
        const VectorXs& m = scene.getM();
        VectorXs F = VectorXs::Zero(x.size());
        
        scene.accumulateGradU(F);
        
        for(int i = scene.getNumParticles()-1; i >= 0; --i)
            if(scene.isFixed(i))
                F.segment<2>(2*i).setZero();
        
        F.array() /= m.array();
        
        v -= dt * F;
        x += dt * v;
  return true;
}

std::string SymplecticEuler::getName() const
{
  return "Symplectic Euler";
}  





