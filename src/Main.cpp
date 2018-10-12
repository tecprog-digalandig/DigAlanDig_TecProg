#include <fstream>
#include <iostream>
#include "Game.h"
#include "StageState.h"
#include "TitleState.h"
#ifdef __ANDROID__
#include "androidbuf.h"
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
    std::ofstream out("cout.txt");
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    std::ofstream err("cerr.txt");
    std::streambuf* cerrbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(err.rdbuf());
#endif
#ifdef __ANDROID__
    std::cout.rdbuf(new androidbuf(ANDROID_LOG_INFO));
    std::cerr.rdbuf(new androidbuf(ANDROID_LOG_ERROR));
#endif
    srand(time(0));

    Game* game = Game::GetInstance("Groundhog Dig", 1024, 768);
    game->Push(new TitleState());
    game->Run();

#ifdef _WIN32
    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);
#endif

    exit(0);
}
