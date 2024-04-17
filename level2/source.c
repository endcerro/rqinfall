#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void p(void)
{
	unsigned int unaff_retaddr;
	char read_buffer [76];

	fflush(stdout);
	gets(read_buffer);
	if ((unaff_retaddr & 0xb0000000) == 0xb0000000) 
	{
		printf("(%p)\n",(void*) unaff_retaddr);
		exit(1);
	}
	puts(read_buffer);
	strdup(read_buffer);
	return;
}


void main(void)
{
	p();
	return;
}