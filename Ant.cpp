/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * Ant.cpp
 *
 * Author: Simon Garfe Herrera
 */

#include "Ant.h"
#include <iostream>
#include <ctime>  //To be able to use the time() function

Ant::Ant() : Organism()
{
    Ant::spawn();
}

Ant::Ant(int yPosition, int xPosition) : Organism(yPosition,xPosition)
{
	Ant::spawn();
}

void Ant::spawn ()
{
    Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
}

void Ant::move()
{
	// First we need to check if the Ant is alive
    if (!(isAlive()))
    {
    	return;
    }
    srand(static_cast<unsigned int> (time(0)));

    int yPosition = Organism::getYPos();
    int xPosition = Organism::getXPos();
    Organism::Movements moveDirection = static_cast<Organism::Movements> (1 + rand() % 4);

    if (moveDirection == Organism::Movements::DOWN)
    {
        int newYPosition = yPosition + 1;

        //Perform grid boundary checking and also check the the cell is unoccupied.
        if ( (newYPosition) >= Organism::gridHeight || (isOccupied(newYPosition, xPosition)) )
        {
        	return;
        }

        else
        {
            // Turn the previous Ant position to an empty cell.
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

            //Set the new cell to occupy the corresponding Ant symbol.
            Organism::setYPos(newYPosition);
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
        }
    }

    else if (moveDirection == Organism::Movements::UP)
    {
        int newYPosition = yPosition - 1;

        //Perform grid boundary checking and also check the the cell is unoccupied.
        if ( (newYPosition) < 0 || (isOccupied(newYPosition, xPosition)) )
        {
        	return;
        }

        else
        {
            // Turn the previous Ant position to an empty cell.
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

            //Set the new cell to occupy the corresponding Ant symbol.
            Organism::setYPos(newYPosition);
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
        }

    }

    else if (moveDirection == Organism::Movements::RIGHT)
    {
        int newXPosition = xPosition + 1;

        //Perform grid boundary checking and also check the the cell is unoccupied.
        if ( (newXPosition) >= Organism::gridWidth || (isOccupied(yPosition, newXPosition)) )
        {
        	return;
        }

        else
        {
            // Turn the previous Ant position to an empty cell.
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

            //Set the new cell to occupy the corresponding Ant symbol.
            Organism::setXPos(newXPosition);
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
        }

    }

    else if (moveDirection == Organism::Movements::LEFT)
    {
        int newXPosition = xPosition - 1;

        //Perform grid boundary checking and also check the the cell is unoccupied.
        if ( (newXPosition) < 0 || (isOccupied(yPosition, newXPosition)) )
        {
        	return;
        }

        else
        {
            // Turn the previous Ant position to an empty cell.
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

            //Set the new cell to occupy the corresponding Ant symbol.
            Organism::setXPos(newXPosition);
            Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
        }

    }

    Organism::incrementTimeStep();

}

void Ant::breed(std::vector<Organism*>& vecOfOrganisms)
{
    int yPosition = Organism::getYPos();
    int xPosition = Organism::getXPos();

    // Start checking in round-robin style which adjacent cell is available.
    // We'll check for an above cell first
    if (!(isOccupied(yPosition - 1, xPosition)) && (yPosition - 1) >= 0)
    {
        int newYPosition = yPosition - 1;

        vecOfOrganisms.push_back(new Ant(newYPosition, xPosition));
    }


    // We'll check for a cell downwards
    else if (!(isOccupied(yPosition + 1, xPosition)) && (yPosition + 1) < Organism::gridHeight )
    {
        int newYPosition = yPosition + 1;

        vecOfOrganisms.push_back(new Ant(newYPosition, xPosition));
    }

    // We'll check for a cell to the right
    else if (!(isOccupied(yPosition, xPosition + 1)) && (xPosition + 1 ) < Organism::gridWidth)
    {
        int newXPosition = xPosition + 1;
        vecOfOrganisms.push_back(new Ant(yPosition, newXPosition));
    }

    // We'll check for a cell to the left
    else if (!(isOccupied(yPosition, xPosition - 1)) && (xPosition - 1) >= 0)
    {
    	int newXPosition = xPosition - 1;
    	vecOfOrganisms.push_back(new Ant(yPosition, newXPosition));
    }

    //else no breeding occurs
}


bool Ant::isAlive()
{
	int yPosition = Organism::getYPos();
	int xPosition = Organism::getXPos();

	if(Organism::getCellContents(yPosition,xPosition) != symbol)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool Ant::isOccupied(int yPosition, int xPosition)
{
	if (Organism::getCellContents(yPosition,xPosition) != Organism::emptyCell)
	{
		return true;
	}

	else
	{
		return false;
	}
}


