#include "FCell.h"

FCell::FCell(const EStatus& InitialStatus) : Neighbours(), Status(InitialStatus), NextStatus()
{
}

EStatus FCell::GetStatus()
{
	return Status;
}

void FCell::SetStatus(const EStatus& NewStatus)
{
	Status = NewStatus;
}

void FCell::AddNeighbour(FCell* Neighbour)
{
	Neighbours.push_back(Neighbour);
}

void FCell::PredictNextStatus()
{
	// Get the number of live neighbours
	int LiveNeighbours = GetLiveNeighbours();

	// Is the current cell alive?
	if (Status == EStatus::Alive)
	{
		// Less than 2 or more than 3 live neighbours?
		if ((LiveNeighbours < 2) || (LiveNeighbours > 3))
		{
			// Kill the cell
			NextStatus = EStatus::Dead;
		}
		else
		{
			// Keep cell alive
			NextStatus = EStatus::Alive;
		}
	}
	// Cell dead
	else
	{
		// 3 live neighbours?
		if (LiveNeighbours == 3)
		{
			// resurrect cell
			NextStatus = EStatus::Alive;
		}
	}
}

void FCell::Update()
{
	Status = NextStatus;
}

int FCell::GetLiveNeighbours()
{
	int LiveNeighbours = 0;
	for (FCell* Neighbour : Neighbours)
	{
		// Is the cell alive?
		if (Neighbour->GetStatus() == EStatus::Alive)
		{
			LiveNeighbours++;
		}
	}

	return LiveNeighbours;
}
