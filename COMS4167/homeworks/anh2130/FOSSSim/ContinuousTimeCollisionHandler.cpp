#include "ContinuousTimeCollisionHandler.h"
#include <iostream>
#include "ContinuousTimeUtilities.h"

void syncScene();

// Loops over all edges, particles, and half-planes in the simulation, and
// applies collision detection and handling to each pair.
//
// Note: No collision detection is done between edges that are connected
// by a particle (since these are always colliding.)
//
// Does not need to be changed by students.

void ContinuousTimeCollisionHandler::handleCollisions(TwoDScene &scene, const VectorXs &oldpos, VectorXs &oldvel, scalar dt)
{
    Vector2s n;
    double time;
    
    const VectorXs & qs = oldpos;
    VectorXs & qe = scene.getX();
    for (int i = 0; i < scene.getNumParticles(); i++)
    {
        for (int j = i + 1; j < scene.getNumParticles(); j++)
        {
            if (detectParticleParticle(scene, qs, qe, i, j, n, time))
            {
                addParticleParticleImpulse(i, j, n, time);
                respondParticleParticle(scene, qs, qe, i, j, n, time, dt, scene.getX(), scene.getV());
            }
        }
        
        for (int e = 0; e < scene.getNumEdges(); e++)
        {
            if (scene.getEdges()[e].first != i && scene.getEdges()[e].second != i)
                if (detectParticleEdge(scene, qs, qe, i, e, n, time))
                {
                    addParticleEdgeImpulse(i, e, n, time);
                    respondParticleEdge(scene, qs, qe, i, e, n, time, dt, scene.getX(), scene.getV());
                }
        }
        
        for (int f = 0; f < scene.getNumHalfplanes(); f++)
        {
            if (detectParticleHalfplane(scene, qs, qe, i, f, n, time))
            {
                addParticleHalfplaneImpulse(i, f, n, time);
                respondParticleHalfplane(scene, qs, qe, i, f, n, time, dt, scene.getX(), scene.getV());
            }
        }
    }
    
    syncScene();
}

std::string ContinuousTimeCollisionHandler::getName() const
{
    return "Continuous-Time Collision Handling";
}

// Responds to a collision detected between two particles by applying an impulse
// to the velocities of each one.
void ContinuousTimeCollisionHandler::respondParticleParticle(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int idx1, int idx2, const Vector2s &n, double time, double dt, VectorXs &qm, VectorXs &qdotm)
{
    const VectorXs &M = scene.getM();
    VectorXs dx = (qe-qs)/dt;
    
    VectorXs nhat = n;
    nhat.normalize();
    
    double cfactor = (1.0 + getCOR())/2.0;
    double m1 = scene.isFixed(idx1) ? std::numeric_limits<double>::infinity() : M[2*idx1];
    double m2 = scene.isFixed(idx2) ? std::numeric_limits<double>::infinity() : M[2*idx2];
    
    double numerator = 2*cfactor * (dx.segment<2>(2*idx2) - dx.segment<2>(2*idx1) ).dot(nhat);
    double denom1 = 1+m1/m2;
    double denom2 = m2/m1 + 1;
    
    if(!scene.isFixed(idx1))
    {
        qdotm.segment<2>(2*idx1) += numerator/denom1 * nhat;
        qm.segment<2>(2*idx1) += dt* numerator/denom1 * nhat;
    }
    if(!scene.isFixed(idx2))
    {
        qdotm.segment<2>(2*idx2) -= numerator/denom2 * nhat;
        qm.segment<2>(2*idx2) -= dt * numerator/denom2 * nhat;
    }
}

