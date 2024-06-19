#ifndef VECTORS_H
# define VECTORS_H

# include "fixed.h"

// (x, y, z) coordinates and type is 1 for a point and 0 for a vector
typedef struct s_tuple
{
	fixed	x;
	fixed	y;
	fixed	z;
	fixed	type;		
}			t_tuple;

// rays 
typedef struct	s_ray
{
	t_tuple		origin;	// point of origin
	t_tuple		direction;	// vector
}				t_ray;


// Objects such as spheres, cylindres and rectangles
typedef struct	s_object
{
	int			id;
	int			type;
}				t_object;

// intersection between ray and object
// will contain more values later
typedef	struct	s_intesect
{
	fixed		t_value; // time or distance value for the intersecting ray
	t_object	*obj; // pointer to the object that was intersected
}




/* ---------- VECTOR FUNCTIONS ---------- */
t_tuple	    *point(fixed x, fixed y, fixed z);
t_tuple	    *vector(fixed x, fixed y, fixed z);
t_tuple	    *add_vect(t_tuple *v1, t_tuple *v2);
t_tuple	    *subtr_vect(t_tuple *v1, t_tuple *v2);
t_tuple	    *negate_vect(t_tuple *vector);
t_tuple	    *scale_vect(t_tuple *vector, fixed scalar);
t_tuple	    *div_vect(t_tuple *vector, fixed scalar);
fixed	    magnitude(t_tuple *vect);
t_tuple	    *normalise(t_tuple *vector);
fixed	    dot_prod(t_tuple *v1, t_tuple *v2);
t_tuple	    *cross_prod(t_tuple *v1, t_tuple *v2);

#endif