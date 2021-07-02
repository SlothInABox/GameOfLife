#pragma once
#include <vector>
#include <iostream>

enum class EStatus
{
	Dead,
	Alive
};

class FCell
{
public:
	// Constructor
	FCell(const EStatus& InitialStatus);

	// Method to get the status of the cell
	EStatus GetStatus();
	// Method to update the cell status
	void SetStatus(const EStatus& NewStatus);

	// Method to add a new neighbour
	void AddNeighbour(FCell* Neighbour);

	// Method to predict the next status of a cell
	void PredictNextStatus();

	// Method to update a cell
	void Update();
private:
	// Status of the cell
	EStatus Status;
	// Next status
	EStatus NextStatus;
	// Pointers to cell neighbours
	std::vector<FCell*> Neighbours;

	// Method to get the number of live neighbours
	int GetLiveNeighbours();
};

