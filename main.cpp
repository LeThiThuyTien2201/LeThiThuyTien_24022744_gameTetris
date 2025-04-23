#include "tetris.h"
#include<ctime>

using namespace std;

const int M = 23;
const int N = 10;

int main(int argc, char* argv[])
{
    game *Game = new game;
    Tetris *tetris = new Tetris;
    srand((double)time(0));
    if(tetris -> init()){
        while(tetris -> menu()){
            while(tetris -> isRunning()){
                tetris -> setCurrentTime(SDL_GetTicks());
                tetris -> Event();
                tetris -> game();
                tetris -> checkline();
                tetris -> gameOver();
                if (!tetris->isRunning()) break;
                tetris -> updateRenderer();
            }
            tetris -> reset();
        }
    }
    Game -> quitSDL(Game -> window, Game -> renderer);
    Mix_CloseAudio();
    return 0;
}
