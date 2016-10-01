#include "ImplicitEuler.h"

ImplicitEuler::ImplicitEuler()
: SceneStepper()
{}

ImplicitEuler::~ImplicitEuler()
{}

bool ImplicitEuler::stepScene( TwoDScene& scene, scalar dt )
{
  VectorXs& x = scene.getX();
  VectorXs& v = scene.getV();
  const VectorXs& m = scene.getM();
  assert(x.size() == v.size());
  assert(x.size() == m.size());

  // Implement implicit euler here for extra credit!
        int x_size = x.size();
        scalar norm = 0.0;
        VectorXs dx = dt*v;
        VectorXs dv = VectorXs::Zero(x_size);
        VectorXs dv_step = VectorXs::Zero(x_size);
        VectorXs right = VectorXs::Zero(x_size);
        MatrixXs left = MatrixXs::Zero(x_size,x_size);
        do{
            right.setZero();
            left.setZero();
            // Accumulating
            scene.accumulateGradU(right,dx,dv);
            right *= -dt;
            right -= (m.array()*dv.array()).matrix();
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
            dv_step = left.fullPivLu().solve(right);
            dv += dv_step;
            dx = dt*(v+dv);
            norm = dv_step.norm();
        }
        while(norm >= 1.0e-9);
        v += dv;
        x += dx;
        return true;
}

std::string ImplicitEuler::getName() const
{
  return "Implicit Euler";
}
