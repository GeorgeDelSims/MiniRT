#ifndef FIXED_H
# define FIXED_H

# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx_linux/mlx.h"

typedef int64_t fixed;

#define FRACTIONAL_BITS 16
#define SCALE_FACTOR (1 << FRACTIONAL_BITS)

fixed       int_to_fixed(int i);
int         fixed_to_int(fixed f);
fixed       float_to_fixed(float f);
float       fixed_to_float(fixed f);
fixed       fixed_mul(fixed a, fixed b);
fixed       fixed_div(fixed a, fixed b);
fixed       fixed_square(fixed a);
fixed       fixed_sqrt(fixed a);

#endif
