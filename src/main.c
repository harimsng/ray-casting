#include "cub3d.h"
#include "init_data.h"
#include "screen_renderer.h"
#include "error.h"

int main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	init_data(argc, argv, &mlx_data);
	if (mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.main_img, 0, 0) < 0
		|| mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.minimap, 0, 0) < 0)
		error_handler(MLX_IMG_TO_WIN_ERROR);
	gun_image_to_window(&mlx_data, 0);
	mlx_loop_hook(mlx_data.mlx_ptr, screen_renderer, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
