/*
 * main.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "interface.h"

int main () {
	//required command that makes the scanf and printf work properly
	setvbuf(stdout,  NULL,  _IONBF,  0);

	menu();

	// return successful
	return 0;
}
