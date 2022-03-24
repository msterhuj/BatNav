#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

// ======= CREATE THE GAME BOARD =======
// game board = 1 dim array
int* create_grid( int nb_case ){
    int i;
    int cases = nb_case * nb_case;
    // create
    int* grid = malloc( cases * sizeof(int) );

    // initialise
    for ( i = 0 ; i < cases; ++i ) {
        *(grid + i) = 0;
    }

    return grid;
}
// =================================================


// ======= PRINT THE ACTUAL STATE OF THE BOARD =======
void print_grid( int* grid, int nb_case, int nb_boat ){
    int i, j;

    // HUD
    printf( "\n======================================\n" );
    printf( "=========== BATAILLE NAVALE ==========\n" );
    printf( "======================================\n" );
    printf( "--- Nombre de bateaux restant : %d ---\n", nb_boat );

    // first line
    printf( "     " );
    for( i = 0 ; i < nb_case ; ++i ){
        printf( "_%d_", i+1 );
        if( i < 8) printf("_");
    }
    printf("\n");

    // rest of the grid
    for( i = 0 ; i < nb_case ; ++i ){
        if( i < 9) printf(" ");
        printf( "%d- |", i+1 );

        for( j = 0 ; j < nb_case ; ++j ){
            switch( grid[i * nb_case +j] ){
                // case vide = _ ; case bateau = X ; case eau = O
                case 0:
                    printf( " _ " );
                    break;

                case 1:
                    printf( " X " );
                    break;

                case -1:
                    printf( " O " );
                    break;
            }
            printf( "|" );
        }
        printf( "\n" );
    }
}
// =================================================


// ======= LET THE ADMIN FILL THE BOARD =======
int fill_grid( int* grid, int nb_case ){
    int input, line, column, nb_boat = 0;
    int case_grid = 0;

    do{
        print_grid( grid, nb_case, nb_boat );

        printf( "\n======================================\n" );
        printf( "===== Placer ou retirer un bateau ====\n" );
        printf( "======= Entrer '0' pour sortir =======\n" );
        printf( "======================================\n" );

        printf("Entrer les coordonnees du bateau sous la forme XY. \nExemple : pour la ligne 1 et la column 3, entrer 13. \nCoordonnees :");
        scanf( "%d", &input );
        fflush( stdin );

        line = input / 10;
        column = input % 10;


        if( line > 0 && line <= nb_case && column > 0 && column <= nb_case ){
            case_grid = (line-1) * nb_case + column-1;

            if( *( grid + case_grid ) == 0 ) {
                *( grid + case_grid ) = 1;
                ++nb_boat;
            } else {
                *( grid + case_grid ) = 0;
                --nb_boat;
            }
        }
    } while ( input != 0 || nb_boat == 0 );

    return nb_boat;
}
// =================================================


// ======= PLAY =======
void play( int* admin_grid, int* player_grid, int nb_case, int nb_boat ){
    int input, line, column, case_grid;

    do {
        print_grid( player_grid, nb_case, nb_boat );

        do {
            printf("\nTirer une torpille sur quelle case ?\n");
            printf("Entrer les coordonnees du bateau sous la forme XY. \nExemple : pour la ligne 1 et la column 3, entrer 13. \nCoordonnees :");
            scanf( "%d", &input );
            fflush( stdin );

            line = input / 10;
            column = input % 10;


        } while (line <= 0 || line > nb_case || column <= 0 || column > nb_case);

        case_grid = (line - 1) * nb_case + column - 1;

        if (*(admin_grid + case_grid) == 1) {
            *(player_grid + case_grid) = 1;
            --nb_boat;
        } else {
            *(player_grid + case_grid) = -1;
        }
    } while( nb_boat > 0 );

    print_grid( player_grid, nb_case, nb_boat );
    printf( "Felicitation ! Vous avez detruit tous les bateaux !" );
}
// =================================================