#ifndef TETRIS_H
#define TETRIS_H
#include "Game.h"

class Tetris
{
    private:
    enum{blockW = 30, blockH = 30};
    enum{line = 20, col = 10};
    SDL_Texture *background = NULL, *block = NULL, *score_frame = NULL;
    SDL_Texture* backgroundMenu = NULL;
    SDL_Texture* play = NULL;
    SDL_Texture* play_light = NULL;
    SDL_Texture* lv1 = NULL;
    SDL_Texture* lv2 = NULL;
    SDL_Texture* lv3 = NULL;
    SDL_Texture* lv1_light = NULL;
    SDL_Texture* lv2_light = NULL;
    SDL_Texture* lv3_light = NULL;
    SDL_Texture* gameover_background= NULL;
    SDL_Rect sRect = {0, 0, 36, 36}, dRect = {0, 0, blockW, blockH};
    SDL_Rect dRect_score_frame = {5, 5, blockW*4, blockH*4};
    bool running = false;
    int level = 1;
    int score = 0;
    int field[line][col] = {{0}};
    static const int figure[7][4];
    struct point
    {
        int x, y;
    }
    temp[4], backup[4];
    unsigned int delay = 0;
    bool rotate = false;
    int move = 0;
    Uint32 currentTime = 0, lastTime = 0;
    int color = 1;
public:
    game Game;
    bool init();
    bool menu();
    bool isRunning()
    {
        return running;
    }
    void Event();
    void tetromino(SDL_Rect &rect, int x = 0, int y = 0, int w = blockW, int h = blockH);
    bool selectRect(SDL_Rect &rect, const int x, const int y);
    void game();
    void clean();
    void setCurrentTime(Uint32 t);
    bool collision();
    void nextTetromino();
    void updateRenderer();
    void updateField(SDL_Rect &rect, const int x, const int y);
    void checkline();
    void gameOver();
    void reset();

};

#endif // TETRIS_H