// Responds to a collision detected between a particle and an edge by applying
// an impulse to the velocities of each one.
void ContinuousTimeCollisionHandler::respondParticleEdge(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int vidx, int eidx, const Vector2s &n, double time, double dt, VectorXs &qm, VectorXs &qdotm)
{
    const VectorXs &M = scene.getM();
    VectorXs dx = (qe-qs)/dt;
    
    int eidx1 = scene.getEdges()[eidx].first;
    int eidx2 = scene.getEdges()[eidx].second;
    
    
    VectorXs dx1 = dx.segment<2>(2*vidx);
    VectorXs dx2 = dx.segment<2>(2*eidx1);
    VectorXs dx3 = dx.segment<2>(2*eidx2);
    
    VectorXs x1 = qs.segment<2>(2*vidx) + time*dt*dx1;
    VectorXs x2 = qs.segment<2>(2*eidx1) + time*dt*dx2;
    VectorXs x3 = qs.segment<2>(2*eidx2) + time*dt*dx3;
    
    VectorXs nhat = n;
    nhat.normalize();
    
    double alpha = (x1-x2).dot(x3-x2)/(x3-x2).dot(x3-x2);
    alpha = std::min(1.0, std::max(0.0, alpha) );
    VectorXs vedge = dx2 + alpha*(dx3-dx2);
    double cfactor = (1.0 + getCOR())/2.0;
    
    double m1 = scene.isFixed(vidx) ? std::numeric_limits<double>::infinity() : M[2*vidx];
    double m2 = scene.isFixed(eidx1) ? std::numeric_limits<double>::infinity() : M[2*eidx1];
    double m3 = scene.isFixed(eidx2) ? std::numeric_limits<double>::infinity() : M[2*eidx2];
    
    double numerator = 2*cfactor*(vedge-dx1).dot(nhat);
    double denom1 = 1.0 + (1-alpha)*(1-alpha)*m1/m2 + alpha*alpha*m1/m3;
    double denom2 = m2/m1 + (1-alpha)*(1-alpha) + alpha*alpha*m2/m3;
    double denom3 = m3/m1 + (1-alpha)*(1-alpha)*m3/m2 + alpha*alpha;
    
    if(!scene.isFixed(vidx))
    {
        qdotm.segment<2>(2*vidx) += numerator/denom1 * nhat;
        qm.segment<2>(2*vidx) += dt*numerator/denom1 * nhat;
    }
    if(!scene.isFixed(eidx1))
    {
        qdotm.segment<2>(2*eidx1) -= (1.0-alpha)*numerator/denom2 * nhat;
        qm.segment<2>(2*eidx1) -= dt*(1.0-alpha)*numerator/denom2 * nhat;
    }
    if(!scene.isFixed(eidx2))
    {
        qdotm.segment<2>(2*eidx2) -= alpha * numerator/denom3 * nhat;
        qm.segment<2>(2*eidx2) -= dt*alpha*numerator/denom3*nhat;
    }
    
}


// Responds to a collision detected between a particle and a half-plane by 
// applying an impulse to the velocity of the particle.
void ContinuousTimeCollisionHandler::respondParticleHalfplane(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int vidx, int pidx, const Vector2s &n, double time, double dt, VectorXs &qm, VectorXs &qdotm)
{
    VectorXs nhat = n;
    nhat.normalize();
    double cfactor = (1.0+getCOR())/2.0;
    VectorXs dx1 = (qe-qs)/dt;
    VectorXs oldqe = qe;
    qdotm.segment<2>(2*vidx) -= 2*cfactor*dx1.segment<2>(2*vidx).dot(nhat)*nhat;
    qm.segment<2>(2*vidx) -= dt*2*cfactor*dx1.segment<2>(2*vidx).dot(nhat)*nhat;
}






// BEGIN STUDENT CODE //


