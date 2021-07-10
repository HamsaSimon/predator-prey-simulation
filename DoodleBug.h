/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * DoodleBug.h
 *
 * Author: Simon Garfe Herrera
 */

#include "Organism.h"

class DoodleBug : public Organism
{
public:
    // Default constructor which will mostly be handled by
    // The base class's (Organism) constructor.
    DoodleBug();

    DoodleBug(int yPosition, int xPosition);

    virtual ~DoodleBug() = default; // virtual destructor

    // Function move(): For every time step, the DoodleBug will move to
    // an adjacent cell containing an ant and will eat the ant. If there
    // are no ants, then the DoodleBug will move randomly to an adjacent cell
    // if all cells are occupied or could move the DoodleBug off the grid,
    // then the DoodleBug stays in the same cell. Please note that a DoodleBug
    // cannot eat another DoodlbeBug!
    virtual void move();

    // Function breed(): The breeding behavior for a DoodleBug is the following:
    // If a DoodleBug survives for eight time steps (i.e, it has not starved)
    // then the DoodleBug will breed in an adjacent cell (up, down, left, or right).
    // If there is no free adjacent cell then the DoodleBug does not breed.
    virtual void breed(std::vector<Organism*>& vecOfOrganisms);

    // Function Starve(): A function which will make the DoodleBug die of starvation.
    // The DoodleBug will starve if it goes three steps without food, that is,
    // if after the third step it has not eat then the DoodleBug would be considered
    // starved and will be removed from the grid
    void starve();

    // Function spawn() will spawn a DoodleBug on the grid.
    virtual void spawn();

    //Function isAlive will check if the Doodlebug is alive or dead.
    virtual bool isAlive();

    virtual bool isOccupied(int yPosition, int xPosition);

private:
    char symbol = 'X';  // The representation of a DoodleBug in the grid.
    int stepsWithoutFood = 0;  // Variable to keep track of how many steps a DoodleBug has been without food.
    bool starved;  // To check whether the DoodleBug has starved or not.

};



