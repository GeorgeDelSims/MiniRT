#include "fixed.h"
#include "pixels.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	int		i = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1920, "MiniRT");
	img.img = mlx_new_image(mlx, 1920, 1920);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (i < 1920)
		write_pixel(&img, i++, 100, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// (void)mlx_win;
	mlx_loop(mlx);
}