// Given the start position (oldpos) and end position (scene.getX) of two
// particles, and assuming the particles moved in a straight line between the
// two positions, determines whether the two particles were overlapping and
// approaching at any point during that motion.
// If so, returns true, sets n to the the vector between the two particles
// at the time of collision, and sets t to the time (0 = start position, 
// 1 = end position) of collision.
// Inputs:
//   scene:  The scene data structure. The new positions and radii of the 
//           particles can be obtained from here.
//   qs:     The start-of-timestep positions.
//   qe:     The predicted end-of-timestep positions.
//   idx1:   The index of the first particle. (ie, the degrees of freedom
//           corresponding to this particle are entries 2*idx1 and 2*idx1+1 in
//           scene.getX()).
//   idx2:   The index of the second particle.
// Outputs:
//   n:    The vector between the two particles at the time of collision.
//   time: The time (scaled to [0,1]) when the two particles collide.
//   Returns true if the two particles overlap and are approaching at some point
//   during the motion.
bool ContinuousTimeCollisionHandler::detectParticleParticle(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int idx1, int idx2, Vector2s &n, double &time)
{
    VectorXs dx = qe-qs;
    
    VectorXs x1 = qs.segment<2>(2*idx1);
    VectorXs x2 = qs.segment<2>(2*idx2);
    
    VectorXs dx1 = dx.segment<2>(2*idx1);
    VectorXs dx2 = dx.segment<2>(2*idx2);
    
    double r1 = scene.getRadius(idx1);
    double r2 = scene.getRadius(idx2);

    std::vector<double> position_polynomial;
    std::vector<double> velocity_polynomial;
    
    // Your implementation here should compute n, and examine time to decide the return value
    std::vector<double> pospoly, velpoly;

    Vector2s dx21 = dx2 - dx1;
    Vector2s x21 = x2 - x1;
    double r12 = r1 + r2;

    // - (dx2 - dx1).dot(dx2 - dx1)
    pospoly.push_back(-dx21.dot(dx21));
    // -2*(x2 - x1).dot(dx2 - dx1)
    pospoly.push_back(-2*x21.dot(dx21));
    // (r1+r2)*(r1_r2) - (x2 - x1).dot(x2 - x1)
    pospoly.push_back(r12*r12 - x21.dot(x21));

    // (dx1 - dx2).dot(dx2 - dx1)
    velpoly.push_back(-(-dx21).dot(-dx21));
    // (dx1 - dx2).dot(x2 - x1)
    velpoly.push_back((-dx21).dot(x21));

    // Your implementation here should fill the polynomials with right coefficients
    // Do not change the order of the polynomials here, or your program will fail the oracle
    std::vector<Polynomial> polynomials;
    polynomials.push_back(Polynomial(pospoly));
    polynomials.push_back(Polynomial(velpoly));
    
    time = PolynomialIntervalSolver::findFirstIntersectionTime(polynomials);
    if(time <= 1.0)
    {
        // n(t) = x2 + t*dx2 - x1 - t*dx1
        // = t*(dx2 - dx1) + (x2 - x1)
        n = time*dx21 + x21;
        return true;
    }
    else
        return false;
}


