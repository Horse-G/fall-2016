#include "ContestDetector.h"
#include <iostream>
#include "TwoDScene.h"
#include <set>

// For all pairs of potentially-overlapping objects, applies the penalty force.
//
// Does not need to be modified by students.
void ContestDetector::performCollisionDetection(const TwoDScene &scene, const VectorXs &qs, const VectorXs &qe, DetectionCallback &dc)
{
  if( (qs-qe).norm() > 1e-8)
    {
      std::cerr << "Contest collision detector is only designed for use with the penalty method!" << std::endl;
      exit(1);
    }

  PPList pppairs;
  PEList pepairs;
  PHList phpairs;

  findCollidingPairs(scene, qe, pppairs, pepairs, phpairs);
  for(PPList::iterator it = pppairs.begin(); it != pppairs.end(); ++it)
    dc.ParticleParticleCallback(it->first, it->second);
  for(PEList::iterator it = pepairs.begin(); it != pepairs.end(); ++it)
    {
      //particle never collides with an edge it's an endpoint of
      if(scene.getEdge(it->second).first != it->first && scene.getEdge(it->second).second != it->first)
	dc.ParticleEdgeCallback(it->first, it->second);
    }
  for(PHList::iterator it = phpairs.begin(); it != phpairs.end(); ++it)
    dc.ParticleHalfplaneCallback(it->first, it->second);
}

