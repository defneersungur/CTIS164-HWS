/*
CTIS164 - HOMEWORK 1
DEFNE ERSUNGUR
22003296
SECTION 001
Interactivity: Animating Shapes

I tried make a farmer who wants to collect his rice. So we can click to pick rice and we can make rain drops.




*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 400

#define TIMER_PERIOD 16   //period for the timer
#define TIMER_ON      1   //0:disable timer, 1:enable timer

#define D2R 0.0174532

//shapes

#define RAIN  1
#define RICE   2

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; //current Window width and height

						  // global variables
bool activeTimer = true;

int mode = RICE; // initial shape is RICE
int r = 0;  // initial number of rice

char shapes[3][20] = { " ", "RAIN", "REISE" };



//TRIANGLE
int xT = 50, yT = 130; //triangle's initial position
int heightT = 20; //triangle's initial height

				   //REISE'S
int xB = 0, yB = -55; //REISE's initial position
int radiusB = 75; //REISE's initial radius

				  /*
				  to draw circle, center at (x,y) radius r
				  DAIRE
				  */
void circle(int x, int y, int r) {
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}




/*
to display text with variables

*/
void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}





void drawRain() {
	glBegin(GL_TRIANGLES);

	glVertex2f(xT - heightT, yT - heightT / 2);
	glVertex2f(xT + heightT, yT - heightT / 2);
	glVertex2f(xT, yT + heightT / 2);

	circle(xT - heightT + 20, yT - 5 - heightT / 2, 15);
	circle(xT - heightT + 20, yT - 5 - heightT / 2, 16);



	vprint(35, 100, GLUT_BITMAP_8_BY_13, " ");



	glEnd();
}

void drawRice() {

	glColor3f(0.9, 0.9, 0.9);
	circle(xB + (radiusB / 10), yB + (radiusB / 10), (radiusB / 10));
}


/*
to display onto window using OpenGL commands
*/
void display() {
	//clear window to green 
	glClearColor(0, 0.5, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//sky
	glColor3f(0, 0.6, 0.6);
	glRectf(-5500, 2000, 5000, -50);

	//sun
	glColor3f(1, 0.5, 0);
	circle(-260, 150, -50);

	//clouds
	glColor3f(0, 0.8, 1);
	circle(-160, 150, -30);
	glColor3f(0, 0.8, 1);
	circle(-120, 160, -30);
	glColor3f(0, 0.8, 1);
	circle(-140, 140, -30);
	glColor3f(0, 0.8, 1);
	circle(-100, 140, -30);

	glColor3f(0, 0.8, 1);
	circle(50, 70, -30);
	glColor3f(0, 0.8, 1);
	circle(90, 70, -30);
	glColor3f(0, 0.8, 1);
	circle(70, 50, -30);
	glColor3f(0, 0.8, 1);
	circle(110, 50, -30);

	glColor3f(0, 0.8, 1);
	circle(190, 110, -30);
	glColor3f(0, 0.8, 1);
	circle(230, 110, -30);
	glColor3f(0, 0.8, 1);
	circle(210, 90, -30);
	glColor3f(0, 0.8, 1);
	circle(250, 90, -30);

	glColor3f(0, 0.8, 1);
	circle(-300, 120, -30);
	glColor3f(0, 0.8, 1);
	circle(-270, 130, -30);
	glColor3f(0, 0.8, 1);
	circle(-290, 110, -30);
	glColor3f(0, 0.8, 1);
	circle(-250, 110, -30);


	// DRAW A RECTANGLE

	glColor3f(0.9, 0.9, 0.9);
	glRectf(-150, -170, -100, -50);
	glColor3f(1, 0.6, 0.6);
	glRectf(-80, -50, -100, -100);
	glColor3f(1, 0.6, 0.6);
	glRectf(-170, -100, -150, -50);
	glColor3f(1, 0.6, 0.6);
	glRectf(-140, -70, -110, -30);

	//grass
	glColor3f(0, 0.3, 0);
	glRectf(-240, -50, -210, -430);

	glColor3f(0, 0.3, 0);
	glRectf(-25, -50, 5, -430);

	glColor3f(0, 0.3, 0);
	glRectf(215, -50, 245, -430);

	//triangle
	glColor3f(0.5f, 0.35f, 0.05f);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex2f(-125, -10);
	glVertex2f(-155, -40);
	glVertex2f(-95, -40);

	glEnd();



	//draw points

	glColor4f(0, 0, 0, 1);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2f(-130, -50);
	glVertex2f(-115, -50);

	glEnd();


	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	// line 1
	glVertex2f(-130, -60);
	glVertex2f(-120, -60);
	// line 2
	glColor4f(0, 0, 0, 1);
	glVertex2f(-150, -110);
	glVertex2f(-100, -110);
	glColor4f(0, 0, 0, 1);
	glVertex2f(-125, -110);
	glVertex2f(-125, -170);

	glEnd();


	glColor3f(0, 0.4, 0.6);

	switch (mode) {

	case RAIN:
		drawRain();
		break;

	case RICE:
		drawRice();
		break;
	}

	
	glColor3f(1, 1, 0); // white
	vprint(-(winWidth / 2) + 20, -(winHeight / 2) + 40, GLUT_BITMAP_8_BY_13, "the number of rice picked=%d ", r);
	glColor3f(0, 0, 0); //black
	vprint(-(winWidth / 2) + 40, -(winHeight / 2) + 240, GLUT_BITMAP_8_BY_13, "Help him to pick his rices!!! ");



	
	glColor3f(0, 1, 1); // blue
	vprint((winWidth / 2) - 450, -(winHeight / 2) + 80, GLUT_BITMAP_8_BY_13, " <-, -> : change shape to rice or rain drop");
	vprint((winWidth / 2) - 440, -(winHeight / 2) + 50, GLUT_BITMAP_8_BY_13, "left click: change location and increase of rice numbers  ");
	





	glutSwapBuffers();
}





//change reise to rain drop
void onSpecialKeyDown(int key, int x, int y) {


	if (key == GLUT_KEY_LEFT) {
		if (mode == RAIN)
			mode = RICE;
		else
			mode--;
	}

	if (key == GLUT_KEY_RIGHT) {
		if (mode == RICE)
			mode = RAIN;
		else
			mode++;
	}


}




/*
When a click occurs in the window,
It provides which button
buttons :  GLUT_LEFT_BUTTON
states  :  GLUT_DOWN
x, y is the coordinate of the point that mouse clicked
*/
void onClick(int button, int stat, int x, int y) {



	


	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		switch (mode) {


		case RAIN:
			xT = x - winWidth / 2;
			yT = winHeight / 2 - y;
			break;

		case RICE:
			xB = x - winWidth / 2;
			yB = winHeight / 2 - y;
			break;
		}
		r++;

	}



}

/*
This function is called when the window size changes.
w : is the new width of the window in pixels
h : is the new height of the window in pixels
*/
void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}





#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);

	if (activeTimer) {
		// animate the current shape until it touches the edge of the window.
		switch (mode) {


		case RAIN:
			if (-yT + heightT / 2 < winHeight / 2)
				yT--;
			break;

		case RICE:
			if (yB + radiusB < winHeight / 2)
				yB++;
			break;
		}
	}


	glutPostRedisplay(); //display()

}
#endif




void main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("1400x800 Interactivity: Animating Shapes");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);


	glutSpecialFunc(onSpecialKeyDown);



	//mouse registration
	glutMouseFunc(onClick);


#if TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif



	//initialize random generator
	srand(time(0));

	glutMainLoop();

}