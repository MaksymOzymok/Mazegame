#include <startscreen.h>
#include "gameconstans.h"
#include "mazegenerator.h"
#include "gamelogic.h"

int main()
{
    while (doesUserWantsToPlay())
    {
        playMazeGame();
    }
}