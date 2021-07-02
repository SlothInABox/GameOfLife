#pragma once
#include "FCell.h"
#include <vector>
#include <iostream>
#include <string>

class FLattice
{
public:
	// Constructor
	FLattice(const int& Width);

	// Size of lattice
	int GetSize();

	// Member function for setting the cells to values in an array
	void SetInitialConditions(const std::vector<EStatus>& InitialConditions);

	void RandomiseLattice();

	// Update function
	void Update();

	// Get the number of active sites
	int GetActiveSites();

	// Get the center of mass of the lattice
	int GetCenterOfMass();

	// Output cells to lattice history
	std::string OutputFrame();
private:
	// Lattice size
	int LatticeSize;
	// Vector of cells
	std::vector<FCell> Cells;
	// Number of active sites
	int ActiveSites;

	// String containing state history for the object
	std::string LatticeHistory;

	// Creating cells
	void PopulateLattice();
};

