
// Program to convert an infix expression into postfix (with only single digit numbers)

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char** argv) {
	char* in;
	// [KADIR] Typically a good practice to display the
	// command line help. Here for example,
	if (argc > 1) {
		in = argv[1];
	} else {
		in = malloc(32);
		scanf("%s", in);
	}

	// [KADIR] It is always best practice to construct the output
	// into a string. What you do with the string is a flexibility.
	// Do not get into the habit of printing things in the middle
	// of code execution.
	char out[32];
	parse(in, out);
	printf("%s\n", out);
	if (argc <= 1)
		free(in);
}
