#include "../include/get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gnl_strichr(char *str, int sumb)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == (char)sumb)
			return (i);
	}
	return (-1);
}

char	*gnl_strdup(const char *str)
{
	char	*res;
	char	*p;
	size_t	size;

	size = (size_t)gnl_strlen((char *)str) + 1;
	res = malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL);
	p = res;
	while (*str)
	{
		*res = *str;
		str++;
		res++;
	}
	*res = 0;
	return (p);
}

static void	*gnl_memmove(void *dest, const void *source, size_t count)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = -1;
	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)source;
	if (dest == source)
		return (dest);
	if (dest > source)
		while (count--)
			p1[count] = p2[count];
	else
		while (++i != count)
			p1[i] = p2[i];
	return (dest);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	size;
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = gnl_strlen((char *)s1);
	len2 = gnl_strlen((char *)s2);
	size = len1 + len2 + 1;
	res = malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (s1)
		gnl_memmove((void *)res, (const void *)s1, len1);
	gnl_memmove((void *)(res + len1), (const void *)s2, len2);
	*(res + size - 1) = 0;
	if (s1)
		free(s1);
	return (res);
}
