#include "FLattice.h"

FLattice::FLattice(const int& Width) : LatticeSize(Width), ActiveSites(0)
{
	// Add cells
	PopulateLattice();
}

int FLattice::GetSize()
{
	return Cells.size();
}

void FLattice::SetInitialConditions(const std::vector<EStatus>& InitialConditions)
{
	// Iterate over each cell and set it to the corresponding state
	for (size_t i = 0; i < Cells.size(); i++)
	{
		Cells[i].SetStatus(InitialConditions[i]);
	}
}

void FLattice::RandomiseLattice()
{
	// Iterate over cells
	for (FCell& Cell : Cells)
	{
		// Randomise status
		Cell.SetStatus(static_cast<EStatus>(rand() % 2));
	}
}

void FLattice::Update()
{
	// Iterate over each cell and predict statuses
	for (FCell& Cell : Cells)
	{
		Cell.PredictNextStatus();
	}

	// Reset the number of active sites
	ActiveSites = 0;

	// Iterate over every cell and update it
	for (FCell& Cell : Cells)
	{
		Cell.Update();

		// Update active cell count
		if (Cell.GetStatus() == EStatus::Alive)
		{
			ActiveSites++;
		}
	}
}

int FLattice::GetActiveSites()
{
	return ActiveSites;
}

int FLattice::GetCenterOfMass()
{
	std::pair<int, int> CenterOfMass = std::pair<int, int>(0, 0);
	int TotalCells = 0;

	// Iterate over cells
	for (size_t CellIndex = 0; CellIndex < Cells.size(); CellIndex++)
	{
		int Row = CellIndex / LatticeSize;
		int Column = CellIndex % LatticeSize;

		// Cell active?
		if (Cells[CellIndex].GetStatus() == EStatus::Alive)
		{
			// Add row and column to sums
			CenterOfMass.first += Row;
			CenterOfMass.second += Column;

			// Increment total number of cells
			TotalCells++;
		}
	}
	CenterOfMass.first /= TotalCells;
	CenterOfMass.second /= TotalCells;

	int CenterOfMassIndex = CenterOfMass.first * LatticeSize + CenterOfMass.second;
	return CenterOfMassIndex;
}

std::string FLattice::OutputFrame()
{
	std::string Frame;

	for (size_t i = 0; i < LatticeSize; i++)
	{
		for (size_t j = 0; j < LatticeSize; j++)
		{
			int CellIndex = i * LatticeSize + j;
			Frame += std::to_string(int(Cells[CellIndex].GetStatus())) + " ";
		}
		Frame += "\n";
	}
	return Frame;
}

void FLattice::PopulateLattice()
{
	// Iterate over size of the lattice
	for (size_t CellIndex = 0; CellIndex < LatticeSize * LatticeSize; CellIndex++)
	{
		// Create new cell using random status
		FCell NewCell(static_cast<EStatus>(rand() % 2));
		// Add new cell to vector
		Cells.push_back(NewCell);
	}

	// Iterate over each cell and get the nearest neighbours
	for (size_t CellIndex = 0; CellIndex < LatticeSize * LatticeSize; CellIndex++)
	{
		// Get the 2D coordinates of the current cell
		int Row = CellIndex / LatticeSize;
		int Column = CellIndex % LatticeSize;

		// Get the nearest neighbour coordinates
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				// Make sure this is not the same coordinate
				if ((i != 0) || (j != 0))
				{
					// Use periodic boundary conditions to get the neighbouring coordinates
					int NeighbourRow = (LatticeSize + ((Row + i) % LatticeSize)) % LatticeSize;
					int NeighbourColumn = (LatticeSize + ((Column + j) % LatticeSize)) % LatticeSize;
					// Convert coordinates into 1D index
					int NeighbourIndex = NeighbourRow * LatticeSize + NeighbourColumn;

					// Get the neighbouring cell in a lattice
					FCell* Neighbour = &Cells[NeighbourIndex];
					// Add a pointer to the neighbour to the cell
					Cells[CellIndex].AddNeighbour(Neighbour);
				}
			}
		}
	}
}
