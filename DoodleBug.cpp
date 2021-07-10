/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * DoodleBug.cpp
 *
 * Author: Simon Garfe Herrera
 */

#include "DoodleBug.h"
#include <iostream>
#include <ctime>  //To be able to use the time() function

DoodleBug::DoodleBug(): Organism()
{
    DoodleBug::spawn();
}

DoodleBug::DoodleBug(int yPosition, int xPosition) : Organism(yPosition,xPosition)
{
	DoodleBug::spawn();
}

void DoodleBug::spawn ()
{
    Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
}

void DoodleBug::move()
{
	// First check if DoodleBug is alive.
	if (!(isAlive()) || starved == true)
	{
		return;
	}

    int yPosition = Organism::getYPos();
    int xPosition = Organism::getXPos();

    // Find if an Ant is an adjacent cell. Start in the above adjacent cell
    if( Organism::getCellContents(yPosition - 1,xPosition) == 'O' && (yPosition - 1) >= 0 )
    {
    	stepsWithoutFood = 0;
    	Organism::setYPos(yPosition - 1);

        Organism::modifyGridCell(yPosition - 1,xPosition,symbol);

        //modify the cell which we were previously at
        Organism::modifyGridCell(yPosition,xPosition,Organism::emptyCell);
    }

    // See if there's an Ant in the bottom adjacent cell.
    else if ( Organism::getCellContents(yPosition + 1,xPosition) == 'O' && (yPosition + 1) < Organism::gridHeight )
    {

    	stepsWithoutFood = 0;
    	Organism::setYPos(yPosition + 1);
    	Organism::modifyGridCell(yPosition + 1,xPosition,symbol);

        //modify the cell which we were previously at
        Organism::modifyGridCell(yPosition,xPosition,Organism::emptyCell);
    }

    // See if there's an Ant in the left adjacent cell.
    else if( Organism::getCellContents(yPosition,xPosition - 1) == 'O' && (xPosition - 1) >= 0)
	{
    	stepsWithoutFood = 0;
    	Organism::setXPos(xPosition - 1);
    	Organism::modifyGridCell(yPosition,xPosition - 1,symbol);

        //modify the cell which we were previously at
        Organism::modifyGridCell(yPosition,xPosition,Organism::emptyCell);
	}

    // See if there's an Ant in the right adjacent cell.
    else if ( Organism::getCellContents(yPosition, xPosition + 1) == 'O' && (xPosition + 1) < Organism::gridWidth )
    {
    	stepsWithoutFood = 0;
    	Organism::setXPos(xPosition + 1);
    	Organism::modifyGridCell(yPosition,xPosition + 1,symbol);

        //modify the cell which we were previously at
        Organism::modifyGridCell(yPosition,xPosition,Organism::emptyCell);
    }

    // Else we will move randomly to one of the adjacent cell.
    else
    {
    	stepsWithoutFood += 1;

    	if (stepsWithoutFood == 3)
    	{
    		starve();
    		return;
    	}

    	srand(static_cast<unsigned int>(time(0)));

    	Organism::Movements moveDirection = static_cast<Organism::Movements> (1 + rand() % 4);

        if (moveDirection == Organism::Movements::DOWN)
        {
            int newYPosition = yPosition + 1;

            //Perform grid boundary checking and also check the the cell is unoccupied.
            if ( (newYPosition) >= Organism::gridHeight || isOccupied(newYPosition, xPosition) )
            {
            	return;
            }

            else
            {
                // Turn the previous DoodleBug position to an empty cell.
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

                //Set the new cell to occupy the corresponding DoodleBug symbol.
                Organism::setYPos(newYPosition);
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
            }
        }

        else if (moveDirection == Organism::Movements::UP)
        {
            int newYPosition = yPosition - 1;

            //Perform grid boundary checking and also check the the cell is unoccupied.
            if ( (newYPosition) < 0 || isOccupied(newYPosition, xPosition) )
            {
            	return;
            }

            else
            {
                // Turn the previous Ant position to an empty cell.
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

                //Set the new cell to occupy the corresponding DoodleBug symbol.
                Organism::setYPos(newYPosition);
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
            }
        }

        else if (moveDirection == Organism::Movements::RIGHT)
        {
            int newXPosition = xPosition + 1;

            //Perform grid boundary checking and also check the the cell is unoccupied.
            if ( newXPosition >= Organism::gridWidth || isOccupied(yPosition, newXPosition) )
            {
            	return;
            }

            else
            {
                // Turn the previous Ant position to an empty cell.
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

                //Set the new cell to occupy the corresponding DoodleBug symbol.
                Organism::setXPos(newXPosition);
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
            }

        }

        else if (moveDirection == Organism::Movements::LEFT)
        {
            int newXPosition = xPosition - 1;

            //Perform grid boundary checking and also check the the cell is unoccupied.
            if ( newXPosition < 0 || isOccupied(yPosition, newXPosition) )
            {
            	return;
            }

            else
            {
                // Turn the previous Ant position to an empty cell.
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), Organism::emptyCell);

                //Set the new cell to occupy the corresponding DoodleBug symbol.
                Organism::setXPos(newXPosition);
                Organism::modifyGridCell(Organism::getYPos(), Organism::getXPos(), symbol);
            }

        }
    }

    Organism::incrementTimeStep();
}

void DoodleBug::breed(std::vector<Organism*>& vecOfOrganisms)
{
    int yPosition = Organism::getYPos();
    int xPosition = Organism::getXPos();


    // Start checking in round-robin style which adjacent cell is available.
    // We'll check for an above cell first
    if (!(isOccupied(yPosition - 1, xPosition)) && (yPosition - 1) >= 0)
    {
         int newYPosition = yPosition - 1;
         vecOfOrganisms.push_back(new DoodleBug(newYPosition, xPosition));
    }

    // We'll check for a cell downwards
    else if (!(isOccupied(yPosition + 1, xPosition)) && (yPosition + 1) < Organism::gridHeight )
    {
        int newYPosition = yPosition + 1;
        vecOfOrganisms.push_back(new DoodleBug(newYPosition, xPosition));
    }

    // We'll check for a cell to the right
    else if (!(isOccupied(yPosition, xPosition + 1)) && (xPosition + 1 ) < Organism::gridWidth)
    {
        int newXPosition = xPosition + 1;
        vecOfOrganisms.push_back(new DoodleBug(yPosition, newXPosition));
    }

    // We'll check for a cell to the left
    else if (!(isOccupied(yPosition, xPosition - 1)) && (xPosition - 1) >= 0)
    {
        int newXPosition = xPosition - 1;
        vecOfOrganisms.push_back(new DoodleBug(yPosition, newXPosition));
    }
    //else no breeding occurs
}

bool DoodleBug::isAlive()
{
	int yPosition = Organism::getYPos();
	int xPosition = Organism::getXPos();

	if(Organism::getCellContents(yPosition, xPosition) != symbol )
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool DoodleBug::isOccupied(int yPosition, int xPosition)
{
	if (Organism::getCellContents(yPosition,xPosition) == symbol)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void DoodleBug::starve()
{
	int yPosition = Organism::getYPos();
	int xPosition = Organism::getXPos();

	Organism::modifyGridCell(yPosition, xPosition,Organism::emptyCell);

	starved = true;
}

