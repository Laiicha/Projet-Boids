#include <iostream>
#include "Game.h"

int main()
{
    int nbre_preadateurs = 256;
    int nbre_proies = 8;
    Game game;
    game.Run(nbre_preadateurs, nbre_proies);
    return 0;
}
