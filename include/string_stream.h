#ifndef STRING_STREAM_H
#define STRING_STREAM_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string_stream {
	char* raw;
	size_t index;
};

typedef struct string_stream* string_stream_t;

string_stream_t string_stream_new(char *str);

char string_stream_get(string_stream_t ss);

char string_stream_peek(string_stream_t ss);

void string_stream_free(string_stream_t ss);

#ifdef __cplusplus
}
#endif

#endif
