#ifndef PIXELS_H
# define PIXELS_H

#include "fixed.h"
#include "vectors.h"

typedef struct  s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}           t_img;

void    my_mlx_pixel_put(t_img *img, int x, int y, int colour);

#endif