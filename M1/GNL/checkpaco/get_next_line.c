#include "get_next_line.h"

static char	*read_to_newline(int fd, char *old_stash)
{
	char	*buf;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(old_stash, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(old_stash);
			return (NULL);
		}
		buf[bytes] = '\0';
		old_stash = ft_strjoin_and_free(old_stash, buf);
	}
	free(buf);
	return (old_stash);
}

static char	*extract_line(char *full_stash)
{
	int		i = 0;
	char	*line;

	if (!full_stash || !full_stash[0])
		return (NULL);
	while (full_stash[i] && full_stash[i] != '\n')
		i++;
	if (full_stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = full_stash[j];
	line[i] = '\0';
	return (line);
}

static char	*update_stash(char *full_stash)
{
	int		i = 0, j = 0;
	char	*new_stash;

	while (full_stash[i] && full_stash[i] != '\n')
		i++;
	if (!full_stash[i])
	{
		free(full_stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(ft_strlen(full_stash + i) + 1);
	if (!new_stash)
		return (NULL);
	while (full_stash[i])
		new_stash[j++] = full_stash[i++];
	new_stash[j] = '\0';
	free(full_stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
