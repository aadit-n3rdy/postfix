#include "string_stream.h"

#include <stdlib.h>

string_stream_t string_stream_new(char *str) {
	string_stream_t ss = malloc(sizeof(struct string_stream));
	if (ss) {
		ss->raw = str;
		ss->index = 0;
	}
	return ss;
}

char string_stream_get(string_stream_t ss) {
	char ret = ss->raw[ss->index];
	if (ret != '\0')
		ss->index++;
	return ret;
}

char string_stream_peek(string_stream_t ss) {
	return ss->raw[ss->index];
}

void string_stream_free(string_stream_t ss) {
	if (ss) 
		free(ss);
}

