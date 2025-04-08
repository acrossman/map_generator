/*	main.c
 *
 *	Program generates a map with pre-defined parameters and prints it to console.
 *	written by Crow
 *
 *	version 1.0
 */

#include <stdio.h>
#include "map_gen.h"

int main(void) {
	createWorld();
	printWorld();	
	return 0;
}
