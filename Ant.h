/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * Ant.h
 *
 * Author: Simon Garfe Herrera
 */

#ifndef ANT_H_
#define ANT_H_

#include "Organism.h"

class Ant : public Organism

{
public:
    // Default constructor which will mostly be handled by
    // The base class's (Organism) constructor.
    Ant();

    // Non-Default constructor to create an Ant during the simulation.
    // Is handled using the base class's (Organism) constructor.
    Ant(int yPosition, int xPosition);

    virtual ~Ant() = default; // virtual destructor

    // Function move() will move the ant in the following manner:
    // for every time step, the ant will randomly move (up, down, left, or right)
    // if the neighboring cell in the select move is occupied or would move the ant
    // off the grid, then the ant will stay in the current cell.
    virtual void move();

    // Function breed() specifies the breeding behavior of an Ant:
    // If an ant survives for three time steps, then at the end of the
    // third time step (i.e, after moving) the ant will breed by creating
    // a new ant in an adjacent cell (up, down, left or right) that is empty.
    // If there is no empty cell available no breeding occurs.
    virtual void breed(std::vector<Organism*>& vecOfOrganisms);

    // Function spawn() will spawn an Ant on the grid.
    virtual void spawn();

    // Function getCurrentTimeStep() will return the current time step
    // the Ant is on
	int getCurrentTimeStep() const;

	// Function isAlive will check if the current Ant is alive or dead.
	virtual bool isAlive();

	virtual bool isOccupied(int yPosition, int xPosition);

private:
    char symbol = 'O'; // The representation of an Ant in the grid.

};



#endif /* ANT_H_ */
