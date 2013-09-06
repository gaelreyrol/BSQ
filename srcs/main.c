/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greyrol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/02 11:20:04 by greyrol           #+#    #+#             */
/*   Updated: 2013/09/02 11:20:06 by greyrol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/map.h"
#include "includes/main.h"
#include "includes/tools.h"
#include "includes/file_desc.h"

#include <stdio.h>
#include <time.h>
void	print_time(char *function, clock_t start, clock_t end);

void	build_map(char *file);
int		check_char_integrity(t_map *map, int pos);
void	draw_square(t_map *map);
void	bsq(t_map *map);

void	build_map(char *file)
{
	t_map	map;

	map.sq_pos = 0;
	map.sq_size = 0;
	if (ft_get_file_size(&map, file) < 0 || ft_file_to_array(&map, file) < 0)
	{
		write(2, "map error\n", 10);
		return ;
	}
	bsq(&map);
	//free(map.map);
}

int		check_char_integrity(t_map *map, int pos)
{
	/*while (map->map[pos] != map->cset[0] && pos < map->stats[2])
	{
		if (map->map[pos] != map->cset[0] 
				&& map->map[pos] != map->cset[1] && map->map[pos] != '\n')
			return (-1);
		pos++;
	}*/
	while (map->map[pos] != map->cset[0] && pos < map->stats[2])
	{
		if (map->map[pos] == map->cset[0] 
			|| map->map[pos] == map->cset[1] || map->map[pos] == '\n')
			pos++;
		else
			return (-1);
	}
	return (pos);
}

void	draw_square(t_map *map)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	pos = map->sq_pos;
	while (i < map->sq_size)
	{
		while (j < map->sq_size)
		{
			map->map[pos] = map->cset[2];
			pos++;
			j++;
		}
		pos = pos - map->sq_size + map->stats[0] ;
		j = 0;
		i++;
	}
}

void	bsq(t_map *map)
{
	int		pos;
	int		i;
	int		j;

	pos = 0;
	i = 0;
	j = 0;
	while (pos < map->stats[2])
	{
		while (map->map[pos] != map->cset[0] && pos < map->stats[3])
			pos++;
		check(map, pos);
		pos++;
	}
	draw_square(map);
	write(1, map->map, map->stats[2]);
}

/*void	bsq(t_map *map)
{
	int		pos;
	int		i;
	int		j;

	pos = 0;
	i = 0;
	j = 0;
	while (pos < map->stats[2])
	{
		if (check_char_integrity(map, pos) < 0)
		{
			write(2, "map error\n", 10);
			return ;
		}
		check(map, pos);
		pos++;
	}
	pos = map->sq_pos;
	draw_square(map, i, j, pos);
	write(1, map->map, map->stats[2]);
}*/

int		main(int argc, char **argv)
{
	int	i;
	clock_t	start;

	i = 1;
	if (argc == 1)
		ft_stdout();
	else
	{
		while (i < argc)
		{
			start = clock();
			build_map(argv[i]);
			//print_time("bsq", start, clock());
			i++;
		}
	}
	return (0);
}
