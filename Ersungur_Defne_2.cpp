﻿/*****
  CTIS164 - HOMEWORK #3
DEFNE ERSUNGUR
22003296
SECTION 001
Interactivity: Animating Shapes

 
*****/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "vec.h"

#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500

#define TIMER_PERIOD   16 // Period for the timer.
#define TIMER_ON        1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
float A = 100, //amplitude
fq = 1,  //frequency
C = 0,   //horizontal phase shift
B = 0;   //vertical phase shift

//different angles for different lights
float angle = 0;
float angl = 0;
float ang = 0;
bool freeze = false;  //freeze 

typedef struct {
    float r, g, b;
} color_t;

typedef struct {
    vec_t   pos;
    color_t color;
    vec_t   vel;
} light_t;

typedef struct {
    vec_t pos;
    vec_t N;
} vertex_t;

#define NUM 3

light_t light[3] =
{
   { {    0, 0 }, { 1, 0, 0 }, { 3,  2} },
   { {  200, 0 }, { 0, 1, 0 }, {-2, -1} },
   { { -200, 0 }, { 0, 0, 1 }, { 3, -2} }
};

color_t mulColor(float k, color_t c) {
    color_t tmp = { k * c.r, k * c.g, k * c.b };
    return tmp;
}

color_t addColor(color_t c1, color_t c2) {
    color_t tmp = { c1.r + c2.r, c1.g + c2.g, c1.b + c2.b };
    return tmp;
}

// To add distance into calculation
// when distance is 0  => its impact is 1.0
// when distance is 350 => impact is 0.0
// Linear impact of distance on light calculation.
double distanceImpact(double d) {
    return (-1.0 / 350.0) * d + 1.0;
}

color_t calculateColor(light_t source, vertex_t v) {
    vec_t L = subV(source.pos, v.pos);
    vec_t uL = unitV(L);
    float factor = dotP(uL, v.N) * distanceImpact(magV(L));
    return mulColor(factor, source.color);
}


//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(y + r * cos(angle), x + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
float f(float x) {
    return A * sin((fq * x + C) * D2R) + B;
}

//drawing and rotating lights and their orbits 
void drawAngle() {
    float r = fabs(A); //amplitude

    glLineWidth(5);
    glColor3f(1, 1, 0);
    circle_wire(0, -30, r+30); //red circle 
    circle_wire(0, -30, r + 130); //blue circle 
    circle_wire(0, -30, r + 80); //green circle 

   

    //lights on circle wire
    glColor3f(1, 0, 0);
    circle((r+30) * cos(angle * D2R) + -30, (r+30) * sin(angle * D2R) , 10);
    glColor3f(0, 0, 1);

    circle((r + 130) * cos(angl * D2R) + -30, (r + 130) * sin(angl * D2R), 10);
    glColor3f(0, 1, 0);

    circle((r + 80) * cos(ang * D2R) + -30, (r + 80) * sin(ang * D2R), 10);
    

}

//
// To display onto window using OpenGL commands
//


void display() {

    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    vprint(-240, 220, GLUT_BITMAP_8_BY_13, "HOMEWORK #3");
    vprint(-240, 200, GLUT_BITMAP_8_BY_13, "by Defne Ersungur");


   
    // calculate the color of each point on the surface
    for (int x = -50; x <= 150; x++) {
        vertex_t P = { { x, -100 }, { 0, 1 } };

        color_t res = { 0, 0, 0 };
        for (int i = 0; i < NUM; i++) {
            res = addColor(res, calculateColor(light[i], P));
        }

        //line segments will be used to paint the area in depth
        glBegin(GL_LINES);
        //from the surface
        glColor3f(res.r, res.g, res.b);
        glVertex2f(x-50, +60);
        //to the bottom
        glColor3f(0, 0, res.b);
        glVertex2f(x-50, -100);
        
        glEnd();
    }
 

    glLineWidth(105);
    glColor3f(0, 0, 0);
    circle_wire(5, -20, 120);
   
    drawAngle();
    
    glutSwapBuffers();

}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}
//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    case GLUT_KEY_F1:   glColor3f(0, 0, 1);
        glVertex2f(x - 50, +60); break;
    case GLUT_KEY_F4:  freeze=false;  break;
 }
    // to refresh the window it calls display() function
    glutPostRedisplay();
}



//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}






#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    


    for (int i = 0; i < NUM; i++) {

        light[i].pos = addV(light[i].pos, light[i].vel);

        // Reflection of lights
        if (light[i].pos.x < 200 || light[i].pos.x > -200) {

            light[i].vel.x *= -1;
        }

        if (light[i].pos.y > 200 || light[i].pos.y < -200) {
            
             light[i].vel.y *= -1;

        }
    }

   

    //giving lights to different speed
    angle += -2;
    if (angle > 360)
        angle -= 360;

    angl += 0.6;
    if (angl > 360)
        angl -= 360;

    ang += 1;
    if (ang > 360)
        ang -= 360;



    //to refresh the window it calls display() function
    glutPostRedisplay(); //display()

   

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Lighting Simulation");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

   

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}