# Computer Animation, COMS 4167
## Lecture 01, 2016-09-06

### Welcome
No textbook, no provided notes
Prereq: C++, calculus, linear algebra
Be entusiastic

### Requirements
All communications on Piazza
Get a free CLIC account

### Grading
85% is based on weekly assignments
	- they all receive equal weight
15% final exam
	- 4/5 should be straightforward if you did the homework

#### Due Dates
Due dates will be listed online
1% grade loss for every 6 minutes it is late
	- 2 hours late is 20%
	- 10 hours and everything is gone

#### Grading & Pardon Policy
Two homeworks with the lowest grades will get doubled grades, at the end of the semester
Class will not curve down. He may curve up if he feels like it.
Pluses and minuses are up to Grinspun's discretion.

### A Brief History of Animation

#### Persistence of Vision
The illusion of motion through showing a series of images in the same place.
Pantomimes Lumineuses, Theatre Optique de E Reynaud

#### History
1937, Snow White - the 7th feature length animated movie
	- Announced in 1934
	- Called "Disney's Folly" because of going overbudget and behind schedule

Cell shading worked really well, until computer showed up

#### Birth of Computer Animation
1963, Sutherland's Sketchpad
	- the first CAD tool
	- the guy got a Turing award, not for this sketchpad though

### Themes
	- integration of ordinary differential equations
	- discontinuities (fractures and collisions)
	- rigid bodies
	- elastic bodies
	- fluids
	- controlling the physics
#### I: Mass Spring Systems
	- objects with position, mass, initial velocity
	- apply a force to see the change in position of the object
#### II: Collisions & Fractures
	- what happens to objects when they bounce
	- reflection
	- coefficient of restitution
#### III: Rigid Bodies
	- Landslides
	- Fracture events
#### IV: Plasto-visco-elasticity
	- Finite Element Method
	- Discrete Differential Geometry
#### V: Smoke & Liquids (Fluids)
	- Navier-Stokes equation
	- Shallow water equations

## Lecture 02, 2016-09-08
There will be a separation between class discussion, and the programming assignments.
Like a physics class does theory in class, and has a lab for the applications.

We will get the theoretical foundations in class, and the assignments will reinforce the practical aspects to these physical systems.

### Configuations
The **configuration** of an object in space completely explains its location in that space.

We use _q_ to identify the configuration.

For a single dimensional space, you may use _\_q_ = _(q0)_.
For an N-dimensional space, you may use _\_q_ = _(q0,...,qN)_. This notation is how we will present **vectors**.

If you were to draw a square for a 2 dimensional space, you could accurately point to 1 (and only 1) configuration in the space.
This drawn square is called the **configuration space**, and it is notated as _Q_. A **configuration subspace** is a subset of a configuration space.

When you write the vector of a configuration - you recognize the **degrees of freedom** of the system.

### Trajectories
_q c Q_

Trajectory: _q(t)_: _R -> Q_

In the simulations, _R_ would be replaced by _[tm,tn]_

The **configurational velocity** is the time derivative of the configuration.

We notate this velocity as _.q_ = _dq_/_dt_.

### State
The **state** of a system explains the entire initial conditions of the system to predict any future states,
In a 2-dimensional space, the state is 4 dimensions (as it the combination of the configuration and the trajectory).
It is notated as _\_y_ = _(\_q, .q)_.

Graphical representing the state is distinct from the graphical representation of the configuration space.

For any position in the state space, you can draw a vector describing the configuration in the next time step.
If you have this entire collection of vectors, it is called the **Hamiltonian flow**.

The vector space is notated as _.y_ = _\_X(\_y)_ = _(.q, ..q)_.

## Lecture 03, 2016-09-13
Recap of last lecture.

### Adding Forces
For homework we added gravity.

We assumed that the acceleration due to gravity was constant, because it is a simple system.

The change in distances within the system is so small compared to the size of the earth that we can assume that the force gravity stays constant.

The degrees of freedom of a configuration is 1, because you only need to know the "position" to know the position of the object.
However, this is not enough information to predict future configurations.

_.y = d(\_q/.q)/dt = .q/..q_

When working with a constant gravity, _..q = \_g_.

Even something as simple as a gravity force will make the Hamiltonian flow way more complicated/interesting.

Any conifguration in the vector field has the same vector space (under constant gravity).

Any given configuration over time will develop into a backwards 'c' (an orbit).

### Explicit Euler
To simulate this in a computer, we need a numerical method that changes the state over time (a time integration).

1. Poll the vector space for the velocity for a given configuration.
2. Add that velocity to the configuration to get the next configuration.
3. Repeat.

_\_y(k+1) = \_y(k) + \_X(\_y(k))_

To include a variable time step (not necessarily the unit), change the function like so:

_\_y(k+1) = \_y(k) + h*\_X(\_y(k))_

