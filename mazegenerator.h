#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <iostream>
#include <vector>
#include <stack>
#include <random>

#include "gameconstans.h"

struct MazeCell
{
    size_t mX;
    size_t mY;
    bool mVisited;

    MazeCell(size_t x, size_t y, bool visited)
        :mX(x), mY(y) , mVisited(visited)
    {}
};

bool checkForVisited(const std::vector<MazeCell> &array);

size_t getIndexOfCell(MazeCell cell , const std::vector<MazeCell> &array);

std::vector<MazeCell> getNeighbors(MazeCell current, const std::vector<MazeCell> &cells);

void removeWall(std::array<std::array<char, cMazeColumns>, cMazeRows> &prMaze, MazeCell first , MazeCell second);

void generateMaze(Maze &prMaze);

#endif // MAZEGENERATOR_H