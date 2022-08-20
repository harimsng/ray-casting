#ifndef READ_CONFIG_H
# define READ_CONFIG_H

# include "cub3d.h"

# define TEXTURE_LIST_NUM (7)
# define ALL_OPTION_FILLED (0b1111111)

void	get_config_info(int fd, t_mlx_data *mlx_data);
int		check_config_path(const char *path);

#endif
