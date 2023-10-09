/*
CTIS164 - HOMEWORK 2
DEFNE ERSUNGUR
22003296
SECTION 001
Interactivity: Animating Shapes

Use the space button to hit the baloons, you can use the arrow keys to move the knife.



*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 400
#define _CRT_SECURE_NO_WARNINIGS 
#define D2R 0.0174532
#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer



/* Global Variables for Template File */



int fx, fy;    // knife exit point
int totalHit = 0; //hit count
int  winWidth, winHeight; // current Window width and height
int knifeAng = 0;  //angle of knife
int ypos = 0;  //knife y position
bool up = false, down = false, right = false, left = false;
bool freeze = false;  //freeze 

//target struct
typedef struct b {
	int x, y;
	int ang;
	bool a = false;
}baloon_t;


//knife struct
typedef struct c {
	int x, y;
	int fAng;
	bool exist = false;  
}knife_t;


baloon_t targetArr[11];  //targets array
knife_t arrArr[10];   //knife array
int exArr = 0;  //existing knife
int circleItr = -300;    // target iterator




//knife rotation 
int rx(int x, int y, int ang) {
	return x * cos(ang * D2R) - y * sin(ang * D2R);
}

int ry(int x, int y, int ang) {
	return x * sin(ang * D2R) + y * cos(ang * D2R);
}






// to draw circle
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
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


