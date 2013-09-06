/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greyrol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/02 15:43:45 by greyrol           #+#    #+#             */
/*   Updated: 2013/09/02 15:43:47 by greyrol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/map.h"
#include "includes/file_desc.h"
#include "includes/tools.h"
#include "includes/main.h"
#include <stdio.h>
void	ft_stdout()
{
	char buff;

	while (read(STDOUT_FILENO, &buff, 1))
	{
		m_putchar(buff);
	}
}

int		read_head(int fd, t_map *map)
{
	char	*temp;
	if (map->stats[3] < 4)
		return (-1);
	temp = (char *) malloc(sizeof(map->stats[3]));
	if (read(fd, temp, map->stats[3]) < 0)
		return (-2);
	map->cset[2] = temp[map->stats[3]--];
	map->cset[1] = temp[map->stats[3]--];
	map->cset[0] = temp[map->stats[3]--];
	map->stats[1] = m_atoi(temp, map->stats[3]);
	map->stats[3] += 3;
	if (map->stats[1] < 1)
		return (-3);
	read(fd, temp, 1);
	return (1);
}

void	set_to_nul(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int		ft_get_file_size(t_map *map, char *file)
{
	int		fd;
	char	err;
	char	buff_1;
	char	*buff;

	set_to_nul(&map->stats[0], &map->stats[2], &map->stats[3]);
	if ((fd = open(file, O_RDONLY | O_RDWR)) < 0)
		return (-1);
	while ((err = read(fd, &buff_1, 1) > 0) && buff_1 != '\n')
		map->stats[3]++;
	map->stats[3]++;
	if (err <= 0)
		return (-2);
	while ((err = read(fd, &buff_1, 1)) > 0 && buff_1 != '\n')
		map->stats[0]++;
	map->stats[0]++;
	if (err < 0)
		return (-3);
	if (!(buff = (char*)malloc(sizeof(char) * map->stats[0])))
		return (-4);
	while (err > 0)
	{
		if ((err = read(fd, buff, map->stats[0])) > 0)
			map->stats[2] += err;
		if (err > 0 && err != map->stats[0])
			err = -1;
	}
	/*while ((err = read(fd, buff, map->stats[0])) > 0)
		map->stats[2] += err;*/
	if (close(fd) < 0 || err < 0)
		return (-5);
	printf("%d\n", map->stats[0]);
	return (1);
}

int		ft_file_to_array(t_map *map, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	map->map = (char *) malloc(sizeof(char) * map->stats[2]);
	if (read_head(fd, map) < 0)
		return (-1);
	if (read(fd, map->map, map->stats[2]))
		return (-2);
	return (1);
}

/*if (buff[map->stats[0] - 1] != '\n')
	return (0);
i++;*/

/*int		ft_get_file(t_map *map, char *file)
{
	int		i;
	int		skip;
	int		fd;
	char	err;
	char	buff;

	i = 0;
	skip = 0;
	fd = open(file, O_RDONLY | O_RDWR);
	if (fd < 0)
		return (0);
	while ((err = read(fd, &buff, 1)) > 0 && buff != '\n')
	{
		map->stats[3] = skip++;
	}
	if (err < 0)
		return (0);
	while ((err = read(fd, &buff, 1) > 0)
	{
		map->stats[2] = i++;
	}
	if (close(fd) < 0 || err < 0)
		return (0);
	return (1);
}*/
