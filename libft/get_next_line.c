/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:40:06 by cproesch          #+#    #+#             */
/*   Updated: 2021/08/09 15:41:25 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_initialization(int fd, char *line, char *buf, int *ret)
{
	if ((BUFFER_SIZE <= 0) || (fd < 0))
		return (NULL);
	*ret = 1;
	line = ft_substr(buf, 0, ft_find('\0', buf));
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_return_line(char *line, char *buf, int nl_index)
{
	char	*free_var;

	ft_memcpy(buf, line + nl_index + 1, (ft_find('\0', line) - (nl_index + 1)));
	buf[ft_find('\0', line) - (nl_index + 1)] = '\0';
	free_var = line;
	line = ft_substr(line, 0, nl_index + 1);
	ft_del(free_var);
	if (!line)
		return (NULL);
	return (line);
}

char	*add_buffer_to_line(char *line, char *buf)
{
	char	*free_var;

	free_var = line;
	line = ft_strjoin(line, buf);
	ft_del(free_var);
	if (!line)
		return (NULL);
	return (line);
}

int	ft_read(int fd, char *buf, char *line)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	if (ret == -1)
	{
		ft_del(line);
		return (-1);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	int			ret;
	int			nl_index;

	line = NULL;
	line = ft_initialization(fd, line, buf, &ret);
	if (!line)
		return (NULL);
	while (ret)
	{
		nl_index = ft_find('\n', line);
		if ((nl_index) || (line[0] == '\n'))
			return (ft_return_line(line, buf, nl_index));
		ret = ft_read(fd, buf, line);
		if (!ret)
			break ;
		line = add_buffer_to_line(line, buf);
		if ((!line) || (ret == -1))
			return (NULL);
	}
	if (line[0])
		return (line);
	else
		return (ft_del(line));
}
