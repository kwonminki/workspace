#include <stdio.h>
#include <stdlib.h>

void exit_handler(void){
    puts("\nProgram Terminated!!!");
}
/**
 * LAB0 - Hello World!
 * hello.c
 */
int main(void)
{
    int n;


    atexit(exit_handler);

    puts("\n====================================");
	puts("               LAB0");
	puts("====================================");
	printf("\nEnter a number : ");
	scanf("%d", &n);

	int sum = 0;
	for (int i=0; i<=n; i++){
	    sum += i;
	}

	printf("Sum = %d\n", sum);
	
	exit(0);
	return 0;
}