// Given start positions (oldpos) and end positions (scene.getX) of a
// particle and an edge, and assuming the particle and edge endpoints moved in 
// a straight line between the two positions, determines whether the two 
// objects were overlapping and approaching at any point during that motion.
// If so, returns true, sets n to the the vector between the particle and the
// edge at the time of collision, and sets t to the time (0 = start position, 
// 1 = end position) of collision.
// Inputs:
//   scene:  The scene data structure. 
//   qs:     The start-of-timestep positions.
//   qe:     The predicted end-of-timestep positions.
//   vidx:   The index of the particle.
//   eidx:   The index of the edge.
// Outputs:
//   n:    The shortest vector between the particle and edge at the time of 
//         collision.
//   time: The time (scaled to [0,1]) when the two objects collide.
//   Returns true if the particle and edge overlap and are approaching at
//   some point during the motion.
// Given start positions (oldpos) and end positions (scene.getX) of a
// particle and an edge, and assuming the particle and edge endpoints moved in 
// a straight line between the two positions, determines whether the two 
// objects were overlapping and approaching at any point during that motion.
bool ContinuousTimeCollisionHandler::detectParticleEdge(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int vidx, int eidx, Vector2s &n, double &time)
{
    VectorXs dx = qe - qs;
    
    VectorXs x1 = qs.segment<2>(2*vidx);
    VectorXs x2 = qs.segment<2>(2*scene.getEdge(eidx).first);
    VectorXs x3 = qs.segment<2>(2*scene.getEdge(eidx).second);
    
    VectorXs dx1 = dx.segment<2>(2*vidx);
    VectorXs dx2 = dx.segment<2>(2*scene.getEdge(eidx).first);
    VectorXs dx3 = dx.segment<2>(2*scene.getEdge(eidx).second);

    double r1 = scene.getRadius(vidx);
    double r2 = scene.getEdgeRadii()[eidx];
    double r12 = r1+r2;

    std::vector<double> position_polynomial;
    std::vector<double> alpha_greater_than_zero_polynomial;
    std::vector<double> alpha_less_than_one_polynomial;
    
    // Your implementation here should fill the polynomials with right coefficients

    // Here's the quintic velocity polynomial:
    std::vector<double> velcity_polynomial;
    {
        double a = (x3-x2).dot(x3-x2);
        double b = (x3-x2).dot(dx3-dx2);
        double c = (dx3-dx2).dot(dx3-dx2);
        double d = (dx2-dx1).dot(dx2-dx1);
        double e = (dx2-dx1).dot(x2-x1);
        double f = (x1-x2).dot(x3-x2);
        double g = (x1-x2).dot(dx3-dx2) + (dx1-dx2).dot(x3-x2);
        double h = (dx1-dx2).dot(dx3-dx2);
        double i = (dx3-dx2).dot(x2-x1) + (dx2-dx1).dot(x3-x2);
        double j = (dx3-dx2).dot(dx2-dx1);
        double k = a*f;
        double l = a*g+2*b*f;
        double m = a*h+2*b*g+c*f;
        double n = c*g+2*b*h;
        double o = c*h;
        double p = (dx3-dx2).dot(x3-x2);
        double q = (dx3-dx2).dot(dx3-dx2);

        double s = (x2 - x1).dot(x2 - x1);

        double t = (dx1-dx3).dot(dx2-dx3);
        double u = (x1-x3).dot(dx2-dx3) + (dx1-dx3).dot(x2-x3);
        double v = (x1-x3).dot(x2-x3);

        // I am aware this is wrong, but I must be inputting the function incorrectly in Mathematica, because this is what I get. I am sure I am supposed to be using a bunch of differences between points.
        position_polynomial.push_back(r12*r12*(x2.dot(x2) - 2*x2.dot(x3) + x3.dot(x3)));
        position_polynomial.push_back(r12*r12*(2*dx2.dot(x2) - 2*dx3.dot(x2) - 2*dx2.dot(x3) + 2*dx3.dot(x3)));
        position_polynomial.push_back(r12*r12*(dx2.dot(dx2) - 2*dx2.dot(dx3) + dx3.dot(dx3)));

        alpha_greater_than_zero_polynomial.push_back(h);
        alpha_greater_than_zero_polynomial.push_back(g);
        alpha_greater_than_zero_polynomial.push_back(f);

        alpha_less_than_one_polynomial.push_back(t);
        alpha_less_than_one_polynomial.push_back(u);
        alpha_less_than_one_polynomial.push_back(v);

        velcity_polynomial.push_back( -h*h*q - c*c*d - 2*o*j );
        velcity_polynomial.push_back( -h*h*p - 2*g*h*q - 4*b*c*d - c*c*e - o*i - 2*n*j );
        velcity_polynomial.push_back( -2*g*h*p - 2*f*g*q - g*g*q - 2*a*c*d - 4*b*b*d - 4*b*c*e - n*i - 2*m*j );
        velcity_polynomial.push_back( -2*f*h*p - g*g*p - 2*f*g*q - 4*a*b*d - 2*a*c*e - 4*b*b*e - m*i - 2*l*j );
        velcity_polynomial.push_back( -2*f*g*p - f*f*q - a*a*d - 4*a*b*e - l*i - 2*k*j );
        velcity_polynomial.push_back( -f*f*p - a*a*e - k*i );
    }

    // Do not change the order of the polynomials here, or your program will fail the oracle
    std::vector<Polynomial> polynomials;
    polynomials.push_back(Polynomial(position_polynomial));
    polynomials.push_back(Polynomial(alpha_greater_than_zero_polynomial));
    polynomials.push_back(Polynomial(alpha_less_than_one_polynomial));
    polynomials.push_back(Polynomial(velcity_polynomial));
    
    // Your implementation here should compute n, and examine time to decide the return value
    time = PolynomialIntervalSolver::findFirstIntersectionTime(polynomials);

    if(time <= 1.0)
    {
        // n = xa - x1
        // = x2 + a(x3 - x2) - x1
        VectorXs _x1 = x1 + time*dx1;
        VectorXs _x2 = x2 + time*dx2;
        VectorXs _x3 = x3 + time*dx3;
        VectorXs _x12 = _x1 - _x2;
        Vector2s _x32 = _x3 - _x2;
        double alpha = _x12.dot(_x32) / _x32.dot(_x32);
        n =  _x2
            + (alpha)*_x32
            - _x1;
        return true;
    }
    else
        return false;
}

