#include "Tetris.h"

/*
 0 1 2 3
 4 5 6 7 */

const int Tetris::figure[7][4] =
{
    0, 1, 2, 3, // I
    0, 1, 5, 6, // Z
    0, 4, 5, 6, // J
    2, 6, 5, 4, // L
    1, 2, 5, 6, // O
    2, 1, 5, 4, // S
    1, 4, 5, 6  // T
};

//khoi tao SDL
bool Tetris::init(){
    Game.initSDL(Game.window, Game.renderer);
    SDL_SetRenderDrawColor(Game.renderer, 255, 255, 255, 255);

    nextTetromino(); // sinh ra khoi dau tien
    return true;
}

// kiem tra chuot co nam trong rect khong
bool Tetris::selectRect(SDL_Rect &rect, const int x, const int y){
    if(x >= rect.x && x <= rect.x + rect.w
       && y >= rect.y && y <= rect.y + rect.h){
        return true;
    }
    return false;
}

bool Tetris::menu(){
    SDL_Event e;
    backgroundMenu = Game.loadTexture("background_while.png", Game.renderer);
    play = Game.loadTexture("play.png", Game.renderer);
    play_light = Game.loadTexture("play_light.png", Game.renderer);
    lv1 = Game.loadTexture("level_1.png", Game.renderer);
    lv2 = Game.loadTexture("level_2.png", Game.renderer);
    lv3 = Game.loadTexture("level_3.png", Game.renderer);
    lv1_light = Game.loadTexture("level_1_light.png", Game.renderer);
    lv2_light = Game.loadTexture("level_2_light.png", Game.renderer);
    lv3_light = Game.loadTexture("level_3_light.png", Game.renderer);
    const int playRect_x = 30;
    const int playRect_y = 250;
    const int levelRect_x = 30;
    const int levelRect_y = 350;
    SDL_Rect playRect = {playRect_x, playRect_y, 94, 53};
    SDL_Rect levelRect = {levelRect_x, levelRect_y, 174, 53};
    SDL_RenderCopy(Game.renderer, backgroundMenu, NULL, NULL);
    SDL_RenderCopy(Game.renderer, play, NULL, &playRect);
    if(level == 1)
    {
        SDL_RenderCopy(Game.renderer, lv1, NULL, &levelRect);
    }
    else if(level == 2)
    {
        SDL_RenderCopy(Game.renderer, lv2, NULL, &levelRect);
    }
    else if(level == 3)
    {
        SDL_RenderCopy(Game.renderer, lv3, NULL, &levelRect);
    }
    int x = 0;
    int y = 0;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            x = e.motion.x;
            y = e.motion.y;
            if(selectRect(playRect, x, y))
            {
                SDL_RenderCopy(Game.renderer, play_light, NULL, &playRect);
                Game.effectAudio("hardDrop.wav");
            }
            else if(selectRect(levelRect, x, y))
            {
                if(level == 1)
                {
                    SDL_RenderCopy(Game.renderer, lv1_light, NULL, &levelRect);
                    Game.effectAudio("hardDrop.wav");
                }
                else if(level == 2)
                {
                    SDL_RenderCopy(Game.renderer, lv2_light, NULL, &levelRect);
                    Game.effectAudio("hardDrop.wav");
                }
                else if(level == 3)
                {
                    SDL_RenderCopy(Game.renderer, lv3_light, NULL, &levelRect);
                    Game.effectAudio("hardDrop.wav");
                }

            }
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN){
            if(e.button.button == SDL_BUTTON_LEFT){
                x = e.button.x;
                y = e.button.y;
                if(selectRect(playRect, x, y)){
                    running = true;
                }
                else if(selectRect(levelRect, x, y)){
                    if(level == 1)
                        level++;
                    else if(level == 2)
                        level++;
                    else if(level == 3)
                        level -= 2;
                }
            }
        }

    }
    SDL_RenderPresent(Game.renderer);
    SDL_DestroyTexture(backgroundMenu);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(play_light);

    return true;
}

//cap nhat vi tri
void Tetris::updateField(SDL_Rect &rect, const int x, const int y){
    rect.x += x;
    rect.y += y;
}

//xu ly phim bam
void Tetris::Event(){
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            running = false;
            break;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
            case SDLK_RIGHT : // sang phai
                {
                     move = 1;
                     Game.effectAudio("Move.wav");
                     break;
                }
            case SDLK_LEFT : // sang trai
                {
                     move = -1;
                     Game.effectAudio("Move.wav");
                     break;
                }
            case SDLK_UP : // xoay khoi
                {
                    rotate = true;
                    Game.effectAudio("rotate.wav");
                    break;
                }
            case SDLK_DOWN : // roi nhanh
                {
                    delay = 0;
                }
            }
        }
    }
}

void Tetris::setCurrentTime(Uint32 t){
    currentTime = t;
}

//kiem tra va cham
bool Tetris::collision(){
    for(int i = 0; i < 4; i++){
        if(temp[i].x < 0 || temp[i].x >= col || temp[i].y >= line)   //va cham vs field
            return false;
        else if(field[temp[i].y][temp[i].x])  //va cham vs block
            return false;
    }
    return true;
}

void Tetris::tetromino(SDL_Rect &rect, int x, int y, int w, int h){
    rect = {x, y, w, h};
}

