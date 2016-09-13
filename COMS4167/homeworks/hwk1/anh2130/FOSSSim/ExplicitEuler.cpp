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
        //MatrixXs m_mat = MatrixXs::Identity(x.size(),x.size()) * scene.getM();
        VectorXs F = VectorXs::Zero(x.size());

        scene.accumulateGradU(F,x,v);
        for(int i = scene.getNumParticles() - 1; i >= 0; i--)
                if(scene.isFixed(i))
                        F.segment<2>(2*i).setZero();
        F.array() /= m.array();
        x += dt * v;
        v -= dt * F;
        //v -= dt * m_mat.transpose() * F;

        return true;
}

std::string ExplicitEuler::getName() const
{
    return "Explicit Euler";
}