// Given start positions (oldpos) and end positions (scene.getX) of a
// particle and a half-plane, and assuming the particle endpoints moved in 
// a straight line between the two positions, determines whether the two 
// objects were overlapping and approaching at any point during that motion.
// If so, returns true, sets n to the the vector between the particle and the
// half-plane at the time of collision, and sets t to the time (0 = start 
// position, 1 = end position) of collision.
// Inputs:
//   scene:  The scene data structure. 
//   qs:     The start-of-timestep positions.
//   qe:     The predicted end-of-timestep positions.
//   vidx:   The index of the particle.
//   eidx:   The index of the half-plane. The vectors (px, py) and (nx, ny) can
//           be retrieved by calling scene.getHalfplane(pidx).
// Outputs:
//   n:    The shortest vector between the particle and half-plane at the time 
//         of collision.
//   time: The time (scaled to [0,1]) when the two objects collide.
//   Returns true if the particle and half-plane overlap and are approaching at
//   some point during the motion.
// Given start positions (oldpos) and end positions (scene.getX) of a
// particle and a half-plane, and assuming the particle endpoints moved in 
// a straight line between the two positions, determines whether the two 
// objects were overlapping and approaching at any point during that motion.
bool ContinuousTimeCollisionHandler::detectParticleHalfplane(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, int vidx, int pidx, Vector2s &n, double &time)
{
    VectorXs dx = qe - qs;
    
    VectorXs x1 = qs.segment<2>(2*vidx);
    VectorXs dx1 = dx.segment<2>(2*vidx);
    
    VectorXs xp = scene.getHalfplane(pidx).first;
    VectorXs np = scene.getHalfplane(pidx).second;
    
    double r = scene.getRadius(vidx);
 
    std::vector<double> position_polynomial;
    std::vector<double> velocity_polynomial;
    
    // Your implementation here should fill the polynomials with right coefficients
    double npnp = np.dot(np);
    double xpx1np = (xp-x1).dot(np);
    double dx1np = dx1.dot(np);

    position_polynomial.push_back(dx1np * -dx1np);
    position_polynomial.push_back(dx1np * 2*xpx1np);
    position_polynomial.push_back(xpx1np * -xpx1np + r*r*npnp);
    
    velocity_polynomial.push_back(dx1np * -dx1np);
    velocity_polynomial.push_back(dx1np * xpx1np);
    // Do not change the order of the polynomials here, or your program will fail the oracle
    std::vector<Polynomial> polynomials;
    polynomials.push_back(Polynomial(position_polynomial));
    polynomials.push_back(Polynomial(velocity_polynomial));
    
    time = PolynomialIntervalSolver::findFirstIntersectionTime(polynomials);
    
    // Your implementation here should compute n, and examine time to decide the return value
    if(time <= 1.0)
    {
        n = (xp - x1 - time*dx1).dot(np)/npnp * np;
        return true;
    }
    else
        return false;
}


