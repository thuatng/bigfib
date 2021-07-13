/******************************************************************************/
/* BigFib.C:                                                     */
/* Copyright (C) 2020 Craig Scratchley    wcs (at) sfu (dot) ca  */
/******************************************************************************/

/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#include "InitHw.h"
#include "BigFib.h"
#define MAX_SIZE_TEST 1000

void halt()
{
	while(0);
}

int main() {

	unsigned *fibResP = NULL;
	int rv;
	unsigned size;
	unsigned lsw;
	
	InitHw(); // Initialize the HW, including the UART for printf()
	printf("BigFib Testing Program\n"); // must write to stdout/printf before below line with __heapstats
	__heapstats((__heapprt)fprintf, stdout);
//
//	////////////////****************1*****************///////////////////

//	////////////////****************2*****************///////////////////
	rv = bigFib(1, 0, &fibResP);
	size = *((fibResP));
	printf("F1 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x0 && size==0) )
			halt();
	free(fibResP);

//	////////////////*****************3****************///////////////////
	rv = bigFib(0, 0, &fibResP);
	
	size = *((fibResP));
	printf("F0 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x0 && size==0) )
		halt();
	free(fibResP);

//	 ////////////////*****************4****************///////////////////
	rv = bigFib(1, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x1 && lsw==1) )
		halt();
	free(fibResP);

//	////////////////****************5*****************///////////////////
	rv = bigFib(3, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F3 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x3 && lsw==2) )
		halt();
	free(fibResP);
	//////////////////////// 5b
	rv = bigFib(3, 6, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F3 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x3 && lsw==2) )
		halt();
	free(fibResP);

//	////////////////***************6******************///////////////////

	rv = bigFib(50, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F50 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x2f && lsw==0xB11924E1) ) // 0x2f is 47 
		halt();
	free(fibResP);
	
//	////////////////***************7******************///////////////////

	rv = bigFib(-2, 1, &fibResP);
	printf("F-2 requested. \n"); 
	if(!(rv==-1 && errno==EINVAL) )  
		halt();
	
//	////////////////***************8******************///////////////////

	rv = bigFib(1, 100000000, &fibResP);
	printf("Maxsize 100000000 requested. \n"); 
	if(!(rv==-1 && errno==ENOMEM) )  
		halt();
	
// please add more testcases	
	
// and now ...	
	rv = bigFib(1000000, MAX_SIZE_TEST, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1000000 requested. F%d was calculated with size %u.\n", rv, size); 
	halt();
	free(fibResP);
	
	while(1);
//	return i;
}

