#ifndef POSTFIX_PARSER_H
#define POSTFIX_PARSER_H

#include <string_builder.h>
#include <string_stream.h>

#define PARSE_OUT_OF_MEM -1
#define PARSE_SYNTAX_ERROR -2

// [KADIR] Give examples for each of these so it is easier for the reader to
// understand these expressions.
//
// expr -> term erest
// eg. 5+2*(1-7): term = 4, erest = +2*(1-7)
//
// erest -> - term {print - } erest | + term {print +} erest | E
// eg. 
//
// term -> fac trest
// trest -> * fac {print *} trest | / fac {print / } trest | E
// fac -> num | ( expr )
// num -> digit {print digit}

int parse_expr(string_stream_t in, string_builder_t out);

int parse_term(string_stream_t in, string_builder_t out);

int parse_fac(string_stream_t in, string_builder_t out);

int parse(char* in, char* out);

#endif
