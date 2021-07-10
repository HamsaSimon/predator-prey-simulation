/*
 * Jonathan S. Weissman
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 *
 * Final Project
 * Main.cpp
 *
 *  Author: Simon Garfe Herrera
 */

#include <iostream>
#include <vector>
#include "Organism.h"
#include "Ant.h"
#include "DoodleBug.h"

int main ()
{
    std::cout << "***************************************************************\n";
    std::cout << "Predator Prey Simulation DoodleBugs (X) vs Ants (O) Version 0.1\n";
    std::cout << "***************************************************************\n";

    int numOfDoodleBugs;
    int numOfAnts;

    // prompt user for the number of DoodleBugs
    std::cout << "How many DoodleBugs do you want in this simulation: ";
    std::cin >> numOfDoodleBugs;

    // prompt user for the number of Ants
    std::cout << "How many Ants do you want in this simulation: ";
    std::cin >> numOfAnts;

    // Build the map
    Organism::initGrid();

    // Save the total number of Organisms
    int totalOrganisms = numOfDoodleBugs + numOfAnts;

    
    

    // Instantiate vector of Organism elements
    for (int i = 0; i < totalOrganisms; ++i)
    {
        if( i < numOfDoodleBugs)
        {
            Organism::addToVecOfOrganisms(new DoodleBug);   
        }

        else //Ant initialization
        {
            Organism::addToVecOfOrganisms(new Ant);
        }
    }

    Organism::clearGrid();
    Organism::drawGrid();
    std::cout << "Grid has been populated\n";

    // Ask for user input


    int currentTimeStep = 1;

    Organism* organism;

    std::cout << "\n\nPress 'n' character to move to the next time step"
    		" or any other key to quit:";
    char input;

    std::cin >> input;

    while (input == 'n')
    {
    	Organism::clearGrid();

        // Make doodlebugs move first
        for(int i = 0; i < Organism::getOrganismVecSize(); ++i)
        {
            organism = Organism::getOrganismFromVec(i);

            if(dynamic_cast<DoodleBug*>(organism) != nullptr)
            {
                organism->move();
            }
            
        }
        
        Organism::drawGrid();

        std::cout << "\n\nPress 'n' character to move the Ants: ";
        std::cin >> input;
        // Then Ants Move
        for(int i = 0; i < Organism::getOrganismVecSize(); ++i)
        {
            organism = Organism::getOrganismFromVec(i);

            if(dynamic_cast<Ant*>(organism) != nullptr)
            {
                organism->move();
            }
            
        }
        
        Organism::drawGrid();
        

        std::cout << "\n\nPress 'n' character to move to the next time step"
    		" or any other key to quit:";
        std::cin >> input;

    }

    std::cout << "\nSimulation finished \n";
}


