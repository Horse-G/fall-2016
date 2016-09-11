#include "ExplicitEuler.h"

ExplicitEuler::ExplicitEuler()
: SceneStepper()
{}

ExplicitEuler::~ExplicitEuler()
{}

bool ExplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
        VectorXs& x = scene.getX();
        VectorXs& v = scene.getV();
        const VectorXs& m = scene.getM();
        VectorXs F = VectorXs::Zero(x.size());
        int part_count = scene.getNumParticles();
        int i = 0;

        scene.accumulateGradU(F,x,v);
        F = -F;

        for(; i < part_count; i++)
                if(scene.isFixed(i))
                        F.segment<2>(2*i).setZero();
        x += dt * v;
        F.array() /= m.array();
        v += dt * F;

        return true;
}

std::string ExplicitEuler::getName() const
{
    return "Explicit Euler";
}
