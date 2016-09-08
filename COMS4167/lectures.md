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

