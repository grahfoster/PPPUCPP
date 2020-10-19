#include <stdlib.h>
#include <stdio.h>

typedef void(*fctp)(struct Shape*);

struct Shape {
	fctp* fctps;
};

struct Circle {
	struct Shape shape;
};

void* safe_malloc(size_t n)
{
	void* p = malloc(n);
	if (!p) {
		fprintf(stderr, "Error: failed to allocate %zu bytes.\n", n);
		exit(1);
	}
	return p;
}

void draw(void* shape)
{
	((struct Shape*)shape)->fctps[0]((struct Shape*)shape);
}

void draw_shape(struct Shape* shape)
{
	printf("Shape\n");
}

void draw_circle(struct Shape* circle)
{
	printf("Circle\n");
}

struct Shape* create_shape()
{
	struct Shape* shape = (struct Shape*)safe_malloc(sizeof(struct Shape));
	shape->fctps = (fctp*)safe_malloc(sizeof(fctp));
	shape->fctps[0] = &draw_shape;
	return shape;
}

struct Circle* create_circle()
{
	struct Circle* circle = (struct Circle*)safe_malloc(sizeof(struct Circle));
	circle->shape = *create_shape();
	circle->shape.fctps[0] = &draw_circle;
	return circle;
}

int main()
{
	Shape* shape = create_shape();
	Circle* circle = create_circle();

	draw(shape);
	draw(circle);

	free(shape);
	free(circle);
}