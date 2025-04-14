#include "Game.h"

void game::logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
    SDL_Quit();
    exit(1);
    }
}

void game::initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void game::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void game::waitGameKeyPressed()
{
    SDL_Event e;
    while (true) {
    if ( SDL_WaitEvent(&e) != 0 &&
    (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
    return;
    SDL_Delay(100);
    }
}


SDL_Texture* game::loadTexture(string path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
        cout<<"Unable to load image "<<path<<" SDL image error : "<<IMG_GetError()<<endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == nullptr)
            cout<<"Unable to create texture from "<<path<<" SDL error : "<<SDL_GetError()<<endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void game::backgroundAudio(const char* nameSong)
{
    Mix_Music* music = NULL;
 	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout<< Mix_GetError();
	}
	music = Mix_LoadMUS(nameSong);
	if (music == NULL)
	{
		cout<< Mix_GetError();
	}
	if (!Mix_PlayingMusic())
        Mix_PlayMusic(music, -1);
}

void game::effectAudio(const char* nameSong)
{
    Mix_Chunk* chunk = NULL;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout<< Mix_GetError();
	}
	chunk = Mix_LoadWAV(nameSong);
	if (chunk == NULL)
	{
		cout<< Mix_GetError();
	}
	if (!Mix_Playing(-1))
        Mix_PlayChannel(-1, chunk, 0);
}

void game::Text(string text, int x, int y, SDL_Renderer* renderer, SDL_Color color)
{
    if (TTF_Init() < 0)
    {
	SDL_Log("%s", TTF_GetError());
    }
    TTF_Font* font = NULL;
    font = TTF_OpenFont("eurof55.ttf", 30);
    //SDL_Color fg = { 240, 66, 225 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Tex = texture;
    SDL_FreeSurface(surface);
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
}

