/*
 * Ethan Chen
 * UCLA Winter 2011
 * CS259 HW4
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_SIZE 256
#define MAX_FILENAME_SIZE 1024

struct Grid
{
    int x;
    int y;
    int z;
    int ***grid;
};


inline double
round(double d)
{
    return floor(d + 0.5);
}


void
help()
{
    printf("usage: meanfilter [-n <iterations> -g|-i <input file>\]n");
    printf("input file format: single number of array, each on newline\n");
}


struct Grid *
allocate_grid()
{
    int i, j;
    struct Grid *g;
    g = (struct Grid *) malloc(sizeof(struct Grid));
    if (!g) {
        return NULL;
    }
    g->x = DEFAULT_SIZE;
    g->y = DEFAULT_SIZE;
    g->z = DEFAULT_SIZE;
    g->grid = (int ***) malloc(sizeof(int) * DEFAULT_SIZE);
    if (!g->grid) {
        return NULL;
    }
    for (i = 0; i < DEFAULT_SIZE; i++) {
        g->grid[i] = (int **) malloc(sizeof(int) * DEFAULT_SIZE);
        if (!g->grid[i]) {
            return NULL;
        }
        for (j = 0; j < DEFAULT_SIZE; j++) {
            g->grid[i][j] = (int *) malloc(sizeof(int) * DEFAULT_SIZE);
            if (!g->grid[i][j]) {
                return NULL;
            }
        }
    }
    return g;
}


void
cleanup_grid(struct Grid *grid)
{
    int i, j;
    for (i = 0; i < DEFAULT_SIZE; i++) {
        for (j = 0; j < DEFAULT_SIZE; j++) {
            free(grid->grid[i][j]);
        }
        free(grid->grid[i]);
    }
    free(grid->grid);
    free(grid);
}


void
generate_grid(struct Grid *grid)
{
    int i, j, k;

    srand(time(NULL));
    for (i = 0; i < grid->x; i++) {
        for (j = 0; j < grid->y; j++) {
            for (k = 0; k < grid->z; k++) {
                int n = rand() % 256;
                grid->grid[i][j][k] = n;
            }
        }
    }
}


int
read_grid(char *input, struct Grid *grid)
{
    int i, j, k;
    FILE *in_file;

    in_file = fopen(input, "r");
    if (in_file == NULL) {
        return -1;
    }

    for (i = 0; i < grid->x; i++) {
        for (j = 0; j < grid->y; j++) {
            for (k = 0; k < grid->z; k++) {
                int n;
                fscanf(in_file, "%d", &n);
                grid->grid[i][j][k] = n;
            }
        }
    }

    fclose(in_file);
    return 0;
}


void
write_grid(struct Grid *grid)
{
    int i, j, k;

    for (i = 0; i < grid->x; i++) {
        for (j = 0; j < grid->y; j++) {
            for (k = 0; k < grid->z; k++) {
                printf("%d ", grid->grid[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


int
mean_filter(const struct Grid *in, struct Grid *out)
{
    int i, j, k, avg;

    for (i = 0; i < in->x; i++) {
        for (j = 0; j < in->y; j++) {
            for (k = 0; k < in->z; k++) {
                avg = 0;
                if (i > 0 && j > 0 && k > 0 && 
                        i < in->x - 1 && j < in->y - 1 && k < in->z - 1) {
                    // don't touch boundary cases
                    avg += in->grid[i-1][j-1][k-1];
                    avg += in->grid[i-1][j-1][k];
                    avg += in->grid[i-1][j-1][k+1];

                    avg += in->grid[i-1][j][k-1];
                    avg += in->grid[i-1][j][k];
                    avg += in->grid[i-1][j][k+1];

                    avg += in->grid[i-1][j+1][k-1];
                    avg += in->grid[i-1][j+1][k];
                    avg += in->grid[i-1][j+1][k+1];

                    avg += in->grid[i][j-1][k-1];
                    avg += in->grid[i][j-1][k];
                    avg += in->grid[i][j-1][k+1];

                    avg += in->grid[i][j][k-1];
                    avg += in->grid[i][j][k];
                    avg += in->grid[i][j][k+1];

                    avg += in->grid[i][j+1][k-1];
                    avg += in->grid[i][j+1][k];
                    avg += in->grid[i][j+1][k+1];

                    avg += in->grid[i+1][j-1][k-1];
                    avg += in->grid[i+1][j-1][k];
                    avg += in->grid[i+1][j-1][k+1];

                    avg += in->grid[i+1][j][k-1];
                    avg += in->grid[i+1][j][k];
                    avg += in->grid[i+1][j][k+1];

                    avg += in->grid[i+1][j+1][k-1];
                    avg += in->grid[i+1][j+1][k];
                    avg += in->grid[i+1][j+1][k+1];
                    
                    avg = (int) round((double) avg / 9.0);
                    in->grid[i][j][k] = avg;
                }
            }
        }
    }
}


int
main(int argc, char *argv[])
{
    char input[MAX_FILENAME_SIZE];
    int c;
    int iterations = 1;
    int generate = 0;
    struct Grid *grid;
    struct Grid *tmp_grid;

    if (argc < 2) {
        help();
        return 0;
    }

    while ((c = getopt(argc, argv, "?hv:n:i:g")) != -1) {
        switch (c) {
            case 'h':
            case 'v':
                help();
                return 0;
            case 'n':
                iterations = atoi((char *) getopt);
                break;
            case 'i':
                strncpy(input, optarg, MAX_FILENAME_SIZE);
                break;
            case 'g':
                generate = 1;
                break;
            default:
                help();
                return 0;
        }
    } 

    if (argc != optind) {
        help();
        return 0;
    }

    grid = allocate_grid();
    tmp_grid = allocate_grid();
    if (!grid || !tmp_grid) {
        printf("error: out of memory\n");
        return -1;
    }
    if (generate) {
        generate_grid(grid);
    } else {
        read_grid(input, grid); 
    }
    for (c = 0; c < iterations; c++) {
        mean_filter(grid, tmp_grid);
        struct Grid *tmp = grid;
        grid = tmp_grid;
        tmp_grid = tmp;
    }
    cleanup_grid(grid);
    cleanup_grid(tmp_grid);

    return 0;
}
