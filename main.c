#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"

void **ptrsArray;
int elementCounter;
int appleCounter = 3;
bool status;


Snake *snake = NULL;
Coordinates **generateMap(int rows, int cols);
Coordinates **map = NULL;
SDL_Event e;
SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
int snakePositionX;
int snakePositionY;
bool quit;
int start = 0;

//Limites (x = 768, x = 568)
//Limites (x = 32, y = 32)

int main(int argc, char *argv[]){       
    init_assets(); 
    if(init_window()){
        SDL_Log("Couldnt initialize Window");
    }
    
    free((*snake).body);
    free(snake);    
    free(map);
    return 0;
}

int init_assets(){ 
    map = generate_map(NUM_TILES_Y, NUM_TILES_X);  
    snakePositionX = map[12][8].x;
    snakePositionY = map[12][8].y;   
    
    generate_snake();  
    return 0; 
}

int init_window(){
    SDL_Log("Initializing Window");
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("inside", SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if(window == NULL){
        return 1;
    }
    if(renderer == NULL){
        SDL_Log("Something went wrong initialinz the render");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Game loop 
    quit = false; //quit = 0
    //Engine loop?
    while(!quit){ //quit not > 0
        SDL_Delay(16);
        move_snake();      
        update_graphics(renderer); 
    } 
    return 0;
}

void update_graphics(){
    SDL_SetRenderDrawColor(renderer, 71, 71, 70, 0); //Red 
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  //   SDL_RenderDrawRects(renderer, (*snake).body, 2); 
    SDL_SetRenderDrawColor(renderer, 36, 214, 36, 0);
    SDL_RenderDrawRect(renderer, &(*snake).body[0]);
   
  //   SDL_RenderFillRects(renderer, (*snake).body, 3);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  //  SDL_RenderFillRect(renderer, &(*snake).body[0]);
    SDL_RenderPresent(renderer);
}

Coordinates **generate_map(int rows, int cols){

    Coordinates **cordsMap = malloc(rows * sizeof(Coordinates *));  
    int i;
    int j;
    int counterX = 0;
    int counterY = 0;
    if(cordsMap == NULL){
        printf("Something went wrong");
        return NULL;
    } 

    for(i = 0; i < rows; i++){
        cordsMap[i] = malloc(cols * sizeof(Coordinates));
        if(cordsMap[i] == NULL){
            printf("Something went wrong");
            for(j = 0; j < i; j++){
                free(cordsMap[j]);
            }
            free(cordsMap);
            return NULL;
     
        }               
    }

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            cordsMap[i][j].x = counterX;
            cordsMap[i][j].y = counterY;
            SDL_Log("cordsMap[%d][%d] = (%d, %d)", i, j, cordsMap[i][j].x, cordsMap[i][j].y);            
            counterY += 32;
        }
       
        counterY = 0;
        counterX += 32; 
    }

    return cordsMap;
}

void *generate_snake(){
    int i;
    int multiplier = 0;

    snake = malloc(sizeof(Snake)); 
    (*snake).body = malloc(appleCounter * sizeof(SDL_Rect));
    for(i = 0; i <= 2; i++){
        (*snake).body[i] = (SDL_Rect){snakePositionX, (snakePositionY+multiplier),
                                      TILE_WIDTH, TILE_HEIGHT}; // 16 bytes here
        SDL_Log("(%d, %d)", snakePositionX, snakePositionY+multiplier); 
        multiplier += 34;
    }      
}

void update_snake(int x, int y){
    SDL_Log("Here we are going to update the snake:)");
    if(snake != NULL){
        free((*snake).body);
        free(snake);
        snake = NULL;
        if(snake == NULL){
            generate_snake();
        }
    }    
}

void move_snake(){
    while (SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                SDL_Log("Bye");
                SDL_DestroyWindow(window);
                SDL_Quit();
                quit = true; // quit = 1
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_w:
                        SDL_Delay(66);
                        (*snake).body[0].y -= 32;
                        break;
                    case SDLK_a: 
                        (*snake).body[0].x -= 32;
                        break;
                    case SDLK_s:
                        (*snake).body[0].y += 32;
                        break;
                    case SDLK_d:
                        (*snake).body[0].x += 32;
                        break;
                    case SDLK_SPACE:
                        start = (!start) ? 1 : 0;
                        SDL_Log("Starting the game");
                    default:
                        break;
                } 
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym){
                case SDLK_a:
                    SDL_Log("Hello WOrld");
                    break;
                
                default:
                    break;
                }

                    
        }
         
    }
    // if(start){
    //     SDL_Delay(900);
    //     (*snake).body[0].y -= 32;
    //     for(i = 1; i <= snakeLength-1; i++){ // 1 - 2; i++
    //         currentPositionX = (*snake).body[i].x;
    //         currentPositionY = (*snake).body[i].y;
    //         (*snake).body[i].x = prevPositionX;
    //         (*snake).body[i].y = prevPositionY;
    //         prevPositionX = currentPositionX;
    //         prevPositionY = currentPositionY;
     
    //     }
    // SDL_Log("Starting the game\n");
    // }
 
}

void follow_head(){
    if(!status){
        SDL_Log("Hello World");

    }
    
    // int snakeLength = appleCounter; // 3
    // int i;
    // int prevPositionX = (*snake).body[0].x;
    // int prevPositionY = (*snake).body[0].y;
    // int currentPositionX;
    // int currentPositionY; 
    // for(i = 0; i <= snakeLength-1; i++){ //2
    //     currentPositionX = (*snake).body[i].x;
    //     currentPositionY = (*snake).body[i].y;
    //     (*snake).body[i].x = prevPositionX;
    //     (*snake).body[i].y = prevPositionY;
    //     prevPositionX = currentPositionX;
    //     prevPositionY = currentPositionY;
    // } 

}
