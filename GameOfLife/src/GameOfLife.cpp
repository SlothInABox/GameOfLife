// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FLattice.h"
#include <vector>
#include <fstream>
#include <string>
#include <map>

std::vector<EStatus> GetInitialConditions(const std::string& Filename);

void WriteToFile(const std::string& Output, const std::string& Filename);

void RunVisualSimulation(FLattice* Lattice);

void RunEquilibriumSimulations(FLattice* Lattice);

void RunCenterOfMassSimulation(FLattice* Lattice);

int main(int argc, char* argv[])
{
    // Create new lattice of width 50
    FLattice* Lattice = new FLattice(50);

    // Command line input?
    if (argc == 2)
    {
        // Get the input from a file
        std::vector<EStatus> InitialConditions = GetInitialConditions(argv[1]);

        // Make sure the length of the values is correct
        if (InitialConditions.size() == Lattice->GetSize())
        {
            // Update the lattice
            Lattice->SetInitialConditions(InitialConditions);
        }
        else
        {
            std::cout << "Error: Cannot read input file" << std::endl;
            return 0;
        }
    }

    int SimulationType = 0;
    while ((SimulationType < 1) || (SimulationType > 3))
    {
        // Get user input for the type of simulation to run
        std::cout << "Please enter the type of simulation to run\nVisual Simulation : 1\nEquilibrium distribution simulations : 2\nCenter of mass tracker : 3" << std::endl;
        std::cin >> SimulationType;
    }

    // Run simulation for the different types
    switch (SimulationType)
    {
    case 1:
        // Visual simulation
        RunVisualSimulation(Lattice);
        break;
    case 2:
        // Equilibrium simulations
        RunEquilibriumSimulations(Lattice);
        break;
    case 3:
        // Center of mass tracker
        RunCenterOfMassSimulation(Lattice);
        break;
    default:
        break;
    }

    delete Lattice;

    return 0;
}

std::vector<EStatus> GetInitialConditions(const std::string& Filename)
{
    // Initialise initial conditions vector
    std::vector<EStatus> InitialConditions;

    std::ifstream InputFile(Filename);
    if (InputFile.is_open())
    {
        while (!InputFile.eof())
        {
            int Value;
            InputFile >> Value;

            InitialConditions.push_back(static_cast<EStatus>(Value));
        }
        InputFile.close();
    }
    return InitialConditions;
}

void WriteToFile(const std::string& Output, const std::string& Filename)
{
    // Write frames to file
    std::ofstream OutputFile(Filename);
    if (OutputFile.is_open())
    {
        OutputFile << Output;
        OutputFile.close();
    }
    else
    {
        std::cout << "Error: cannot open output file" << std::endl;
    }
}

void RunVisualSimulation(FLattice* Lattice)
{
    // Initialise string for storing frames (heap allocate as it could get pretty big)
    std::string* Frames = new std::string();

    *Frames = Lattice->OutputFrame() + "\n";

    // Iterate for n simulations
    for (size_t t = 0; t < 500; t++)
    {
        // Update simulation
        Lattice->Update();

        // Add frame to output
        *Frames += Lattice->OutputFrame() + "\n";
    }

    // Output frames
    WriteToFile(*Frames, "Frames.txt");
    delete Frames;
}

void RunEquilibriumSimulations(FLattice* Lattice)
{
    // Initialise vector of equilibrium times
    std::vector<int> EquilibriumTimes;

    // Perform 100 simulations
    for (size_t n = 0; n < 100; n++)
    {
        // Equilibrium time
        int EquilibriumTime = 0;
        // Set the equilibrium value to the first activity value
        int EquilibriumValue = Lattice->GetActiveSites();
        int EquilibriumCount = 0;

        // Randomise simulation
        Lattice->RandomiseLattice();

        // Perform the simulation
        for (size_t t = 0; t < 5000; t++)
        {
            // Update the simulation
            Lattice->Update();
            // Get the number of active sites
            int ActiveSites = Lattice->GetActiveSites();

            // Is this the same as the previous number of active sites?
            if (ActiveSites == EquilibriumValue)
            {
                // Increment the equilibrium count
                EquilibriumCount++;
            }
            else
            {
                // Update the equilibrium value and the count
                EquilibriumValue = ActiveSites;
                EquilibriumCount = 0;
            }

            // Unchanged for a number of simulations
            if (EquilibriumCount >= 10)
            {
                // Set equilibrium time
                EquilibriumTime = t - EquilibriumCount;
                // Exit early, no need to continue simulating
                break;
            }
        }

        // Did it reach equilibrium?
        if (EquilibriumTime != 0)
        {
            // Add to equilibrium times
            EquilibriumTimes.push_back(EquilibriumTime);
        }
    }

    // Initialise string for storing
    std::string EquilibriumOutput;

    for (const int& Time : EquilibriumTimes)
    {
        // Add to string
        EquilibriumOutput += std::to_string(Time) + "\n";
    }

    // Output to file
    WriteToFile(EquilibriumOutput, "Equilibrium.txt");
}

void RunCenterOfMassSimulation(FLattice* Lattice)
{
    // Initialise string for storing the center of mass and times
    std::string COMData;

    // Run simulation
    for (size_t t = 0; t < 500; t++)
    {
        // Update the lattice
        Lattice->Update();

        // Get the center of mass
        int CenterOfMass = Lattice->GetCenterOfMass();
        COMData += std::to_string(t) + " " + std::to_string(CenterOfMass) + "\n";
    }
    WriteToFile(COMData, "CenterOfMass.txt");
}
