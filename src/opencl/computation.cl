typedef struct m_star {
	double cmx;
	double cmy;
	double height;
	double width;
	double accx;
	double accy;
	double x;
	double y;
	double mass;
	unsigned int depth;
} Star;

typedef struct m_quadrant {
	double cmx;
	double cmy;
	double height;
	double width;
	double accx;
	double accy;
	double x;
	double y;
	double mass;
	unsigned int depth;
} Quadrant;

#define SOFTENER 1000
#define G 0.0000066742
#define THETA 0.5

void computeForceSingleQuadrantSingleBody(global Star *star, Quadrant *quad, bool hasChild)
{
	if (star->depth == quad->depth)
	{
		star->depth = 0;
		return;
	}
	if (star->depth > quad->depth)
		return;
	double theta = quad->width / (fabs((star->x - quad->x)) + fabs((star->y - quad->y)));
	if (theta || hasChild) {
		double dx = star->x - quad->x;
		double dy = star->y - quad->y;
		double r = sqrt(pow(dx, 2) + pow(dy, 2) + SOFTENER);
		if (r > 0) {
			double k = G * star->mass / pow(r, 3);
			star->accx += k * (quad->x - star->x);
			star->accy += k * (quad->y - star->y);
		}
		star->depth = quad->depth;
	}
}

//Divide the data so each thread has one
void kernel test1(global Star *list, unsigned long starSize, Quadrant pQuadrant, bool hasChild)
{
	exit(1);
	for(unsigned int it = 0; it < starSize; it++) {
		computeForceSingleQuadrantSingleBody(&list[it], &pQuadrant, hasChild);
	}
}
