#include <fstream>
#include <iostream>
#include "Game.h"
#include "TitleState.h"

int main(int argc, char** argv) {
#ifdef _WIN32
    std::ofstream out("cout.txt");
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    std::ofstream err("cerr.txt");
    std::streambuf* cerrbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(err.rdbuf());
#endif

    Game* game = Game::GetInstance("Pedro Henrique 100119191", 1024, 600);
    game->Push(new TitleState());
    game->Run();

#ifdef _WIN32
    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);
#endif

    return 0;
}
