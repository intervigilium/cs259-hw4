/*
 * Ethan Chen
 * UCLA Winter 2011
 * CS259 HW4
 */

#include <stdlib.h>
#include "autopilot_tech.h"

#define DEFAULT_SIZE 256

typedef uint9 dim3;
typedef uint32 uint32_t;


void
mean_filter(
		uint32_t input_array[DEFAULT_SIZE][DEFAULT_SIZE][DEFAULT_SIZE],
		uint32_t output_array[DEFAULT_SIZE][DEFAULT_SIZE][DEFAULT_SIZE])
{
#pragma AP interface ap_memory port=input_array pipeline
#pragma AP interface ap_memory port=output_array pipeline

	dim3 x, y, z;
	x = DEFAULT_SIZE;
	y = DEFAULT_SIZE;
	z = DEFAULT_SIZE;
	uint32_t block_cache[3][3][3];
#pragma AP array_partition variable=block_cache complete dim=0

	uint32_t avg;
	dim3 i, j, k;
    
    for (i = 1; i < x-1; i++) {
    	for (j = 1; j < y-1; j++) {
    		for (k = 1; k < z-1; k++) {
#pragma AP pipeline enable_flush

                avg = 0;
                if (i == 1 && j == 1 && k == 1) {
                	block_cache[0][0][0] = input_array[0][0][0];
	            	block_cache[0][1][0] = input_array[0][1][0];
	            	block_cache[0][2][0] = input_array[0][2][0];
	            	
	            	block_cache[0][0][1] = input_array[0][0][1];
	            	block_cache[0][1][1] = input_array[0][1][1];
	            	block_cache[0][2][1] = input_array[0][2][1];
		                	
	            	block_cache[0][0][2] = input_array[0][0][2];
	            	block_cache[0][1][2] = input_array[0][1][2];
	        		block_cache[0][2][2] = input_array[0][2][2];
		                	                	
	            	block_cache[1][0][0] = input_array[1][0][0];
	            	block_cache[1][1][0] = input_array[1][1][0];
	            	block_cache[1][2][0] = input_array[1][2][0];
	            	
	            	block_cache[1][0][1] = input_array[1][0][1];
	            	block_cache[1][1][1] = input_array[1][1][1];
	            	block_cache[1][2][1] = input_array[1][2][1];
	            	
	            	block_cache[1][0][2] = input_array[1][0][2];
	            	block_cache[1][1][2] = input_array[1][1][2];
	            	block_cache[1][2][2] = input_array[1][2][2];
	            	                	
	            	block_cache[2][0][0] = input_array[2][0][0];
	            	block_cache[2][1][0] = input_array[2][1][0];
	            	block_cache[2][2][0] = input_array[2][2][0];
	            	
	            	block_cache[2][0][1] = input_array[2][0][1];
	            	block_cache[2][1][1] = input_array[2][1][1];
	            	block_cache[2][2][1] = input_array[2][2][1];
	            	
	            	block_cache[2][0][2] = input_array[2][0][2];
	            	block_cache[2][1][2] = input_array[2][1][2];
	            	block_cache[2][2][2] = input_array[2][2][2];
                } else {
	            	block_cache[0][0][0] = block_cache[0][0][1];
	            	block_cache[0][1][0] = block_cache[0][1][1];
	            	block_cache[0][2][0] = block_cache[0][2][1];
	            	
	            	block_cache[0][0][1] = block_cache[0][0][2];
	            	block_cache[0][1][1] = block_cache[0][1][2];
	            	block_cache[0][2][1] = block_cache[0][2][2];
		                	
	            	block_cache[0][0][2] = input_array[i-1][j-1][k+1];
	            	block_cache[0][1][2] = input_array[i-1][j][k+1];
	        		block_cache[0][2][2] = input_array[i-1][j+1][k+1];
		                	                	
	            	block_cache[1][0][0] = block_cache[1][0][1];
	            	block_cache[1][1][0] = block_cache[1][1][1];
	            	block_cache[1][2][0] = block_cache[1][2][1];
	            	
	            	block_cache[1][0][1] = block_cache[1][0][2];
	            	block_cache[1][1][1] = block_cache[1][1][2];
	            	block_cache[1][2][1] = block_cache[1][2][2];
	            	
	            	block_cache[1][0][2] = input_array[i][j-1][k+1];
	            	block_cache[1][1][2] = input_array[i][j][k+1];
	            	block_cache[1][2][2] = input_array[i][j+1][k+1];
	            	                	
	            	block_cache[2][0][0] = block_cache[2][0][1];
	            	block_cache[2][1][0] = block_cache[2][1][1];
	            	block_cache[2][2][0] = block_cache[2][2][1];
	            	
	            	block_cache[2][0][1] = block_cache[2][0][2];
	            	block_cache[2][1][1] = block_cache[2][1][2];
	            	block_cache[2][2][1] = block_cache[2][2][2];
	            	
	            	block_cache[2][0][2] = input_array[i+1][j-1][k+1];
	            	block_cache[2][1][2] = input_array[i+1][j][k+1];
	            	block_cache[2][2][2] = input_array[i+1][j+1][k+1];
                }

                avg += block_cache[0][0][0];
                avg += block_cache[0][0][1];
                avg += block_cache[0][0][2];

                avg += block_cache[0][1][0];
                avg += block_cache[0][1][1];
                avg += block_cache[0][1][2];

                avg += block_cache[0][2][0];
                avg += block_cache[0][2][1];
                avg += block_cache[0][2][2];

                avg += block_cache[1][0][0];
                avg += block_cache[1][0][1];
                avg += block_cache[1][0][2];

                avg += block_cache[1][1][0];
                avg += block_cache[1][1][1];
                avg += block_cache[1][1][2];

                avg += block_cache[1][2][0];
                avg += block_cache[1][2][1];
                avg += block_cache[1][2][2];

                avg += block_cache[2][0][0];
                avg += block_cache[2][0][1];
                avg += block_cache[2][0][2];

                avg += block_cache[2][1][0];
                avg += block_cache[2][1][1];
                avg += block_cache[2][1][2];

                avg += block_cache[2][2][0];
                avg += block_cache[2][2][1];
                avg += block_cache[2][2][2];
                
                avg = (int) (((double) avg / 9.0) + 0.5);
                output_array[i][j][k] = avg;
            }
        }
    }
}