#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

	while (i <= BUFFER_SIZE)
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
	int i = 0;

	ret = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	int s1len = ft_strlen(s1);
	int s2len = ft_strlen(s2);
	int i = 0;
	int j = 0;
	char *ret = malloc(sizeof(char) * (s1len + s2len + 1));

	while (i < s1len)
	{
		ret[i] = s1[i];
		i++;
	}
	while (j < s2len)
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

void	zero_buffer(char *buffer)
{
	int i = 0;

	while (i <= BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	char *line;
	char *substr;
	char *temp;
	int nl;
	int i;
	int read_bytes;

	line = malloc(sizeof(char) * 1);
	line[0] = '\0';
	i = find_char_buffer(buffer);

	if (i > -1)
	{
		nl = find_nl(buffer);
		if (nl > -1)
		{
			temp = line;
			substr = ft_substr(buffer, i, nl - i + 1);
			line = ft_strjoin(line, substr);
			free(temp);
			free(substr);
			if (!line || !substr)
				return (NULL);
			while (i <= nl)
			{
				buffer[i] = '\0';
				i++;
			}
			return (line);
		}
		else
		{
			temp = line;
			line = ft_strjoin(line, &buffer[i]);
			free(temp);
			if (!line)
				return (NULL);
			zero_buffer(buffer);
		}
	}
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0 && ft_strlen(line))
			return (line);
		else if (read_bytes == 0)
		{
			return (NULL);
		}
		nl = find_nl(buffer);
		if (nl > -1)
		{
			temp = line;
			substr = ft_substr(buffer, 0, nl + 1);
			line = ft_strjoin(line, substr);
			free(temp);
			free(substr);
			if (!line)
				return (NULL);
			i = 0;
			while (i <= nl)
			{
				buffer[i] = '\0';
				i++;
			}
			return (line);			
		}
		else
		{
			temp = line;
			line = ft_strjoin(line, buffer);
			free(temp);
			if (!line)
				return (NULL);
			zero_buffer(buffer);
		}
	}

	return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("test", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
	}
	// line = get_next_line(fd);
	// printf("%s", line);
}