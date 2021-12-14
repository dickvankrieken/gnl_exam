#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	find_char_buffer(char *buffer)
{
	int i = 0;

	while (i <= BUFFER_SIZE)
	{
		if (buffer[i] != '\0')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	find_nl(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char *ft_substr(char *s, int start, int len)
{
	char *ret;
	int i;

	ret = malloc(sizeof(char) * len + 1);
	if (s[i] = '\0')
	{

	}
}

char *get_next_line(int fd)
{
	static char *buffer;
	char *line;
	char *substr;
	char *temp;
	int i;

	i = find_char_buffer(buffer);
	if (i > -1)
	{
		int nl = find_nl(buffer);
		if (nl > -1)
		{
			temp = line;
			substr = ft_substr(buffer, i, nl);
			line = ft_strjoin(line, substr);
			free(temp);
			free(substr);
			if (!line)
			{
				return (NULL);
			}
		}
	}
	else
	{

	}
}

int main()
{
	int fd;
	char *line;

	fd = open("test", O_RDONLY);
	line = get_next_line(fd);

}