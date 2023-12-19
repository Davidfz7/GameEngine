#ifndef TEST_H
#define TEST_H
    #define SCREEN_WIDTH 800
    #define X_MAX 768
    #define Y_MAX 544
    #define X_MIN 32
    #define Y_MIN 32

    #define SCREEN_HEIGHT 576
    #define TILE_WIDTH 32
    #define TILE_HEIGHT 32
    #define NUM_TILES_X (SCREEN_WIDTH / TILE_WIDTH) // 25
    #define NUM_TILES_Y (SCREEN_HEIGHT / TILE_HEIGHT) // 18
    #define BLOCK_JUMP 32

    int init_window();
    void *generate_snake();
    int init_assets();
    void update_snake(int x, int y);
    void move_snake();
    void update_graphics();
    void follow_head();


    typedef struct Coordinates{
        int x;
        int y;
    }Coordinates;

    typedef struct Snake{
        SDL_Rect *body; 
    }Snake;

    Coordinates **generate_map(int rows, int cols);

#endif
