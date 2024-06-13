#include "fixed.c"


// (x, y, z) coordinates and type is 1 for a point and 0 for a vector
typedef struct s_vect
{
	fixed	x;
	fixed	y;
	fixed	z;
	fixed	type;		
}		t_vect;


/* ---------- VECTOR FUNCTIONS ---------- */

// creates a point from three fixed values
t_vect	*point(fixed x, fixed y, fixed z)
{
	t_vect	*point;

	point = (t_vect *)malloc(sizeof(t_vect));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->type = 1;
	return (point);
}

// creates a vector from three fixed values
t_vect	*vector(fixed x, fixed y, fixed z)
{
	t_vect	*vector;

	vector = (t_vect *)malloc(sizeof(t_vect));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->type = 0;
	return (vector);
}

// works for adding a point to a vector or a vector to a vector
t_vect	*add_vect(t_vect *v1, t_vect *v2)
{
	t_vect	*result;

	result = (t_vect *)malloc(sizeof(t_vect));
	if (!result)
		return (NULL);
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	result->type = v1->type + v2->type;
	return (result);
}

// subtract a vector or point from another one, or a vector from a point
// you can't subtract a point from a vector
t_vect	*subtr_vect(t_vect *v1, t_vect *v2)
{
	t_vect	*result;

	result = (t_vect *)malloc(sizeof(t_vect));
	if (!result)
		return (NULL);
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	result->type = v1->type - v2->type;
	return (result);
}

// Get the opposite of a vector 
t_vect	*negate_vect(t_vect *vector)
{
	t_vect	*neg;

	neg = (t_vect *)malloc(sizeof(t_vect));
	if (!neg)
		return (NULL);
	neg->x = fixed_mul(vector->x, -1);
	neg->y = fixed_mul(vector->y, -1);
	neg->z = fixed_mul(vector->z, -1);
	neg->type = vector->type;
	return (neg);
}


// Scalar mutiplication
t_vect	*scale_vect(t_vect *vector, fixed scalar)
{
	t_vect	*result;

	result = (t_vect *)malloc(sizeof(t_vect));
	if (!result)
		return (NULL);
	result->x = fixed_mul(vector->x, scalar);
	result->y = fixed_mul(vector->y, scalar);
	result->z = fixed_mul(vector->z, scalar);
	result->type = vector->type;
	return (result);
}

// Scalar Division
t_vect	*scale_vect(t_vect *vector, fixed scalar)
{
	t_vect	*result;

	result = (t_vect *)malloc(sizeof(t_vect));
	if (!result)
		return (NULL);
	result->x = fixed_div(vector->x, scalar);
	result->y = fixed_div(vector->y, scalar);
	result->z = fixed_div(vector->z, scalar);
	result->type = vector->type;
	return (result);
}

// Vector Magnitude  (= total length of a vector)
fixed	magnitude(t_vect *vect)
{
	fixed	sum;

	sum = fixed_square(vect->x) + fixed_square(vect->y) + fixed_square(vect->z);
	return (fixed_sqrt(sum));
}



