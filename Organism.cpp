/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * Organism.cpp
 *
 * Author: Simon Garfe Herrera
 */


#include <iostream>
#include <ctime>    // contains function prototype for function time
#include "Organism.h"

// Static data initialization
char Organism::grid[Organism::gridHeight][Organism::gridWidth] = {'.'};
std::vector<Organism*> Organism::organisms;
int Organism::currentOrganism = 0;

Organism::Organism()
{
    Organism::currentOrganism++;

    int xPosition = 0;
    int yPosition = 0;
    bool isEmptyCell = false;

    srand(static_cast<unsigned int>(time(0)));

    while(!isEmptyCell)
    {
        xPosition = (0 + rand() % (gridWidth-1));
        yPosition = (0 + rand() % (gridHeight-1));

        //condition to check if position is not empty
        if(grid[yPosition][xPosition] != emptyCell)
        {
            //std::cout << "\nThe cell is not empty\n";
            //std::cout << "grid[yPosition][xPosition] = " << grid[yPosition][xPosition];
            //std::cout << "\n";
            isEmptyCell = false;
        }

        else
        {
            isEmptyCell = true;
            setXPos(xPosition);
            setYPos(yPosition);
        }
    }
}

Organism::Organism(int yPosition, int xPosition)
{
    Organism::currentOrganism++;
    setYPos(yPosition);
    setXPos(xPosition);
}

void Organism::initGrid()
{
    for (int i = 0; i < gridHeight; ++i)
    {
        for(int j = 0; j < gridWidth; ++j)
        {
            grid[i][j] = emptyCell;
        }
    }
}

void Organism::drawGrid()
{
    for (int i = 0; i < gridHeight; ++i)
    {
        for(int j = 0; j < gridWidth; ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << "\n";
    }
}

//Implementation found here: https://www.cplusplus.com/forum/articles/10515/
void Organism::clearGrid()
{
    std::cout << std::string(100,'\n');
}

void Organism::setXPos(int xPos)
{
    // Check that is a valid value, that is,
    // we are not stepping outside the boundaries of the grid.
    if (xPos >= gridWidth)
    {
        std::cout << "Error wrong X position\n";
        return;
    }

    xPos_ = xPos;
}

void Organism::setYPos(int yPos)
{
    // Check that is a valid value, that is,
    // we are not stepping outside the boundaries of the grid.
    if (yPos >= gridHeight)
    {
        std::cout << "Error wrong Y Position\n";
        return;
    }

    yPos_ = yPos;
}

int Organism::getXPos() const
{
    return xPos_;
}

int Organism::getYPos() const
{
    return yPos_;
}

void Organism::modifyGridCell(int yPosition, int xPosition, char newValue)
{
    grid[yPosition][xPosition] = newValue;
}


char Organism::getCellContents(int yPosition, int xPosition)
{
	char cellSymbol = Organism::grid[yPosition][xPosition];

	return cellSymbol;
}

int Organism::getCurrentTimeStep() const {
	return currentTimeStep;
}

void Organism::incrementTimeStep()
{
	currentTimeStep += 1;
}

void Organism::addToVecOfOrganisms(Organism* organism)
{
    Organism::organisms.push_back(organism);
}

Organism* Organism::getOrganismFromVec(int index)
{
    return Organism::organisms[index];
}

int Organism::getOrganismVecSize()
{
    return Organism::organisms.size();
}
