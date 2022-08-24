/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:44:09 by hseong            #+#    #+#             */
/*   Updated: 2022/08/24 16:13:47 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_map_element
{
	WALL = '1',
	DOOR = '3',
	EMPTY = '0',
	CHECKED = 0b10000000
};

static int	check_closed(char **map, t_ivec2 pos, t_ivec2 *boundary);
static void	unmask_map(char **map, int rows, int cols);
static int	check_door(char **map, int rows, int cols,
		t_ivec2 *boundary);

/*
 * return value 1: FAIL, 0: SUCCESS
 * return value of check_closed()
 * 		1: SUCCESS, 0:FAIL
 */
int	check_map_validity(char **map, int rows, int cols, t_ivec2 *player_pos)
{
	int		i;
	int		j;
	t_ivec2	boundary;
	int		ret;

	boundary = (t_ivec2){cols, rows};
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if ((ft_strchr("NSWE", map[i][j]) && player_pos->x != -1)
				|| (map[i][j] == 51 && check_door(map, i, j, &boundary)))
				return (1);
			if (ft_strchr("NSWE", map[i][j]))
				*player_pos = (t_ivec2){j, i};
			++j;
		}
		++i;
	}
	ret = !check_closed(map, *player_pos, &boundary);
	unmask_map(map, rows, cols);
	map[player_pos->y][player_pos->x] = '0';
	return (ret);
}

static int	check_closed(char **map, t_ivec2 pos, t_ivec2 *boundary)
{
	if (pos.y < 0 || pos.y >= boundary->y || pos.x < 0 || pos.x >= boundary->x
		|| map[pos.y][pos.x] == ' ')
		return (0);
	if (map[pos.y][pos.x] & CHECKED || map[pos.y][pos.x] == WALL)
		return (1);
	map[pos.y][pos.x] |= CHECKED;
	return (check_closed(map, (t_ivec2){pos.x - 1, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x - 1, pos.y}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y}, boundary)
		&& check_closed(map, (t_ivec2){pos.x - 1, pos.y + 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x, pos.y + 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y + 1}, boundary));
}

static void	unmask_map(char **map, int rows, int cols)
{
	int		i;
	int		j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			map[i][j] &= 0b01111111;
			if (map[i][j] == ' ')
				map[i][j] = '1';
			++j;
		}
		++i;
	}
}

static int	check_door(char **map, int rows, int cols,
	t_ivec2 *boundary)
{
	int	vertical;
	int	horizon;

	vertical = 0;
	horizon = 0;
	if (cols <= 0 || cols >= boundary->x - 1
		|| rows <= 0 || rows >= boundary->y - 1)
		return (1);
	if (map[rows][cols - 1] == '1' && map[rows][cols + 1] == '1')
		horizon = 1;
	if (map[rows - 1][cols] == '1' && map[rows + 1][cols] == '1')
		vertical = 1;
	return (horizon == 0 && vertical == 0);
}
