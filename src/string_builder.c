#include "string_builder.h"

#include <stdlib.h>

string_builder_t string_builder_new() {
	string_builder_t ret;
	ret =  malloc(sizeof(struct string_builder));
	if (ret) {
		ret->raw = malloc(STRING_BUILDER_BLOCK_SIZE);
		if (!ret->raw) {
			free(ret);
			return (void*)NULL;
		}
		ret->len = 0;
		ret->max = STRING_BUILDER_BLOCK_SIZE;
	}
	return ret;
}

int string_builder_append(string_builder_t sb, char c) {
	if (sb->len >= sb->max-2) {
		sb->raw = realloc(sb->raw, sb->len+STRING_BUILDER_BLOCK_SIZE);
		if (sb->raw) {
			sb->max += STRING_BUILDER_BLOCK_SIZE;
		} else {
			return -1;
		}
	}
	sb->raw[sb->len] = c;
	sb->raw[sb->len+1] = '\0';
	sb->len++;
}

int string_builder_get(string_builder_t sb, char *out) {
	if (sb && sb->raw) {
		strcpy(out, sb->raw);
		return 0;
	} else {
		return -1;
	}
}

void string_builder_free(string_builder_t sb) {
	free(sb);
}	
