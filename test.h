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
    typedef struct Direction{
        bool up;
        bool left;
        bool down;
        bool right;
        bool noDirection;
    } Direction;

    int init_window();
    void generate_snake();
    void update_graphics(SDL_Renderer *renderer, 
                         bool action, Direction *direction);
    void follow_head();
    bool interval_action(double interval); 
    bool key_handler(Direction *direction); 
    void reset_all_directions(Direction *direction, bool *exc);
    void draw_snake(SDL_Renderer *renderer);
#endif
