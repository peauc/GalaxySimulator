#pragma OPENCL EXTERNSION cl_khr_fp64 : enable

typedef struct m_star {
	float cmx;
	float cmy;
	float height;
	float width;
	float accx;
	float accy;
	float x;
	float y;
	float mass;
	unsigned int depth;
} Star;

typedef struct m_quadrant {
	float cmx;
	float cmy;
	float height;
	float width;
	float accx;
	float accy;
	float x;
	float y;
	float mass;
	unsigned int depth;
} Quadrant;

#define SOFTENER 100000
#define G 0.00066742
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
	float v1 = fabs(star->x - quad->x);
	float v2 = fabs(star->y - quad->y);
	float theta = quad->width / (v1 + v2);
//	// added the theta check
	//float theta = THETA;
	if (theta < THETA || hasChild) {
		float dx = star->x - quad->x;
		float dy = star->y - quad->y;
		float r = sqrt(dx * dx + dy * dy + SOFTENER);
		if (r > 0) {
			float k = G * star->mass / (r*r*r);
			star->accx += k * (quad->x - star->x);
			star->accy += k * (quad->y - star->y);
		}
		star->depth = quad->depth;
	}
}

//Divide the data so each thread has one
void kernel test1(global Star *list, unsigned long starSize, Quadrant pQuadrant, bool hasChild)
{
	for(unsigned int it = 0; it < starSize; it++) {
		computeForceSingleQuadrantSingleBody(&list[it], &pQuadrant, hasChild);
	}
}
