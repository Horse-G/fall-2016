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
        int x_size = x.size();
        VectorXs dx = dt*v;
        VectorXs dv = VectorXs::Zero(x_size);
        VectorXs right = VectorXs::Zero(x_size);
        MatrixXs left = MatrixXs::Zero(x_size,x_size);
        // Accumulating
        scene.accumulateGradU(right,dx,dv);
        right *= -dt;
        scene.accumulateddUdxdx(left,dx,dv);
        left *= dt;
        scene.accumulateddUdxdv(left,dx,dv);
        left *= dt;
        left.diagonal() += m;
        // Fixed vertices
        for(int i = x_size/2 - 1; i >= 0; --i)
            if(scene.isFixed(i))
            {
                right.segment<2>(2*i).setZero();
                left.block(2*i,0,2,x_size/2).setZero();
                left.block(0,2*i,x_size/2,2).setZero();
                left.block(2*i,2*i,2,2) = Matrix2s::Identity();
            }
        v += left.fullPivLu().solve(right);
        x += dt * v;
        return true;
}

std::string LinearizedImplicitEuler::getName() const
{
  return "Linearized Implicit Euler";
}
