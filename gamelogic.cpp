#include "gamelogic.h"

void drawMaze(Maze &maze)
{
    for (size_t row = 0; row < cMazeRows; row++)
    {
        for (size_t column = 0; column < cMazeColumns; column++)
        {
            std::cout << maze[row][column];
        }

        std::cout << std::endl;
    }
}

bool scanForChar(const Maze &maze,
                 const char charToFind,
                 size_t &prCharRow,
                 size_t &prCharColumn)
{
    for (size_t row = 0; row < cMazeRows; row++)
    {
        for (size_t column = 0; column < cMazeColumns; column++)
        {
            if (maze[row][column] == charToFind)
            {
                prCharRow = row;
                prCharColumn = column;
                return true;
            }
        }
    }

    return false;
}
char moveAndGather(size_t row,
                   size_t column,
                   const std::string &command,
                   Maze &prMaze, bool isKeyFound)
{
    char rCharMovedOnto = cEmptySymbol;

    // Take character out from map
    prMaze[row][column] = cEmptySymbol;

    if (command == "a")
    {
        rCharMovedOnto = prMaze[row][column - 1];

        if (isStepAvaliable(rCharMovedOnto,isKeyFound))
        {
            column--;
        }
    }

    if (command == "d")
    {
        rCharMovedOnto = prMaze[row][column + 1];

        if (isStepAvaliable(rCharMovedOnto,isKeyFound))
        {
            column++;
        }
    }

    if (command == "w")
    {
        rCharMovedOnto = prMaze[row - 1][column];

        if (isStepAvaliable(rCharMovedOnto,isKeyFound))
        {
            row--;
        }
    }

    if (command == "s")
    {
        rCharMovedOnto = prMaze[row + 1][column];

        if (isStepAvaliable(rCharMovedOnto,isKeyFound))
        {
            row++;
        }
    }

    // Place character back with new position
    prMaze[row][column] = cCharacterSymbol;

    return rCharMovedOnto;
}

void gameMessage(const std::string &message)
{
    {
        std::cout << std::endl << message << std::endl << std::endl;
    }
}

bool moveCharacterAndCheckIfExitFound(Maze &prMaze, bool &rKeyFound)
{
    bool rExitFound = false;

    size_t charRow = 1;
    size_t charColumn = 1;
    if (scanForChar(prMaze, cCharacterSymbol, charRow, charColumn))
    {
        std::cout << "Command (a - left, d - right, w - up, s - down):";
        std::string command;
        std::cin >> command;

        const char charMovedOnto = moveAndGather(charRow, charColumn, command, prMaze,rKeyFound);

        if (charMovedOnto == cWallSymbol)
        {
            gameMessage("Cannot move here!");
        }
        if (charMovedOnto == cKeySymbol)
        {
            gameMessage("You found a key");
            rKeyFound = true;

        }
        if (charMovedOnto == cExitSymbol && rKeyFound == true)
        {
            gameMessage("Exit found!");
            rExitFound = true;
        }
    }
    else
    {
        gameMessage("Error: cannot find char!");
    }

    return rExitFound;
}
void playMazeGame()
{
    std::cout << "LETS START!" << std::endl;

    Maze maze;
    generateMaze(maze);

    bool isKeyFound = false;
    do
    {
        drawMaze(maze);
    }
    while (!moveCharacterAndCheckIfExitFound(maze,isKeyFound));
}

bool isStepAvaliable(char charMovedOnto, bool isKeyFound)
{
    if(charMovedOnto == cWallSymbol || (charMovedOnto == cExitSymbol && isKeyFound == false))
    {
        return false;
    }
    return true;

}