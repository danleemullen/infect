#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <set>

#include "entity.h"
#include "population.h"
#include "barriers.h"

#define PLOT_HEIGHT 100
#define SAMPLE_SIZE 500

int evect::HEIGHT{700};
int evect::WIDTH{1080};
int evect::BOTTOM_BORDER{PLOT_HEIGHT};

int SIZE = 3;

int walls[][4] = {
                  {200,0,250,250},
                  {250, 250, 200,300}, 
                  {200,evect::HEIGHT,200,325},
                  {500,0,500,125},
                  {500,evect::HEIGHT, 500, 175},
                  {0,0,0,0}
                 };

int boxes[][4] = {
    MAKE_BOX(300,300),
    MAKE_BOX(400,500),
    MAKE_BOX(600,500),
    MAKE_BOX(700,300),
    MAKE_BOX(950,500)
};

int no_walls[][4] = {
                  {0,0,0,0}
                 };


#define SPREAD_FACTOR 4

population p(SAMPLE_SIZE, 200);
barriers b(boxes);

//barriers b(walls);

void reshape(int width, int height) {

    evect::set_height(height-PLOT_HEIGHT);
    evect::set_width(width);
    
    glViewport(0, 0, width, height);    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width - 1, 0, height-1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void draw_walls() {
    glColor3f(0.5, 0.5, 0.75);
    glBegin(GL_LINES);

    for (wall* w : b.all_walls()) {
        // std::cout << w->X1() << " " << w->Y1() << " " << w->X2() << " " << w->Y2() << std::endl;
        glVertex2i(w->X1(), w->Y1());
        glVertex2i(w->X2(), w->Y2());
        //glVertex2i(w->cx, w->cy);
        //glVertex2i(w->nx,w->ny);
    }
    glEnd();
}

void plot(void) {
    static int iteration = 0;
    static int x_plot = 0;
    int aiViewport[4];
    
    if (iteration % 3 == 0) {
        glGetIntegerv(GL_VIEWPORT, aiViewport);
        
        glViewport(0, 0, (GLsizei)evect::WIDTH, (GLsizei) PLOT_HEIGHT);
        glLoadIdentity();
        glScissor(0,0, evect::WIDTH, PLOT_HEIGHT);
        glPushMatrix();
        
        glOrtho(0, evect::WIDTH, 0, SAMPLE_SIZE, 0, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glColor3f(1.0, 1.0, 0.5);

        glBegin(GL_LINES);
            glVertex2i(x_plot, 0);
            glVertex2i(x_plot, p.active_cases());
        glEnd();

        glViewport(aiViewport[0], aiViewport[1], (GLsizei) aiViewport[2], (GLsizei) aiViewport[3]);
        glPopMatrix();
        x_plot++;
    }
        iteration++;
}

void init(void){
glClearColor(0.0,0.0,0.0,1.0);
glPointSize(2.0);
}

void Timer(int ex)
{
    glutPostRedisplay();
    glutTimerFunc(30,Timer,0);
    p.move_all(b);
    p.infect_all(SPREAD_FACTOR);
  
}

void square(entity *e)
{
    int x=e->X(), y=e->Y();
    int s = SIZE;
    float ic = 0.0, cc=1.0, ec = 0.0;

    if (e->is_infected()) {
        ic = 1.0;
        cc = 0.0;
    } else if (e->is_contagious()) {
        ec = 1.0;
    } else if (! e->is_susceptible()) {
        cc = 0.0;
        ec = 1.0;
    }
 glColor3f(ic, cc, ec);
 glBegin(GL_POLYGON);
  glVertex2i(x, y);
  //glVertex2i(x, y+s);
  glVertex2i(x+s, y+s);
  glVertex2i(x+s, y);
 glEnd();
// glFlush();
} 

void display(void)
{
    glScissor(0,100, evect::WIDTH, evect::HEIGHT);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_walls();
    for (entity *e : p.get_entities()) {
        square(e);
    }

    plot();
    
    glFlush();
 
    glutSwapBuffers();

}

void idle(void){
/* do nothing */
}

int main(int argc, char **argv){
    srand (time(NULL));
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowPosition(0,0);
std::cout << "Width: " << evect::WIDTH << std::endl;
std::cout << "Height: " << evect::HEIGHT << std::endl;
glutInitWindowSize(evect::WIDTH, evect::HEIGHT);
glutCreateWindow(argv[0]);
init();
glutIdleFunc(idle);
glutReshapeFunc(reshape);
glutDisplayFunc(display);
glutTimerFunc(0,Timer,0);
glutMainLoop();
return(1);
}