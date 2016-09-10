#include "ExplicitEuler.h"

ExplicitEuler::ExplicitEuler()
: SceneStepper()
{}

ExplicitEuler::~ExplicitEuler()
{}

bool ExplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
        // Your code goes here!
        
        // Some tips on getting data from TwoDScene:
        // A vector containing all of the system's position DoFs. x0, y0, x1, y1, ...
        //VectorXs& x = scene.getX();
        // A vector containing all of the system's velocity DoFs. v0, v0, v1, v1, ...
        //VectorXs& v = scene.getV();
        // A vector containing the masses associated to each DoF. m0, m0, m1, m1, ...
        //const VectorXs& m = scene.getM();
        // Determine if the ith particle is fixed
        // if( scene.isFixed(i) )
        
        VectorXs& x = scene.getX();
        VectorXs& v = scene.getV();
        const VectorXs& m = scene.getM();
        int part_count = scene.getNumParticles();
        for(int i = 0; i < part_count; i++)
        {
                if(!scene.isFixed(i))
                {
                        VectorXs tmp_v = v.segment<2>(2*i);
                        MatrixXs m_mat = m.segment<2>(2*i) * MatrixXs::Identity(2,2);
                        scene.setPosition(i, x.segment<2>(2*i) + dt * v.segment<2>(2*i));
                        scene.setVelocity(i, v.segment<2>(2*i) /*+ dt * m_mat.transpose() * (v.segment<2>(2*i).dot(v.segment<2>(2*i)) * m_mat/2)*/ );
                }
        }
        return true;
}

std::string ExplicitEuler::getName() const
{
    return "Explicit Euler";
}
