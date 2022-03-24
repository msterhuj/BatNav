#ifndef GRID_H
#define GRID_H

int* create_grid( int nb_case );
void print_grid( int* grid, int nb_case, int nb_boat );
int fill_grid( int* grid, int nb_case );
void play( int* admin_grid, int* player_grid, int nb_case, int nb_boat );

#endif //GRID_H
