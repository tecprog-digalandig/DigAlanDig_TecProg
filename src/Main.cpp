#include "Game.h"

#define UNUSED_VAR (void)

int main(int argc, char** argv) {
    Game* game = Game::getInstance("Pedro Henrique 100119191", 1024, 600);
    game->run();

    return 0;
}