void Tetris::nextTetromino(){
    color = 1 + rand()%7;
    int a = rand()%7;
    for(int i = 0; i < 4; i++){
        temp[i].x = figure[a][i] % 4;
        temp[i].y = figure[a][i] / 4;
    }
}

void Tetris::game(){
    for(int i = 0; i < 4; i++){
        backup[i] = temp[i];
    }
    for(int i = 0; i < 4; i++){
        temp[i].x += move;
    }
    if(!collision())   // xu li va cham khi move
        {
            for(int i = 0; i < 4; i++)
                temp[i] = backup[i];
        }
    //rotate
    if(rotate)
    {
        point p = temp[2];
        for(int i = 0; i < 4; i++)
        {
            int x = temp[i].y - p.y;
            int y = temp[i].x - p.x;
            temp[i].x = p.x - x;
            temp[i].y = p.y + y;
        }
        if(!collision())  // xu ly va cham khi rotate
        {
            for(int i = 0; i < 4; i++)
                temp[i] = backup[i];
        }
    }

    if(currentTime - lastTime > delay){
        for(int i = 0; i < 4; i++){
            temp[i].y += 1;
        }
        lastTime = currentTime;
        if(!collision()){
            for(int i = 0; i < 4; i++){
                field[backup[i].y][backup[i].x] = color;// save mau o cuoi line
            }
            nextTetromino();
        }
    }

    move = 0;
    rotate = false;
    if(level == 1)
        delay = 900;
    else if(level == 2)
        delay = 500;
    else if(level == 3)
        delay = 250;
}

void Tetris::checkline(){
    int n = line - 1;
    for(int i = n; i > 0; i--){
        int count = 0;
        for(int j = 0; j < col; j++){
            if(field[i][j])
                count++;
            field[n][j] = field[i][j];
        }
        if(count < col)
            n--;
        if(count == col){
            Game.effectAudio("Lineclear.wav");
            score += 100;
            string text = to_string(score);
            if(score < 1000)
                Game.Text(text, 42, 70, Game.renderer, { 240, 66, 225 });
            else if(score < 10000)
                Game.Text(text, 37, 70, Game.renderer, { 240, 66, 225 });
        }
    }
}

void Tetris::gameOver(){
    int game_over_count = 0;
    for(int i = 0; i < line; i++){
        for(int j = 0; j < col; j++){
            if(field[i][j] != 0){
                game_over_count ++;
                break;
            }
        }
    }
    if(game_over_count == line){
        Mix_HaltMusic(); // dung nhac nen neu dang chay
        Game.effectAudio("gameover1.wav");
        SDL_Texture* GAME_OVER = Game.loadTexture("gameover.png", Game.renderer);
        SDL_RenderCopy(Game.renderer, GAME_OVER, NULL, nullptr);
        SDL_RenderPresent(Game.renderer);
        SDL_Delay(3000);
        SDL_DestroyTexture(GAME_OVER);

        clean();
        running = false;
    }
}

void Tetris::updateRenderer(){
    SDL_RenderClear(Game.renderer);
    Game.backgroundAudio("Background.wav");
    background = Game.loadTexture("background.png", Game.renderer);
    block = Game.loadTexture("blocks.png", Game.renderer);
    score_frame = Game.loadTexture("score_frame.png", Game.renderer);
    SDL_RenderCopy(Game.renderer, background, NULL, NULL);
    SDL_RenderCopy(Game.renderer, score_frame, NULL, &dRect_score_frame);
    if(score == 0){
        Game.Text("0", 58, 70, Game.renderer, { 240, 66, 225 });
        SDL_RenderCopy(Game.renderer, Game.Tex, &Game.srcRest, &Game.desRect);
    }
    SDL_RenderCopy(Game.renderer, Game.Tex, &Game.srcRest, &Game.desRect);
    //va cham vs day
    for(int i = 0; i < line; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(field[i][j])
            {
                tetromino(sRect, field[i][j]*36);
                tetromino(dRect, j*blockW, i*blockH);
                updateField(dRect, blockW, SCREEN_HEIGHT - (line + 1)*blockH);
                SDL_RenderCopy(Game.renderer, block, &sRect, &dRect);
            }
        }
    }
    //Tao block
    for(int i = 0; i < 4; i++){
        tetromino(sRect, color * 36);
        tetromino(dRect, temp[i].x *blockW, temp[i].y*blockH);
        updateField(dRect, blockW, SCREEN_HEIGHT - (line + 1)*blockH);
        SDL_RenderCopy(Game.renderer, block, &sRect, &dRect);
    };
    SDL_RenderPresent(Game.renderer);
    clean();
}

void Tetris::reset(){
    for(int i = 0; i < line; i++){
        for(int j = 0; j < col; j++){
            field[i][j] = 0;
        }
    }
    score = 0;
}

void Tetris::clean() // chong tran bo nho
{

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(block);
    SDL_DestroyTexture(backgroundMenu);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(play_light);
    SDL_DestroyTexture(lv1);
    SDL_DestroyTexture(lv2);
    SDL_DestroyTexture(lv3);
    SDL_DestroyTexture(lv1_light);
    SDL_DestroyTexture(lv2_light);
    SDL_DestroyTexture(lv3_light);
}
