#ifndef ARGV_H

#define ARGV_H

char **make_argv(const char *line, int *argc_out);
void free_argv(char **argv);

#endif