// Given particle positions, computes lists of *potentially* overlapping object
// pairs. How exactly to do this is up to you.
// Inputs: 
//   scene:  The scene object. Get edge information, radii, etc. from here. If 
//           for some reason you'd also like to use particle velocities in your
//           algorithm, you can get them from here too.
//   x:      The positions of the particle.
// Outputs:
//   pppairs: A list of (particle index, particle index) pairs of potentially
//            overlapping particles. IMPORTANT: Each pair should only appear
//            in the list at most once. (1, 2) and (2, 1) count as the same 
//            pair.
//   pepairs: A list of (particle index, edge index) pairs of potential
//            particle-edge overlaps.
//   phpairs: A list of (particle index, halfplane index) pairs of potential
//            particle-halfplane overlaps.
int bound_var(const int& orig, const int& floor, const int& ceil)
{
    return std::max(std::min(ceil,orig),0);
}
void ContestDetector::findCollidingPairs(const TwoDScene &scene, const VectorXs &x, PPList &pppairs, PEList &pepairs, PHList &phpairs)
{
        struct box
        {
            std::set<int> ppp;
            std::set<int> pep;
        };
        static bool first = true;
        static int ct_boxes;
        static int ct_particles;
        static int ct_edges;
        static int ct_halfplanes;
        static box* ds_boxes = NULL;
        
        double min_x = x[0];
        double max_x = x[0];
        
        double min_y = x[1];
        double max_y = x[1];

        double avg_x = 0.0;
        double avg_y = 0.0;
        double dx_left, dx_right, dy_left, dy_right;
        
        int i,j,k;

        // initialize static variables
        if (first)
        {
            ct_particles = scene.getNumParticles();
            ct_edges = scene.getNumEdges();
            ct_halfplanes = scene.getNumHalfplanes();
            ct_boxes = sqrt(ct_particles);
            ds_boxes = new box[ct_boxes*ct_boxes];
            first = false;
        }

        //ds_boxes = new box[ct_boxes][ct_boxes];
        
        // set up mins and maxes for current time step
        for(i = 0; i < ct_particles; ++i)
        {
            int x_tmp = 2*i;
            int y_tmp = x_tmp+1;

            avg_x += x[x_tmp];
            avg_y += x[y_tmp];

            if(x[x_tmp] < x[min_x])
                min_x = x_tmp;
            if(x[x_tmp] > x[max_x])
                max_x = x_tmp;
            if(x[y_tmp] < x[min_y])
                min_y = y_tmp;
            if(x[y_tmp] > x[max_x])
                max_x = y_tmp;
        }

        // setting up the distribution of boxes
        avg_x /= ct_particles;
        avg_y /= ct_particles;
        dx_left = (avg_x - min_x)/(ct_particles/2);
        dx_right = (max_x - avg_x)/(ct_particles/2);
        dy_left = (avg_y - min_y)/(ct_particles/2);
        dy_right = (max_x - avg_y)/(ct_particles/2);

        // Particle-Particle
        for(i = 0; i < ct_particles; ++i)
        {
            int x_tmp = 2*i;
            int y_tmp = x_tmp+1;
            double radius = scene.getRadius(i);

            int p_minx = (x[x_tmp]-radius-min_x)/(max_x-min_x)*ct_boxes;
            int p_maxx = (x[x_tmp]+radius-min_x)/(max_x-min_x)*ct_boxes;
            int p_miny = (x[y_tmp]-radius-min_y)/(max_y-min_y)*ct_boxes;
            int p_maxy = (x[y_tmp]+radius-min_y)/(max_y-min_y)*ct_boxes;
            
            // particles is placed in all the bins it or its radius is in
            for(j = bound_var(p_minx,0, ct_boxes-1); j <= bound_var(p_maxx,0,ct_boxes-1); ++j)
                for(k = bound_var(p_miny,0,ct_boxes-1); k <= bound_var(p_maxy,0,ct_boxes-1); ++k)
                    ds_boxes[ct_boxes*j + k].ppp.insert(i);
        }

        // Particle-Edge
        for(i = 0; i < ct_edges; ++i)
        {
            int e1x_tmp = 2*scene.getEdge(i).first;
            int e1y_tmp = e1x_tmp+1;
            int e2x_tmp = 2*scene.getEdge(i).second;
            int e2y_tmp = e2x_tmp+1;
            double radius = scene.getEdgeRadii()[i];

            int e1_minx = (x[e1x_tmp]-radius-min_x)/(max_x-min_x)*ct_boxes;
            int e1_maxx = (x[e1x_tmp]+radius-min_x)/(max_x-min_x)*ct_boxes;
            int e1_miny = (x[e1y_tmp]-radius-min_y)/(max_y-min_y)*ct_boxes;
            int e1_maxy = (x[e1y_tmp]+radius-min_y)/(max_y-min_y)*ct_boxes;
            
            int e2_minx = (x[e2x_tmp]-radius-min_x)/(max_x-min_x)*ct_boxes;
            int e2_maxx = (x[e2x_tmp]+radius-min_x)/(max_x-min_x)*ct_boxes;
            int e2_miny = (x[e2y_tmp]-radius-min_y)/(max_y-min_y)*ct_boxes;
            int e2_maxy = (x[e2y_tmp]+radius-min_y)/(max_y-min_y)*ct_boxes;

            // one large area of the line
            int p_minx = std::min(e1_minx,e2_minx);
            int p_maxx = std::max(e1_maxx,e2_maxx);
            int p_miny = std::min(e1_miny,e2_miny);
            int p_maxy = std::max(e1_maxy,e2_maxy);

            // edge is placed in all bins within the area
            for(j = bound_var(p_minx,0, ct_boxes-1); j <= bound_var(p_maxx,0,ct_boxes-1); ++j)
                for(k = bound_var(p_miny,0,ct_boxes-1); k <= bound_var(p_maxy,0,ct_boxes-1); ++k)
                    ds_boxes[ct_boxes*j + k].pep.insert(i);
        }

        // Particle-Halfplane
        //// count every particle-halfplane combo as an intersection to compute
        //   (as calculating if plane is in one box or the other will take too much computing time)
        for(i = 0; i < ct_particles; ++i)
            for(j = 0; j < ct_halfplanes; ++j)
                phpairs.insert(std::pair<int,int>(i,j));
       
        std::set<int>::iterator iter1, iter2; 
        // for each box in the ds
        for(i = 0; i < ct_boxes*ct_boxes; ++i)
        {
            // for each particle in that box
            for(iter1 = ds_boxes[i].ppp.begin(); iter1 != ds_boxes[i].ppp.end(); ++iter1)
            {
                iter2 = iter1;
                // search the rest of the particles in the given box and mark a collision
                for(++iter2; iter2 != ds_boxes[i].ppp.end(); ++iter2)
                    pppairs.insert(std::pair<int,int>(*iter1,*iter2));
                
                // search all the edges in the given box and mark a collision
                for(iter2 = ds_boxes[i].pep.begin(); iter2 != ds_boxes[i].pep.end(); ++iter2)
                    pepairs.insert(std::pair<int,int>(*iter1,*iter2));
            }
        }

        return;
}

