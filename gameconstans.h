#ifndef GAMECONSTANS_H
#define GAMECONSTANS_H

#include <array>

const size_t cMazeColumns = 21;
const size_t cMazeRows = 21;

const char cEmptySymbol = ' ';
const char cWallSymbol = 'X';
const char cCharacterSymbol = '@';
const char cExitSymbol = '#';
const char cKeySymbol = '%';

using Maze = std::array<std::array<char, cMazeColumns>, cMazeRows>;

#endif // GAMECONSTANS_H