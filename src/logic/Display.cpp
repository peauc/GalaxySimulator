//
// Created by Clément Péau on 2018-09-26.
//

#include <iostream>
#include <GLUT/glut.h>
#include "logic/Display.hpp"

Display::Display(int size, const class Quadrant &quadrant) : size(size)
{

}

void Display::render()
{
	glClear( GL_COLOR_BUFFER_BIT );

	glPushMatrix();
	glColor3d( 1.0, 1.0, 1.0 );
	glutSolidTeapot( 0.5 );
	
	glColor3d( 0.0, 0.0, 1.0 );
	glTranslated( 0.0, 0.6, 0.0 );
	glutSolidTeapot( 0.25 );
	glPopMatrix();
	
	glutSwapBuffers() ;
}

void Display::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(this->size, this->size);
	glutCreateWindow("Multicore Galaxies");
	glutDisplayFunc(Display::render);
	glutMainLoop();
}
