#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "enco.h"
#include "fsl_debug_console.h"
int c,ft;

int main (void) {
	encoinit();
	while (1) {
c=direction ();
	//	ft=steps(500);
		}

	}













