#pragma once
#include "pch.h"
#include "Cell.h"
#include "A_starAlgo.h"

class Grid {

public:

	std::vector<CellPoint> haveChanged;

	void ResetPlayerInStateMatrix(int, int);
	void initializeGrid();
	void nextGeneration();
	void SetInitialised(bool state);
	void Clear();

	bool GetInitialised();

	int getNeighbours(int x, int z);
	int Size();

	//AStar
	int* GetDistance();

	Cell GetCollectibleCell();
	Cell GetPlayerCell();
	Cell cellMatrix[27][27];


private:

	std::pair<int, int> _collectibleIndex;
	std::pair<int, int> _playerIndex;
	
	const int gridSize = 27;
	const int probabilityToBeAlive = 30;
	
	int stateMatrix[27][27];
	int _distSearchResult;

	bool gridInitialised = false;
	bool _isPlayerSet, _isCollectibleSet;
	bool _isLevelSolvable;
	bool _aStardistance;

	Cell _cellCollectible;
	Cell _cellPlayer;

	AStar _aStarCalc;
	
};