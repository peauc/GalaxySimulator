//
// Created by Clément Péau on 2018-09-26.
//
#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <GLUT/glut.h>
#include "display/Display.hpp"
#import "logic/Quadrant.hpp"

std::shared_ptr<RootQuadrant> Quad;
std::vector<std::shared_ptr<Star>> Star;

Display::Display(int size, std::shared_ptr<class RootQuadrant> &quadrant, std::vector<std::shared_ptr<class Star>> &star) : size(size)
{
	Quad = std::move(quadrant);
	Star = std::move(star);
}

void Display::drawPoints(const std::vector<std::shared_ptr<class Star>> &vector)
{
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	for(const auto &it : vector) {
		glVertex2i(it->getX(), it->getY());
	}
	glEnd();
}


void Display::drawQuadrantsRec(class Quadrant &rq)
{
	for(const auto &it : rq.get_links().get_quadrantList()) {
		if (it) {
			glBegin(GL_LINE_LOOP);
			
			glVertex2d(it->getX(), it->getY()); // x,y
			glVertex2d(it->getX() + it->getHeight(), it->getY());
			glVertex2d(it->getX() + it->getHeight(),
				   it->getY() + it->getHeight());
			glVertex2d(it->getX(), it->getY() + it->getHeight());
			
			glEnd();
			drawQuadrantsRec(*it);
		}
		
	}
}

void Display::drawQuadrants() {
	glLineWidth(0.2);
	glColor3f(0.3, 0.3, 0.3);
	drawQuadrantsRec(Quad->getRootQuadrant());
}

void Display::render()
{
	Quad->getRootQuadrant().computeMassOfQuadrant();
	for(auto &it : Star) {
		auto acc = Quad->getRootQuadrant().computeTreeForce(it);
		it->setX(it->getX() + acc.first);
		it->setY(it->getY() + acc.second);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1000.0, 1000.0, 0);
	
	drawQuadrants();
	drawPoints(Star);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Display::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(this->size, this->size);
	glutCreateWindow("Multicore Galaxies");
	glutDisplayFunc(Display::render);
	
	glutMainLoop();
	
	
}



