
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define FD_MAX 65534
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char *get_next_line(int fd);

#endif