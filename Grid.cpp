#include "pch.h"
#include "Grid.h"
#include <iostream>


int Grid::getNeighbours(int x, int z)
{
    int neighbourCount = 0;
    if (cellMatrix[(x - 1)][z].GetState() == 1 && x != 0) // middle left
        neighbourCount++;
    if (cellMatrix[(x - 1)][(z - 1)].GetState() == 1 && x != 0 && z != 0) // top left
        neighbourCount++;
    if (cellMatrix[(x - 1)][(z + 1)].GetState() == 1 && x != 0 && z != gridSize) // bottom left
        neighbourCount++;
    if (cellMatrix[(x)][(z - 1)].GetState() == 1 && z != 0) // middle top
        neighbourCount++;
    if (cellMatrix[(x)][(z + 1)].GetState() == 1 && z != gridSize) // middle bottom
        neighbourCount++;
    if (cellMatrix[(x + 1)][z].GetState() == 1 && x != gridSize) // middle right
        neighbourCount++;
    if (cellMatrix[(x + 1)][(z + 1)].GetState() == 1 && x != gridSize && z != gridSize) // top right
        neighbourCount++;
    if (cellMatrix[(x + 1)][(z - 1)].GetState() == 1 && x != gridSize && z != 0) // bottom right
        neighbourCount++;
    return neighbourCount;
}


void Grid::initializeGrid()
{
    int border          = 1;
    _isPlayerSet        = false;
    _isCollectibleSet   = false;
    _isLevelSolvable    = false;
    _aStardistance      = false;
    _distSearchResult   = 1;

    Clear();
    _aStarCalc.ResetDistance();

    // here i and j are x and y repectively from Grid::getNeighbours(int x, int z) where we did the matrix definitions

    while (!_isPlayerSet && !_isCollectibleSet && !_isLevelSolvable)
    {
        for(int i = 0; i <= gridSize - 1; i++ )
        {
            for(int j = 0; j <= gridSize - 1; j++)
            {
                if (i == 0 || i == (gridSize - 1) || j == 0 || j == (gridSize - 1) )
                {
                    cellMatrix[i][j].SetState(border);
                    stateMatrix[j][i] = border;
                }
                else //time to define all the other states
                {
                    /*PLAYER SET*/
                    if (!_isPlayerSet) 
                    {
                        int randomValue = (rand() % 100 + 1);
                        if (randomValue > 70 - probabilityToBeAlive)
                        {
                            // player
                            cellMatrix[i][j].SetState(2); 
                            _cellPlayer = cellMatrix[i][j];

                            stateMatrix[j][i] = 2;
                            _playerIndex = make_pair(j, i);

                            _isPlayerSet = true;
                            continue;
                        }
                    }

                    /*COLLECTIBLE SET*/
                    if(!_isCollectibleSet)
                    {
                        int randomValue = (rand() % 100 + 1);
                        if (randomValue % probabilityToBeAlive == 0)
                        {
                            // collectible (pick ups)
                            cellMatrix[i][j].SetState(3); 
                            _cellCollectible = cellMatrix[i][j];

                            stateMatrix[j][i] = 3;
                            _collectibleIndex = make_pair(j, i);

                            _isCollectibleSet = true;
                            continue;
                        }
                    }

                    int randomValue = (rand() % 100 + 1);
                    bool aliveState = randomValue > 100 - probabilityToBeAlive ? 1 : 0;
                    cellMatrix[i][j].SetState(aliveState);
                    stateMatrix[j][i] = aliveState;
                }
            }
        }

        // CHECKS For if the dungeon is solvable
        // ALSO we should calculate the distance here too

        _distSearchResult = _aStarCalc.aStarSearch(stateMatrix, _playerIndex, _collectibleIndex);

        // Pointers scary
        if (*_aStarCalc.GetDistance() > 10) {
            _aStardistance = true;
        }
        else 
        {
            _aStardistance = false;
        }

        if (_distSearchResult == 1 && _aStardistance) 
        {
            _isLevelSolvable = true;
        }
    }
}

int* Grid::GetDistance()
{
    int distance = *_aStarCalc.GetDistance();
    int* distancePointer = &distance;
    return distancePointer;
}

void Grid::ResetPlayerInStateMatrix(int r, int c)
{
    for (int z = 0; z < gridSize - 1; z++)
    {
        for (int x = 0; x < gridSize - 1; x++)
        {
            if (cellMatrix[z][x].GetState() == 2)
            {
                stateMatrix[r][c] = 2;
                _playerIndex = make_pair(r, c);
            }
        }
    }
}

void Grid::nextGeneration()
{
    gridInitialised = false; // collisions
    int nextGrid[101][101];
    for (int z = 0; z < gridSize - 1; z++)
        for (int x = 0; x < gridSize - 1; x++)
            if (z == 0 || z == gridSize - 1 || x == 0 || x == gridSize - 1) {
                // border, do nothing
            }
            else {
                nextGrid[x][z] = getNeighbours(x, z);
            }
    for (int z = 0; z < gridSize - 1; z++)
        for (int x = 0; x < gridSize - 1; x++)
        {
            if (z == 0 || z == gridSize - 1 || x == 0 || x == gridSize - 1) {
                // border, do nothing
            }
            else {
                if (cellMatrix[x][z].GetState() == 1)
                {
                    if (nextGrid[x][z] > 3)
                    {
                        cellMatrix[x][z].SetState(0);
                        haveChanged.push_back(CellPoint(x, z, 0));
                    }
                    if (nextGrid[x][z] < 2)
                    {
                        cellMatrix[x][z].SetState(0);
                        haveChanged.push_back(CellPoint(x, z, 0));
                    }
                }
                else if (cellMatrix[x][z].GetState() == 3)
                {
                    // do nothing to collectible box
                }
                else
                {
                    if (nextGrid[x][z] == 3) {
                        cellMatrix[x][z].SetState(1);
                        haveChanged.push_back(CellPoint(x, z, 1));
                    }
                }
            }
        }
}

//Clear grid and stateMatrix
void Grid::Clear()
{
    for (int z = 0; z < gridSize; z++)
    {
        for (int x = 0; x < gridSize; x++)
        {
            stateMatrix[z][x] = -1;
            cellMatrix[x][z].SetState(-1);
        }
    }
}

//Return grid size
int Grid::Size() {
    return gridSize;
}


//GridInitialisation
bool Grid::GetInitialised() {
    return gridInitialised;
}

void Grid::SetInitialised(bool state) {
    gridInitialised = state;
}

Cell Grid::GetCollectibleCell() {
    return _cellCollectible;
}

Cell Grid::GetPlayerCell() {
    return _cellPlayer;
}