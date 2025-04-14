#ifndef GAME_H
#define GAME_H


#include<iostream>
#include<string>
#include<algorithm>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

using namespace std;
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 800;

const string WINDOW_TITLE = "TETRIS CUA TIEN XINH DEP 🩶";

struct game
{

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect srcRest;
    SDL_Rect desRect;
    SDL_Texture* Tex;
public:
    void logSDLError(std::ostream& os, const string &msg, bool fatal = false);
    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
    void waitGameKeyPressed();
    SDL_Texture *loadTexture(string path, SDL_Renderer *renderer);
    void backgroundAudio(const char* nameSong);
    void effectAudio(const char* nameSong);
    void Text(string text, int x, int y, SDL_Renderer* renderer, SDL_Color color);
};

#endif // GAME_H
