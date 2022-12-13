
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "string_builder.h"
#include "string_stream.h"

int parse_expr(string_stream_t in, string_builder_t out) {
	int ret = 0;
	parse_term(in, out);
	char c;
	while (1) {
		c = string_stream_peek(in);
		switch(c) {
			case '-':
				string_stream_get(in);
				parse_term(in, out);
				string_builder_append(out, '-');
				continue;
			case '+':
				string_stream_get(in);
				parse_term(in, out);
				string_builder_append(out, '+');
				continue;
			case '\0':
				break;
			default:
				break;
		}
		break;
	}
	return ret;
}

int parse_term(string_stream_t in, string_builder_t out) {
	int ret = parse_fac(in, out);
	if (ret) {
		return ret;
	}
    // [KADIR] This overall code will not work for
    // invalid string constructs. How will you use
    // the unit-testing to cover and get to the
    // perfect code. For e.g., anytime after you do
    // in++, you may have wandered off over the \0.
    // The next access to in[0] can result in invalid
    // memory access. 
    // [FIXED] string stream
	char c;
	while (1) {
		c = string_stream_peek(in);
		switch(c) {
			case '*':
				string_stream_get(in);
				parse_fac(in, out);
				string_builder_append(out, '*');
				continue;
			case '/':
				string_stream_get(in);
				parse_fac(in, out);
				string_builder_append(out, '/');
				continue;
			default:
				break;
		}
		break;
	}
	return ret;
}

// [KADIR] Get into the habit of writing unit-tests, using
// code coverage and asserts. I'm leaving things at this
// for you to investigate. But these MUST be foundational
// traits which will make you efficient with development.
int parse_fac(string_stream_t in, string_builder_t out) {
	char c  = string_stream_peek(in);
	int ret = 0;
	if (c >= '0' && c <= '9') {
		string_stream_get(in);
		string_builder_append(out, c);
		ret = 0;
	} else if (c == '(') {
		string_stream_get(in);
		parse_expr(in, out);
		c = string_stream_peek(in);
		if (c == ')') {
			ret = 0;
			string_stream_get(in);
		} else {
			ret = PARSE_SYNTAX_ERROR;
		}
            // [KADIR] Always work with specific error codes and allow the
            // functions to bubble up error details.
            // You can additionally have logging methods which will be used
            // to dump dev traces that will help to debug the code flow.
            // See for example - https://www.geeksforgeeks.org/error-handling-c-programs/
	}
	return ret;
}

int parse(char* in, char* out) {
	string_builder_t sb = string_builder_new();
	string_stream_t ss = string_stream_new(in);

	if (!sb) {
		return PARSE_OUT_OF_MEM;
	} else if (!ss) {
		return PARSE_OUT_OF_MEM;
	}
	int ret = parse_expr(ss, sb);
	if (!ret) {
		string_builder_get(sb, out);
	}
	return ret;
}
