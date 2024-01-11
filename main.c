#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "linked_list/linkedlist.h"
#include <link.h>

typedef struct Snake{
    int eatenApples;
    Node *head;
    int counter;
}Snake;

Snake *gameSnake;

int main(int argc, char *argv[]){       
    gameSnake = NULL;
    if(init_window()){
        SDL_Log("Couldnt initialize Window");
    } 
    return 0;
}

int init_window(){
    SDL_Log("Initializing Window");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL; 
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
    bool quit = false; //quit = 0
    clock_t start_time = clock();
    double elapsed_time; 
    Direction direction = {false, false,
                           false, false,
                           true}; 
    //Engine loop?
    while(!quit){  
        elapsed_time = (double) (clock() - start_time) / CLOCKS_PER_SEC;
        quit = key_handler(&direction);
        if(quit){
            SDL_Log("Bye");
            SDL_DestroyWindow(window);
            free_list((*gameSnake).head);
            (*gameSnake).head = NULL;
            free(gameSnake);
            gameSnake = NULL;
            SDL_Quit();  
            break;
        }
        if(elapsed_time >= 0.03){
            start_time = clock();
            update_graphics(renderer, true, &direction);  
        }
    }
    return 0;
}



void update_graphics(SDL_Renderer *renderer, bool action, Direction *direction){  
    SDL_SetRenderDrawColor(renderer, 71, 71, 70, 0); //Red 
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 36, 214, 36, 0);  
    draw_snake(renderer);
    // if((*direction).noDirection){
    //     rect.y -= 4;
    //     rect2.y -= 4;
    // }else if((*direction).up){
    //     rect.y -= 4;
    //     rect2.y = rect.y + 22;
    //     rect2.x = rect.x;
    // }else if((*direction).left){
    //     rect.x -= 4;
    //     rect2.x = rect.x+22;
    //     rect2.y = rect.y;
    // }else if((*direction).down){
    //     rect.y += 4;
    // }else if((*direction).right){
    //     rect.x += 4;
    //     rect2.x = rect.x -22;
    //     rect2.y = rect.y;
    // }
 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

bool key_handler(Direction *direction){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                return true;  
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym){
                    case SDLK_w:
                        reset_all_directions(&(*direction),
                                             &(*direction).up);  
                        break;
                    case SDLK_a:
                        reset_all_directions(&(*direction),
                                             &(*direction).left); 
                        break;
                    case SDLK_s:
                        reset_all_directions(&(*direction),
                                             &(*direction).down); 
                        break;
                    case SDLK_d:
                        reset_all_directions(&(*direction),
                                             &(*direction).right);  
                        break;
                    default:
                        break;
                } 
                break;  
        } 
    }
    return false; 
}

void reset_all_directions(Direction *direction, bool *exc){
    (*direction).noDirection = false;

    if(&(*direction).up == &(*exc)){
        (*direction).up = true;
        (*direction).left = false;
        (*direction).down = false;
        (*direction).right = false;
    }else if(&(*direction).left == &(*exc)){
        (*direction).up = false;
        (*direction).left = true;
        (*direction).down = false;
        (*direction).right = false;
    }else if(&(*direction).down == &(*exc)){
        (*direction).up = false;
        (*direction).left = false;
        (*direction).down = true;
        (*direction).right = false;
    }else if(&(*direction).right == &(*exc)){
        (*direction).up = false;
        (*direction).left = false;
        (*direction).down = false;
        (*direction).right = true;
    } 
}

// void generate_snake(){
//     SDL_Rect rect = {76, 20, 20, 20};
//     head = create_head(&rect);
//     SDL_Log("Rect x value: %d\n", (*(SDL_Rect *)(*head).data).x);
//     free_list(head);
//     head = NULL;
// }

void draw_snake(SDL_Renderer *renderer){
    SDL_Rect momRect = {20, 20, 20, 20};

    if(gameSnake == NULL){
        gameSnake = (Snake *) malloc(sizeof(Snake));  
        (*gameSnake).eatenApples = 2;
        (*gameSnake).head = create_head(&momRect);
        (*gameSnake).counter = 1;
    }

    
    if(gameSnake != NULL && (*gameSnake).eatenApples > 1){
        int i;
        int momX = momRect.x;
        int momY = momRect.y; 
        for(i = 1; i <= (*gameSnake).eatenApples; i++){   
            SDL_Rect newRect = {momX, momY+25, momRect.w, momRect.h};
            append((*gameSnake).head, &newRect);
            momY = newRect.y;
        }    
    }

    Node *justTheBody = (*gameSnake).head;

    while(justTheBody != NULL){
        SDL_RenderDrawRect(renderer, (SDL_Rect *)(*justTheBody).data);
        justTheBody = (*justTheBody).next; 
    }
}