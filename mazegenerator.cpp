#include "mazegenerator.h"


size_t getIndexOfCell(MazeCell cell, const std::vector<MazeCell> &array)
{
    size_t index = 0;
    for(auto temp : array)
    {
        if(cell.mX == temp.mX && cell.mY == temp.mY)
        {
            return index;
        }
        index++;
    }
    return index;
}

bool checkForVisited(const std::vector<MazeCell> &array)
{

    for(auto temp : array)
    {
        if(temp.mVisited == false)
        {
            return true;
        }
    }
    return false;
}

std::vector<MazeCell> getNeighbors(MazeCell current, const std::vector<MazeCell> &cells)
{
    std::vector<MazeCell> result;
    for(auto temp : cells)
    {
        if((abs(static_cast<int>(temp.mX - current.mX)) <= 2) && abs(static_cast<int>(temp.mY - current.mY)) == 0
               && temp.mVisited == false)
        {
            result.push_back(temp);
        }
        else if(abs(static_cast<int>(temp.mY - current.mY)) <= 2 && abs(static_cast<int>(temp.mX - current.mX)) == 0
                && temp.mVisited == false)
        {
            result.push_back(temp);
        }
    }
    return result;
}

void removeWall(Maze &prMaze, MazeCell first , MazeCell second)
{
    if(first.mX == second.mX)
    {
        if(first.mY > second.mY)
        {
            prMaze[first.mX][first.mY - 1] = cEmptySymbol;
        }
        else
        {
            prMaze[first.mX][first.mY + 1] = cEmptySymbol;
        }
    }
    else
    {
        if(first.mX > second.mX)
        {
            prMaze[first.mX - 1][first.mY] = cEmptySymbol;
        }
        else
        {
            prMaze[first.mX + 1][first.mY] = cEmptySymbol;
        }
    }
}

void generateMaze(Maze &prMaze)
{
    for (size_t row = 0; row < cMazeRows; row++)
    {
        for (size_t column = 0; column < cMazeColumns; column++)
        {
            if(row % 2 == 0 || column % 2 == 0)
            {
                prMaze[row][column] = cWallSymbol;
            }
            else
            {
                prMaze[row][column] = cEmptySymbol;
            }
        }
    }

    std::vector<MazeCell> lMazeCells;
    for (size_t row = 0; row < cMazeRows; row++)
    {
        for (size_t column = 0; column < cMazeColumns; column++)
        {
            if(prMaze[row][column] == cEmptySymbol)
            {
                lMazeCells.push_back(MazeCell(row,column,false));
            }
        }
    }

    std::random_device rd;
    std::mt19937 mt{rd()};

    std::uniform_int_distribution<size_t> randomCell = std::uniform_int_distribution<size_t>(0,lMazeCells.size()-1);
    size_t currentIndex = randomCell(mt);

    lMazeCells[currentIndex].mVisited = true;

    std::stack<MazeCell> stackOfCells;
    while(checkForVisited(lMazeCells))
    {
        auto lNeighbours = getNeighbors(lMazeCells[currentIndex],lMazeCells);
        if(lNeighbours.size()>0)
        {
            stackOfCells.push(lMazeCells[currentIndex]);

            std::uniform_int_distribution<size_t> randomNeighbour = std::uniform_int_distribution<size_t>(0,lNeighbours.size()-1);
            size_t randomNeighbourIndex = randomNeighbour(mt);

            removeWall(prMaze,lMazeCells[currentIndex],lNeighbours[randomNeighbourIndex]);
            currentIndex = getIndexOfCell(lNeighbours[randomNeighbourIndex],lMazeCells);
            lMazeCells[currentIndex].mVisited = true;
        }
        else if(!stackOfCells.empty())
        {
            stackOfCells.pop();
            currentIndex = getIndexOfCell(stackOfCells.top(),lMazeCells);
        }
        else
        {
            for(auto temp : lMazeCells)
            {
                if(temp.mVisited == false)
                {
                    currentIndex = getIndexOfCell(temp,lMazeCells);
                }
            }
        }
    }

    prMaze[1][1] = cCharacterSymbol;


    std::uniform_int_distribution<size_t> keyGenerator = std::uniform_int_distribution<size_t>(0, lMazeCells.size() - 1);

    std::uniform_int_distribution<size_t> exitGenerator = std::uniform_int_distribution<size_t>(0, lMazeCells.size() - 1);

    size_t keyIndex = keyGenerator(mt);
    size_t exitIndex = exitGenerator(mt);

    prMaze[lMazeCells[keyIndex].mX][lMazeCells[keyIndex].mY] = cKeySymbol;
    prMaze[lMazeCells[exitIndex].mX][lMazeCells[exitIndex].mY] = cExitSymbol;

}