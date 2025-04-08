#ifndef MAP_GEN_H_
#define MAPS_GEN_H_

#define COL 31
#define ROW 31

#define water    "\033[30;44m ~ \033[0m"
#define forest   "\033[30;42m T \033[0m"
#define mountain "\033[30;41m ^ \033[0m"
#define thicket  "\033[30;48;2;0;100;0m t \033[0m"
#define oats     "\033[30;48;5;230m o \033[0m"
#define grass    "\033[30;48;2;139;69;19m w \033[0m"
#define wall     "\033[5;37m{ }\033[0m"

// Structs
typedef struct tile {
    char contents[4];
    char description[200];
} tile_t;

typedef struct map {
    tile_t *grid[ROW][COL];
} map_t;

void createWorld();
void printWorld();
void set_fort();
void set_water();
void set_woods();
void set_mountains();
void set_grass();

int dice(int number, int sides);

#endif
