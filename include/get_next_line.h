#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int		gnl_strlen(char *str);
int		gnl_strichr(char *str, int sumb);
char	*gnl_strdup(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
