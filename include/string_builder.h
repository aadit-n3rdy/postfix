#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <string.h>

#ifndef STRING_BUILDER_BLOCK_SIZE
	#define STRING_BUILDER_BLOCK_SIZE 32
#endif

struct string_builder {
	char *raw;
	size_t len;
	size_t max;
};

typedef struct string_builder* string_builder_t;

string_builder_t string_builder_new();

int string_builder_append(string_builder_t sb, char c);

int string_builder_get(string_builder_t sb, char* out);

void string_builder_free(string_builder_t sb);

#endif
