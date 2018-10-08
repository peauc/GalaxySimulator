//
// Created by Clément Péau on 2018-09-26.
//

#include <iostream>
#include <GLUT/glut.h>
#include <logic/Display.hpp>
#include "logic/Display.hpp"
#import "logic/Quadrant.hpp"

std::shared_ptr<Quadrant> Quad;
std::list<Star> Star;

Display::Display(int size, std::shared_ptr<class Quadrant> quadrant, const std::list<class Star> &star) : size(size)
{
	Quad = quadrant;
	Star = star;
}

void Display::drawPoints(const std::list<class Star> &vector)
{
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	for (auto it = vector.begin(); it != vector.end(); it++){
		glVertex2i((*it).getX(), (*it).getY());
	}
	glEnd();
}


void Display::drawQuadrantsRec(class Quadrant *quadrant)
{
	for(auto it = quadrant->getQuadrantList().begin(); it != quadrant->getQuadrantList().end(); it++) {
		if (*it) {
			glBegin(GL_LINE_LOOP);
			
			glVertex2d((*it)->getX(), (*it)->getY()); // x,y
			glVertex2d((*it)->getX() + (*it)->getLength(),(*it)->getY());
			glVertex2d((*it)->getX() + (*it)->getLength(), (*it)->getY() + (*it)->getLength());
			glVertex2d((*it)->getX(), (*it)->getY() + (*it)->getLength());
			
			glEnd();
			drawQuadrantsRec(it->get());
		}
		
	}
}

void Display::drawQuadrants() {
	glLineWidth(0.2);
	glColor3f(0.3, 0.3, 0.3);
	drawQuadrantsRec(Quad.get());
}

void Display::render()
{
	Quad->computeMassOfQuadrant();
	for(auto it = Star.begin(); it != Star.end() ; it++) {
		auto acc = Quad->computeTreeForce((*it));
		(*it).setX((*it).getX() + acc.first);
		(*it).setY((*it).getY() + acc.second);
	}
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 1000.0, 1000.0, 0);
		
		drawQuadrants();
		drawPoints(Star);
		glFlush();
		glutSwapBuffers();
}

void Display::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(this->size, this->size);
	glutCreateWindow("Multicore Galaxies");
	glutDisplayFunc(Display::render);
	glutIdleFunc(Display::render);
	
	glutMainLoop();
	
	
}

