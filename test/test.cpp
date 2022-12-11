#include "parser.h"
#include "string_builder.h"
#include "string_stream.h"

#include <stdio.h>
#include <assert.h>

int main() {

	// String builder test

	char out[32];	
	string_builder_t sb = string_builder_new();
	string_builder_append(sb, 'a');
	string_builder_append(sb, 'b');
	string_builder_get(sb, out);
	assert(strcmp(out, "ab") == 0);
	printf("String builder test passed\n");
	string_builder_free(sb);

	// String stream test
	
	char c;
	char str[32] = "2+3";
	string_stream_t ss = string_stream_new(str);
	assert(string_stream_get(ss) == '2');
	assert(string_stream_get(ss) == '+');
	assert(string_stream_get(ss) == '3');
	printf("String stream test passed\n");
	string_stream_free(ss);

	// Parse factor
	sb = string_builder_new();
	ss = string_stream_new("2+3");
	parse_fac(ss, sb);
	assert(strcmp("2", sb->raw) == 0);
	printf("Parsed 2\n");
	string_stream_free(ss);
	string_builder_free(sb);

	// Parse term
	sb = string_builder_new();
	ss = string_stream_new("2+3");
	parse_term(ss, sb);
	assert(strcmp("2", sb->raw) == 0);
	printf("Parsed term 1\n");
	string_stream_free(ss);
	string_builder_free(sb);

	sb = string_builder_new();
	ss = string_stream_new("2*3");
	parse_term(ss, sb);
	assert(strcmp("23*", sb->raw) == 0);
	printf("Parsed term 2\n");
	string_stream_free(ss);
	string_builder_free(sb);


	// Parse expr
	
	sb = string_builder_new();
	ss = string_stream_new("2*3");
	parse_expr(ss, sb);
	assert(strcmp("23*", sb->raw) == 0);
	printf("Parsed expr 1\n");
	string_stream_free(ss);
	string_builder_free(sb);

	sb = string_builder_new();
	ss = string_stream_new("2+3");
	parse_expr(ss, sb);
	assert(strcmp("23+", sb->raw) == 0);
	printf("Parsed expr 2\n");
	string_stream_free(ss);
	string_builder_free(sb);

	sb = string_builder_new();
	ss = string_stream_new("2*6+3");
	parse_expr(ss, sb);
	assert(strcmp("26*3+", sb->raw) == 0);
	printf("Parsed expr 3\n");
	string_stream_free(ss);
	string_builder_free(sb);

	sb = string_builder_new();
	ss = string_stream_new("2*(6+3)");
	parse_expr(ss, sb);
	assert(strcmp("263+*", sb->raw) == 0);
	printf("Parsed expr 4\n");
	string_stream_free(ss);
	string_builder_free(sb);

	printf("ALL TESTS PASSED\n");
}
