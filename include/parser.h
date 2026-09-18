#ifndef PARSER_H
#define PARSER_H

char **parse_command(char *line);
void free_tokens(char **tokens);

#endif