Where _h = dt_. To implement this in the homework, let's spell out our positions and velocities:

_(\_q(k+1) , .q(k+1)) = (\_q(k) , .q(k)) + h*(.q(k) , \_g)_

This is an explicit method because everything on the right hand side is dependent on the current time step.
This is because, at a more general level, _\_g = ..q(k)_.

### Symplectic Euler
Symplectic and Explicit develop the same trajectories in the special case where the only force is gravity and it is constant.

_\_q(k+1) = \_q(k) + f(.q)_

_.q(k+1) = .q(k) + f(..q)_

If the forces are in any way different, then Symplectic generates differently.

### Drag / Friction
Drag points in the opposite direction of the direction of motion (it makes the size of the direction vector smaller). A simple model of this:

_\_F = - s * .q_

## Lecture 04, 2016-09-15
### Forces recap
Forces are typically written

_\_F = m * a_

where `F` is the force, `m` is the mass of the object, and `a` is the accelration applied.

Under gravity, it can be rewritten

_\_F = M * ..q_

Mass is represented as a matrix because the force and the acceleration are not necessarily colinear.

(Vectors and tensors exist independent of the configuration space. Once you have a new coordinate system, you can know its specifics.)

You can rewrite the function as

_M^(-1) * F = ..q_

For now we will cop out by defining a *force* as the thing that accelerates objects.

### Work
**Work** was originally defined as force over a distance.
Under sufficient conditions you can think of the rate of work (**power**) as:

_W = .q^(T) * F_

### Aside to conservative forces
A **conversative force** exerts a total work of 0. This occurs when the object under the force
returns to its original position (a closed loop in configuration space). Friction is not a conservative force. It is **dissipative**.

!conservative != dissipative

dissipative = !conservative

Under a consersative force for the total work `W`, _W = W1 + W2 = 0_.

And therefore, if there is a `W3` that has the same endpoints as `W1`, _W1 = W3_.

The work done from A to B on a conversative force does not depend on the specific path from A to B.

_W(A->B) = -W(B->A)_

### Energy
The **energy** at a specific point in configuration space is the work it takes to get from the origin to that point.

_E(B) = W(O->B)_

And therefore

_W(A->B) = E(B) - E(A) = W(O->B) - W(O->A)_

_E(q) = U(q) = V(q)_

This does not work for friction because it is not a conservative force.

For the energy of gravity: _G = m * g * \_x_

It is conventional to draw forces as attempting to reduce energy.

### Summary
_F = -grad\_q(U(q))_

Where gradient is the direction of steepest ascent, so it must be negative to point towards the reduction of energy.

_delta (U) = (grad U)^(T) * delta(q)_

For gravity,

_9.8 = (grad U)^(T) * (0,1)_

_0 = (grad U)^(T) * (-1,0)_

If _gradU = (alpha, Beta)_, then _alpha = 0_, _Beta = 9.8_.

## Lecture 05, 2016-09-20


## Lecture 06, 2016-09-22
Last lecture we covered that there were issues with both of the Eulers we have been using.

_g(y) = 0_

### Newton's method
Line search

input: y0
k = 0
loop
	Jacobian * delta y = - G(yk)
	yk+1 = yk + delta y
	++k
	if delta Y < epsilon_step
	if g(yk) < epsilon value
	f g(yk+1)/g(y0) < epsilon change in value

Jacobian = 

2d x 2d matrix

- top left = id_d
- top right = -h * id_d
- bottom left = -h * M^(-1) * Jacobian of Force with respect to \_q
- bottom right = id_d - h * M^(-1) * Jacobain of Force with respect to .q

## Lecture 07, 2016-09-27
How would you simulate a pendulum with our current abilities. There are different possibilities;

### Penalty force
make the particle not want to leave the curve (tie it to a spring)

But if you want to generalize this process to any path, you have to realize the the spring is just applying potential energies to the particle.

To do this you need to define a **constraint function**, that applies 0 energy when the particle is on the curve, and an antienergy when it is off the path.

The potential for this force is the constraint function squared.

### Constraint maintaining force
For a pendulum, have a force pushing against the ball that is proportionally opposite to the amount of gravity pushing it out of the circle.
 
This is specifically called **constraint enforcement via Lagrange multipliers**.

#### Post constraint

### Reduced coordinates

## Lecture 08, 2016-09-29

### Penalty force
The penality approach is perfect for **elastic collisions**. Elastic collisions have a **coefficient of restution** of 1.

Emily Nother

### Constraint maintaining force
_g > 0 -> lambda = 0_

_lambda >= 0_

_(Force total) dot (grad g) >= 0_

Those last two were complementary; either lambda or force dot grad can be a positive nonzero, but not both.

## Lecture 07, 2016-10-04
I MISSED THIS CLASS

## Lecture 08, 2016-10-06
























