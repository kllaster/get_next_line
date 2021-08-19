#include "get_next_line.h"

static int	gnl_end(int error, char **line, char **line_buff)
{
	if (error == -1 || error == 0)
	{
		if (error == -1 && line)
		{
			if (*line)
				free(*line);
			*line = NULL;
		}
		if (line_buff && *line_buff)
			free(*line_buff);
		*line_buff = NULL;
		return (error);
	}
	return (error);
}

static char	*gnl_get_buff(int i, char *line_buff)
{
	char	*new_buff;

	if (line_buff[i] && line_buff[i + 1])
	{
		new_buff = gnl_strdup(line_buff + i + 1);
		if (new_buff == NULL)
			return (NULL);
	}
	if (!line_buff[i] || !line_buff[i + 1])
		new_buff = gnl_strdup("");
	free(line_buff);
	return (new_buff);
}

static char	*gnl_get_line(char **line, char *line_buff)
{
	int		i;
	int		index;

	if (!line_buff)
	{
		*line = gnl_strdup("");
		return (gnl_strdup(""));
	}
	index = gnl_strichr(line_buff, '\n');
	if (index == -1)
		index = gnl_strlen(line_buff);
	*line = malloc((index + 1) * sizeof(char));
	if (*line == NULL)
		return (NULL);
	i = -1;
	while (++i < index)
		(*line)[i] = line_buff[i];
	(*line)[i] = 0;
	return (gnl_get_buff(i, line_buff));
}

int	gnl_check_read(int res, char **line, char **line_buff)
{
	if (res == -1)
		return (gnl_end(-1, line, line_buff));
	else if (!res)
	{
		*line_buff = gnl_get_line(line, *line_buff);
		if (*line_buff == NULL)
			return (gnl_end(-1, line, line_buff));
		else if (!(*line_buff)[0])
			return (gnl_end(0, line, line_buff));
		else if (*line && !(*line_buff)[0])
			return (1);
	}
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static char	*line_buff;
	char		buff[BUFFER_SIZE + 1];
	int			res;
	int			read_end;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, buff, 0) == -1)
		return (gnl_end(-1, NULL, &line_buff));
	while (gnl_strichr(line_buff, '\n') == -1)
	{
		res = read(fd, buff, BUFFER_SIZE);
		read_end = gnl_check_read(res, line, &line_buff);
		if (read_end != 2)
			return (read_end);
		buff[res] = '\0';
		line_buff = gnl_strjoin(line_buff, buff);
		if (line_buff == NULL)
			return (gnl_end(-1, line, &line_buff));
	}
	line_buff = gnl_get_line(line, line_buff);
	if (line_buff == NULL)
		return (gnl_end(-1, line, &line_buff));
	return (1);
}
