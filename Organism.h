/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * Organism.h
 *
 * Author: Simon Garfe Herrera
 */

#ifndef ORGANISM_H_
#define ORGANISM_H_

#include <vector>

class Organism //Abstract class Organism
{
public:
    // Default constructor will be used for spawning an Organism
    // At the beginning of the simulation.
    Organism();

    // Constructor to handle spawning wich happens during simulation,
    // e.g., when an Organism breeds.
    Organism(int yPosition, int xPosition);

    //Declare virtual destructor
    virtual ~Organism() = default;

    // Enum class to specify the movement that an organism might make
    // in a grid world.
    enum class Movements {UP = 1, DOWN, LEFT, RIGHT};

    // variable to specify the symbol which will represent an empty cell.
    const static char emptyCell = '.';

    // specify the width of our grid (i.e, our world where creatures will live )
    // declared static because we don't want to make it dependent on an Orgamisn object.
    const static int gridWidth = 20;

    // specify the height of our grid (i.e, our world where creatures will live )
    // declared static because we don't want to make it dependent on an Orgamisn object.
    const static int gridHeight = 20;

    // pure virtual function move() for classes which will inherit from Organism.
    // this function will specify the moving behavior of an organism.
    virtual void move() = 0;

    // Pure virtual function breed() for classes which will inherit from Organism.
    // this function will specify the breeding behavior of an organism.
    // Param vecOfOrganisms: The vector which is being used to take hold all
    // organisms in the simulation.
    virtual void breed(std::vector<Organism*>& vecOfOrganisms) = 0;

    // spawn() function to spawn the organism on the map
    virtual void spawn() = 0;

    //Function isAlive will check if the current organism is alive or dead.
    virtual bool isAlive() = 0;

    // initGrid() will draw the initial empty grud.
    static void initGrid();

    //drawGrid() function will draw or redraw the grid after each time step.
    static void drawGrid();

    // clearGrid() function will clear the screen so that the grid can be updated
    static void clearGrid();

    // Set the organism x coordinate in the grid
    void setXPos(int xPos);

    // Set the organism y coordinate in the grid
    void setYPos(int yPos);

    // Get the x coordinate of the current organism
    int getXPos() const;

    // Get the y coordinate of the current organism
    int getYPos() const;

    // Function modifyGridCell() will set a new value to a specific cell
    // Param yPosition : the y coordinate (or the row) of the cell to be modified
    // Param xPosition : the x coordinate (or the column) of the cell to be modified
    // Param newValue : the new value which will be populated in the cell coordinate
    static void modifyGridCell (int yPosition, int xPosition, char newValue);

    // Function isOccupied() will check if the cell is either occupied by another Organism.
    // Returns : true : if it is occupied by another Organism, false: if it's an empty cell.
    virtual bool isOccupied(int yPosition, int xPosition) = 0;

    // Function getCellContents() will return the character stored in
    // in the y and x coordinates which are passed as arguments.
    char getCellContents(int yPosition, int xPosition);

    // Function getCurrentTimeStep() returns an integer value representing the 
    // current time step the organisms is on.
	int getCurrentTimeStep() const;
    
    // Increases the currentTimeStep private variable by one.
	void incrementTimeStep();

    // Add an organism to organisms<*Organism> vector
    static void addToVecOfOrganisms(Organism* organism);

    // Will get the corresponding Organism object from organisms vector
    // Param index: The index to retrieve the organism from the organisms vector
    static Organism* getOrganismFromVec(int index);

    // Returns the current size of the vector 
    static int getOrganismVecSize();
private:
    static char grid[gridHeight][gridWidth];  // The grid where organisms will live.
    static std::vector<Organism*> organisms;  // The vector to hold the current organisms in the simulation.
    static int currentOrganism;  // Will hold the current Organism created in the simulation.
    int xPos_;  // The organism x coordinate in the grid.
    int yPos_;  // The organism y coordinate in the grid.
    int currentTimeStep = 0; // // The number of time steps which an organisms has survived.
};



#endif /* ORGANISM_H_ */
