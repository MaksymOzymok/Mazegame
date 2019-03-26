#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <string>
#include <iostream>

#include "gameconstans.h"
#include "mazegenerator.h"

bool isStepAvaliable(char charMovedOnto, bool isKeyFound);

void drawMaze(Maze &maze);

bool scanForChar(const Maze &maze,
                 const char charToFind,
                 size_t &prCharRow,
                 size_t &prCharColumn);

char moveAndGather(size_t row,
                   size_t column,
                   const std::string &command,
                   Maze &prMaze, bool isKeyFound);

void gameMessage(const std::string& message);


bool moveCharacterAndCheckIfExitFound(Maze &prMaze, bool &rKeyFound);

void playMazeGame();



#endif // GAMELOGIC_H