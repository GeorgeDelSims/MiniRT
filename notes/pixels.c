#include "pixels.h"

void    write_pixel(t_img *img, int x, int y, int colour)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = colour;
}