void dspBackground() {
	//sky
	glColor3ub(95, 50, 170);
	glRectf(-400, 250, 400, -250);
	//grass
	glColor3ub(20, 70, 15);
	glRectf(-400, -100, 400, -250);

	//Moon
	glColor3f(1, 2, 0);
	circle(-260, 150, -50);

	glColor3ub(95, 50, 170);
	circle(-230, 150, -50);


	//clouds
	glColor3f(0.7, 0.7, 0.7);
	circle(-160, 150, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-120, 160, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-140, 140, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-100, 140, -30);

	glColor3f(0.7, 0.7, 0.7);
	circle(50, 70, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(90, 70, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(70, 50, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(110, 50, -30);

	glColor3f(0.7, 0.7, 0.7);
	circle(190, 110, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(230, 110, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(210, 90, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(250, 90, -30);

	glColor3f(0.7, 0.7, 0.7);
	circle(-300, 100, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-270, 110, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-290, 90, -30);
	glColor3f(0.7, 0.7, 0.7);
	circle(-250, 90, -30);




}
//display knife
void dspKnife(int xpos, int ypos) {

	glLineWidth(10);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(rx(cos(-90 * D2R) * 25, sin(-90 * D2R) * 25, knifeAng) + xpos + 10, ry(cos(-90 * D2R) * 25, sin(-90 * D2R) * 25, knifeAng) + ypos);
	glVertex2f(rx(cos(90 * D2R) * 25, sin(90 * D2R) * 25, knifeAng) + xpos + 10, ry(cos(90 * D2R) * 25, sin(90 * D2R) * 25, knifeAng) + ypos);
	glEnd();


	glColor3f(0.7, 0.7, 0.7);
	glLineWidth(20);
	glBegin(GL_LINES);
	glVertex2f(rx((cos(0 * D2R) * 25) - 20, (sin(0 * D2R) * 25), knifeAng) + xpos, ry((cos(0 * D2R) * 25) - 20, (sin(0 * D2R) * 25), knifeAng) + ypos);
	glVertex2f(rx((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25), knifeAng) + xpos, ry((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25), knifeAng) + ypos);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(20);
	glBegin(GL_LINES);
	glVertex2f(rx((cos(0 * D2R) * 25) - 10, (sin(0 * D2R) * 25), knifeAng) + xpos, ry((cos(0 * D2R) * 25) - 20, (sin(0 * D2R) * 25), knifeAng) + ypos);
	glVertex2f(rx((cos(0 * D2R) * 25) - 40, (sin(0 * D2R) * 25), knifeAng) + xpos, ry((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25), knifeAng) + ypos);
	glEnd();

	glLineWidth(1);

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_TRIANGLES);
	glVertex2f(rx((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25) + 10, knifeAng) + xpos, ry((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25) + 10, knifeAng) + ypos);
	glVertex2f(rx((cos(0 * D2R) * 25) + 30, (sin(0 * D2R) * 25), knifeAng) + xpos, ry((cos(0 * D2R) * 25) + 30, (sin(0 * D2R) * 25), knifeAng) + ypos);
	glVertex2f(rx((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25) - 10, knifeAng) + xpos, ry((cos(0 * D2R) * 25) + 20, (sin(0 * D2R) * 25) - 10, knifeAng) + ypos);
	glEnd();

	fx = rx((cos(0 * D2R) * 25) + 30, (sin(0 * D2R) * 25), knifeAng) + xpos;
	fy = ry((cos(0 * D2R) * 25) + 30, (sin(0 * D2R) * 25), knifeAng) + ypos;

}



void knife(knife_t arrow) {


	//display knife
	glColor3f(0.7, 0.7, 0.7);
	glLineWidth(20);
	glBegin(GL_LINES);
	glVertex2f(arrow.x + rx(-20, 0, arrow.fAng), arrow.y + ry(0 - 20, 0, arrow.fAng));
	glVertex2f(arrow.x + rx(0 + 20, 0, arrow.fAng), arrow.y + ry(0 + 20, 0, arrow.fAng));
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(50);
	glBegin(GL_LINES);
	glVertex2f(arrow.x + rx(-25, 0, arrow.fAng), arrow.y + ry(0 - 20, 0, arrow.fAng));
	glVertex2f(arrow.x + rx(-15, 0, arrow.fAng), arrow.y + ry(0 + 20, 0, arrow.fAng));
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(20);
	glBegin(GL_LINES);
	glVertex2f(arrow.x + rx(-20, 0, arrow.fAng), arrow.y + ry(0 - 20, 0, arrow.fAng));
	glVertex2f(arrow.x + rx(0 - 50, 0, arrow.fAng), arrow.y + ry(0 + 20, 0, arrow.fAng));
	glEnd();
	glLineWidth(2);

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_TRIANGLES);
	glVertex2f(arrow.x + rx(0 + 20, 0 + 10, arrow.fAng), arrow.y + ry(0 + 20, 0 + 10, arrow.fAng));
	glVertex2f(arrow.x + rx(0 + 30, 0, arrow.fAng), arrow.y + ry(0 + 30, 0, arrow.fAng));
	glVertex2f(arrow.x + rx(0 + 20, 0 - 10, arrow.fAng), arrow.y + ry(0 + 20, 0 - 10, arrow.fAng));
	glEnd();
}


//disp baloons
void baloon(baloon_t t) {

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(t.x, t.y);
	glVertex2f(t.x, t.y - 60);

	glEnd();


	glColor3f(1.0, 0.0, 1.0);
	circle(t.x, t.y, 25);

	glColor3f(1.0, 1.0, 1.0);
	circle(t.x + 7, t.y + 3, 5);

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(t.x, t.y);
	glVertex2f(t.x + 13, t.y - 35);
	glVertex2f(t.x - 13, t.y - 35);
	glEnd();

}




//reset target and knife
void initBoxes() {
	for (int i = 1; i <= 11; i++) {
		targetArr[i - 1].ang = i * 40;
		targetArr[i - 1].x = targetArr[i - 1].y = 0;
		targetArr[i - 1].a = true;

	}

	for (int i = 0; i < 10; i++) {
		arrArr[i].x = arrArr[i].y = 0;
		arrArr[i].exist = false;
	}

}

void dspBaloons() {
	for (int i = 0; i < 10; i++) {



		targetArr[i].y = (targetArr[i].ang * D2R) * 200 - 100;
		if (targetArr[i].a) {
			baloon(targetArr[i]);



		}
	}


}






// To display onto window using OpenGL commands


void display() {

	// clear window to black

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	dspBackground();
	dspKnife(-390, ypos);


	for (int i = 0; i < 10; i++) {
		if (arrArr[i].exist) {
			knife(arrArr[i]);
		}
	}

	dspBaloons();

	glColor3f(0, 0, 0);

	vprint(150, 20, GLUT_BITMAP_8_BY_13, "Try to hit the baloons!!!");

	vprint(150, -140, GLUT_BITMAP_8_BY_13, "F1 : pause or restart the game");
	vprint(150, -120, GLUT_BITMAP_8_BY_13, "Spacebar : throw the knife");
	vprint(150, -160, GLUT_BITMAP_8_BY_13, "Up and Down : move the knife");

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

	if (key == ' ' && !freeze) {
		arrArr[exArr].x = fx;
		arrArr[exArr].y = fy;
		arrArr[exArr].fAng = knifeAng;
		arrArr[exArr].exist = true;
		exArr = (exArr + 1) % 10;
	}

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
	case GLUT_KEY_UP: up = true; if (!freeze)ypos += 3; break;
	case GLUT_KEY_DOWN: down = true; if (!freeze)ypos -= 3; break;
	case GLUT_KEY_LEFT: left = true; knifeAng++; break;
	case GLUT_KEY_RIGHT: right = true; knifeAng--; break;
	case GLUT_KEY_F1: if (totalHit < 10) freeze = !freeze; else { initBoxes(); totalHit = 0; freeze = false; } break;
	}


	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_UP: up = false;  break;
	case GLUT_KEY_DOWN: down = false;  break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}


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




void hitDetector() {
	for (int i = 0; i < 11; i++) {
		for (int k = 0; k < 10; k++) {
			if (targetArr[i].a && arrArr[k].exist) {
				int a = (targetArr[i].x - arrArr[k].x) * (targetArr[i].x - arrArr[k].x);
				int b = (targetArr[i].y - arrArr[k].y) * (targetArr[i].y - arrArr[k].y);
				if ((a + b) < 400) {
					targetArr[i].a = arrArr[k].exist = false;
					totalHit++;
					if (totalHit >= 11)
						freeze = true;
				}
			}
		}
	}
}






#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);


	if (!freeze) {


		for (int i = 0; i < 10; i++) {
			if (arrArr[i].exist) {
				arrArr[i].x += cos(arrArr[i].fAng * D2R) * 5;
				arrArr[i].y += sin(arrArr[i].fAng * D2R) * 5;
				if (arrArr[i].x > 450)
					arrArr[i].exist = false;
				if (arrArr[i].y > 250 || arrArr[i].y < -250)
					arrArr[i].exist = false;
			}
		}

		for (int i = 0; i < 10; i++) {
			if (targetArr[i].a) {
				targetArr[i].ang = (targetArr[i].ang + 1) % 360;
			}
		}

		hitDetector();


		targetArr[10].x = (sin(circleItr * D2R) * 50) + 300;
		targetArr[10].y = circleItr;

		circleItr += 2;
		if (circleItr > 250)
			circleItr = -250;



	}

	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initBoxes();

}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Defne Ersungur");

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