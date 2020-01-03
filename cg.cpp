#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<glut.h>

using namespace std;

//function prototypes
void enqueue(char key);
void dequeue();
void draw_rectangle();
void queue();
void welcome();
void drawString(float x, float y, float z, void *font, char *string);
void display1();
void display();
void display_back();
void mouse_callback_function(int button, int state, int ax, int ay);
void keyboard_callback_function(unsigned char key, int a, int b);
void Reshape_callback_function(int w, int h);
void myinit();
void stack();
void displaying_stack();
void bg_color();
void simple_queue();
void displaying_simple_queue();

int keyboard_callback = 0;
/*
In this program we use only one keyboard callback function
so we use a flag called keyboard callback to identify between various functions which
will call the keyboard callback function

to determine size of stack flag = 1
to either push or pop from stack flag = 2

*/
int key1 = 3;//key1 is set to 3 to display initial window
int SCREENH = 450, SCREENW = 450;//screen size
int mouseval = 1;//flag for mouse callback
int stk_size,que_size;
int stk_top = -1;
int sx1, sx2, sx3, sx4, sy1, sy2, sy3, sy4; // used to draw stack
int stk_top_ptr_pos;
int stk_push_pos;

int que_frnt, que_rear;
int que_front_ptr_pos, que_rear_ptr_pos;
int que_front_elem_ptr_pos, que_rear_elem_ptr_pos;

int draw_rect;

bool down = false;//to check whether key is pressed by mouse

char stk[] = "Stack", que[] = "Queue", ext[] = "EXIT", sk[] = "STACK", di_qu[] = "QUEUE";
char stck[] = "Enter the size of the stack ";
char stck1[] = "NOTE: Maximum stack size is 9";
char simple_q[] = "Enter the size of the Queue ";
char simple_q1[] = "NOTE: Maximum Queue size is 9";
char top_pointer[] = "top->";
char back[] = "BACK";
char front[] = "f"; 
char rear[] = "r";

void display_back() {
	switch (key1)
	{
	case 8:
		welcome();
		break;
	case 9:
		stack();
		break;
	case 10:
		queue();
		break;
	}
	glFlush(); // Render now
	glutSwapBuffers(); //Swap front- and back framebuffer
}

void display1() {
	switch (key1)
	{
	case 5:
		simple_queue();
		break;
	/*case 6:
		cout << "\ncircular Queue ";
		break;
	case 7:
		cout << " \nPriority queue ";
		break;*/
	}
	glFlush(); // Render now
	glutSwapBuffers(); //Swap front- and back framebuffer
}

void simple_queue() {
	bg_color();

	keyboard_callback = 3;
	mouseval = 2;
	bg_color();
	glColor3f(0, 0, 0);
	drawString(25, 60, 0, GLUT_BITMAP_HELVETICA_18, simple_q);

	glColor3f(0, 0, 0);
	drawString(20, 25, 0, GLUT_BITMAP_HELVETICA_18, simple_q1);

	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 4.5, 60.5, 10.5);

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 5, 60, 10);
	glColor3f(0.137, 0.137, 0.556);
	drawString(44, 6, 0, GLUT_BITMAP_HELVETICA_18, back);

	glFlush();
}

void frntpge() {
	mouseval = -30;
	char by[] = "by", title[]="IMPLEMENTATION OF DS",ta[]="Tharif Ansari A           1RN16CS115";
	char sabu[] = "Shaista Saba             1RN16CS092",prcd[]="PROCEED";
	bg_color();
	glColor3f(.6, 0, 0);
	drawString(23, 80, 0, GLUT_BITMAP_HELVETICA_18, title);
	drawString(47, 75, 0, GLUT_BITMAP_HELVETICA_18, by);
	glColor3f(0,0,0);
	drawString(20, 50, 0, GLUT_BITMAP_HELVETICA_18, sabu);
	drawString(20, 40, 0, GLUT_BITMAP_HELVETICA_18, ta);

	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 19.5, 65.5, 25.5);

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 20, 65, 25);
	glColor3f(0.137, 0.137, 0.556);
	drawString(43, 21.5, 0, GLUT_BITMAP_HELVETICA_18, prcd);
	glFlush();
}

void display() {
	if (mouseval == 1) {
		switch (key1)
		{
		case 1: 
		{
			stack();
			break; 
		}
		case 2:
		{
			mouseval = 2;
			queue();
			break; 
		}

		//
		case 3:
		{
			frntpge();
			break; 
		}
		case 70: {	
					welcome();
					break; 
		}
		case 4: {
			exit(0);
		}
		}
	}
	glFlush(); // Render now
	glutSwapBuffers(); //Swap front- and back framebuffer
}

void mouse_callback_function(int button, int state, int ax, int ay)            // takes input from mouse
{
	int mx = ax * 100 / SCREENW, my = (SCREENH - ay) * 100 / SCREENH;		// m = mouse cordinate to graphics

	down = button == GLUT_LEFT_BUTTON && state == GLUT_LEFT;
	if (down && mouseval== -30) {
		if (mx > 39.7 && mx < 65.3 && my > 20 && my < 25) {
			glClear(GL_COLOR_BUFFER_BIT);
			mouseval = 1;
			key1 = 70;
			display();
		}
	}
	else
		if (down && mouseval == 1)
	{
		if (mx > (39.7) && mx < (60.3) && my >(40) && my < (45)) //Stack
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 1;
			display();
		}
		if (mx > (39.7) && mx < (60.3) && my >(30) && my < (35)) //Queue
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 2;
			display();
		}
		if (mx > (39.7) && mx < (60.3) && my >(20) && my < (25)) //exit
		{
			//
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 4;
			display();
		}
	}
	else if (down && mouseval == 2)
	{
		//cout << "\ninside else if of mouse1";
		if (mx > (19.7) && mx < (80.3) && my >(40) && my < (45)) //Stack
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 5;
			display1();
		}
		if (mx > (19.7) && mx < (80.3) && my >(30) && my < (35)) //Queue
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 6;
			display1();
		}
		if (mx > (19.7) && mx < (80.3) && my >(20) && my < (25)) //exit
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 7;
			display1();
		}
		if (mx > (39.7) && mx < (60.3) && my >(5) && my < (10)) //stack to home
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 8;
			display_back();
		}
	}
	else if( (down && mouseval == 3) || (down && mouseval == 4))
	{
		if (mx > (39.7) && mx < (60.3) && my >(5) && my < (10) && mouseval == 3) //stack to home
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 8;
			display_back();
		}
		else if (mx > (69.7) && mx < (90.3) && my >(5) && my < (10) && mouseval == 4) //to stack size
		{
			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 9;
			display_back();
		}
	}
	else if (down && mouseval == 5) {
		glClear(GL_COLOR_BUFFER_BIT);
		key1 = 10;
		display_back();
	}
	glutMouseFunc(mouse_callback_function); // Register callback handler for mouse event
}

void displaying_stack() {
	bg_color();
	glColor3f(0, 0, 0);
	drawString(45, 95, 0, GLUT_BITMAP_HELVETICA_18, sk);//user definded function to write inisde the box

	keyboard_callback = 2;
	stk_top = -1;
	mouseval = 4;
	draw_rect = 1;

	glColor3f(0.8, 0.8, 0.8);
	glRectf(70, 5, 90, 10);
	glColor3f(0.137, 0.137, 0.556);
	drawString(74, 6, 0, GLUT_BITMAP_HELVETICA_18, back);


	if (stk_size < 5) {
		glColor3f(0, 0, 0);
		stk_push_pos = 22;
		stk_top_ptr_pos = 22;
		sx1 = 40;
		sy1 = 20;
		sx2 = 60;
		sy2 = 20;
		sx3 = 40;
		sy3 = 30;
		sx4 = 60;
		sy4 = 30;
		for (int z = 0; z < stk_size; z++)
			draw_rectangle();
	}
	else {

		glColor3f(0, 0, 0);
		stk_push_pos = 3;
		stk_top_ptr_pos = 3;
		sx1 = 40;
		sy1 = 1;
		sx2 = 60;
		sy2 = 1;
		sx3 = 40;
		sy3 = 11;
		sx4 = 60;
		sy4 = 11;
		for (int z = 0; z < stk_size; z++)
			draw_rectangle();
	}
	glFlush();
}

void displaying_simple_queue() {
	que_front_elem_ptr_pos = 32;
	que_rear_elem_ptr_pos = 0;
	bg_color();
	glColor3f(0, 0, 0);
	drawString(45, 95, 0, GLUT_BITMAP_HELVETICA_18, di_qu);//user definded function to write inisde the box
	
	que_frnt = -1;
	que_rear = -1;

	keyboard_callback = 4;
	draw_rect = 2;
	mouseval = 5;

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 15, 60, 20);
	glColor3f(0.137, 0.137, 0.556);
	drawString(44, 16.5, 0, GLUT_BITMAP_HELVETICA_18, back);

	if (que_size < 5) {
		glColor3f(0, 0, 0);
		que_front_elem_ptr_pos = 32;
		que_front_ptr_pos = 32;
		sx1 = 30;
		sy1 = 50;
		sx2 = 40;
		sy2 = 50;
		sx4 = 40;
		sy4 = 60;
		sx3 = 30;
		sy3 = 60;
		for (int z = 0; z < que_size; z++)
			draw_rectangle();
	}
	else {
		glColor3f(0, 0, 0);
		que_front_elem_ptr_pos = 8;
		que_front_ptr_pos = 8;
		sx1 = 5;
		sy1 = 50;
		sx2 = 15;
		sy2 = 50;
		sx3 = 5;
		sy3 = 60;
		sx4 = 15;
		sy4 = 60;
		for (int z = 0; z < que_size; z++)
			draw_rectangle();
	}
	glFlush();
}

void welcome() {
	mouseval = 1;
	bg_color();
	// button 1 .. Stack
	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 39.5 , 60.5, 45.5 );//draw a rectangle+10

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 40 , 60, 45);
	glColor3f(0.137, 0.137, 0.556);
	drawString(45, 41 , 0, GLUT_BITMAP_HELVETICA_18, stk);//user definded function to write inisde the box

	// button 2 .. Queue
	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 29.5 , 60.5, 35.5 );

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 30 , 60, 35 );
	glColor3f(0.137, 0.137, 0.556);
	drawString(45, 31 , 0, GLUT_BITMAP_HELVETICA_18, que);

	// button 3 .. EXIT
	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 19.5 , 60.5, 25.5 );

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 20 , 60, 25 );
	glColor3f(0.137, 0.137, 0.556);
	drawString(46, 21.5 , 0, GLUT_BITMAP_HELVETICA_18, ext);

	glFlush();
	glPushMatrix(); // Save model-view matrix setting
	glPopMatrix();
}

void stack() {

	keyboard_callback = 1;
	bg_color();
	glColor3f(0, 0, 0);
	drawString(25, 60, 0, GLUT_BITMAP_HELVETICA_18, stck);

	glColor3f(0, 0, 0);
	drawString(20, 25, 0, GLUT_BITMAP_HELVETICA_18, stck1);

	glColor3f(0.196, 0.196, 0.8);
	glRectf(39.5, 4.5, 60.5, 10.5);

	mouseval = 3;

	glColor3f(0.8, 0.8, 0.8);
	glRectf(40, 5, 60, 10);
	glColor3f(0.137, 0.137, 0.556);
	drawString(44, 6, 0, GLUT_BITMAP_HELVETICA_18, back);
}

void queue() {
	simple_queue();
}
void push(char key) {
	char *key_ptr = &key;
	if (stk_top < stk_size - 1) {
		cout << "\nPushing '"<<key<<"'" ;
		glColor3f(0.3, 0.56, 0.84);
		glRectf(19, 0, 39, 100);
		glColor3f(0, 0, 0);
		stk_top += 1;
		drawString(50, stk_push_pos, 0, GLUT_BITMAP_HELVETICA_18, key_ptr);
		drawString(20, stk_top_ptr_pos, 0, GLUT_BITMAP_HELVETICA_18, top_pointer);
		stk_push_pos += 10;
		stk_top_ptr_pos += 10;
	}
	else
		cout << "\nStack is full";
	glFlush();
}
void pop() {
	if (stk_top > -1) {
		cout << "\nPopping from stack";
		stk_top -= 1;
		stk_top_ptr_pos -= 10;
		stk_push_pos -= 10;//funny
		glColor3f(0.3, 0.56, 0.84);
		glRectf(19, 0, 39, 90);
		glColor3f(0, 0, 0);//
		drawString(20, stk_top_ptr_pos - 10, 0, GLUT_BITMAP_HELVETICA_18, top_pointer);
		glColor3f(0.3, 0.56, 0.84);
		glRectf(41, stk_top_ptr_pos - 1, 59, stk_top_ptr_pos + 4);
	}
	else
		cout << "\nStack is Empty";
	glFlush();
}

void keyboard_callback_function(unsigned char key, int a, int b) {
	if (keyboard_callback == 1 && key != '0' && isdigit(key) != 0) {
		stk_size = int(key) - 48;
		cout << "\nSTACK\n---------------------------------------------------\n";
		cout << "\nThe Stack size entered is " << stk_size; // << " " << key;
		displaying_stack();
	}
	else if (keyboard_callback == 2) {
		if (isalnum(key)) {
			push(key);
		}
		else
			if (key == '-') {
				pop();
			}
			else {
				cout << "\nInvalid entry";
			}
	}
	else if (keyboard_callback == 3 && key != '0' && isdigit(key) != 0) {
		que_size = int(key) - 48;
		cout << "\nQUEUE\n-----------------------------------------------\n";
		cout << "\n\nThe Queue size entered is " << que_size; // << " " << key;
		displaying_simple_queue();
	}
	else if (keyboard_callback == 4) {
		if (isalnum(key)) {
			enqueue(key);
		}
		else
			if (key == '-') {
				dequeue();
			}
			else {
				cout << "\nInvalid entry";
			}
	}
}
void enqueue(char key) {
	char *key_ptr = &key;

	if (que_rear == que_size - 1) {
		cout << "\nQueue Overflow";
	}
	else {
		if (que_frnt == -1) { 
			que_frnt = 0; 
			glColor3f(0.3, 0.56, 0.84);
			glRectf(1, 39, 80, 49);
			glColor3f(0, 0, 0);
			drawString(que_front_ptr_pos , 46, 0, GLUT_BITMAP_HELVETICA_18, front);
		}
		cout << "\nEnqueueing '" << key << "' to Queue";
		glColor3f(0.3, 0.56, 0.84);
		glRectf(1, 61, 80, 70);
		glColor3f(0, 0, 0);
		drawString(que_front_elem_ptr_pos,64 , 0, GLUT_BITMAP_HELVETICA_18, rear);
		drawString(que_front_elem_ptr_pos, 54, 0, GLUT_BITMAP_HELVETICA_18, key_ptr);
		que_front_elem_ptr_pos += 10;
		que_rear++;
	}
	glFlush();
}

void dequeue() {
	if (que_frnt == -1 || que_frnt > que_rear) {
		cout << "\nUnderflow";
	}
	else {
		cout << "\nDequeing ";
		que_frnt++;
		glColor3f(0.3, 0.56, 0.84);
		glRectf(1, 39, 95, 49);
		glColor3f(0, 0, 0);
		drawString(que_front_ptr_pos+10, 46, 0, GLUT_BITMAP_HELVETICA_18, front);//
		glColor3f(0.3, 0.56, 0.84);
		glRectf(que_front_ptr_pos-1,51,que_front_ptr_pos+7 , 59);
		que_front_ptr_pos += 10;
		glColor3f(0, 0, 0);
	}
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);// Set display mode.
	glutInitWindowPosition(100, 100);			// Set top-left display-window position.
	glutInitWindowSize(SCREENH, SCREENW);				// Set display-window width and height.
	glutCreateWindow("DS_Implementation");// Create display window.
	myinit();									// Execute initialization procedure.
	//glutTimerFunc(400, timer, 0);     // First timer call immediately
	glutReshapeFunc(Reshape_callback_function);       // Register callback handler for window re-size event
	glutKeyboardFunc(keyboard_callback_function);   // Register callback handler for special-key event
	glutMouseFunc(mouse_callback_function);   // Register callback handler for mouse event
	glutDisplayFunc(display);				//Invokes a function to create a picture within the current display window.
	glutMainLoop();                   //Executes the computer-graphics program.
	return 0;
}

//after main function

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void Reshape_callback_function(int w, int h)
{
	glViewport(0, 0, w, h); // Set the viewport to cover the new window
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
	glLoadIdentity(); // Reset the model-view matrix
	if (key1 == 3) {
		glOrtho(0.0, 100.0, 0.0, 100.0, -5.0, 10.0);
	}
}

void drawString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z); //Specifies the raster position for pixel operations.
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c); //renders a bitmap character using OpenGL
	}
}

void bg_color() {
	glMatrixMode(GL_PROJECTION);
	glColor3f(0.3, 0.56, 0.84);   //background color
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.3, 0.56, 0.84);
	//glColor3f(0.137, 0.137, 0.556);
	glVertex3f(100.0, 0.0, 0.0);
	glColor3f(0.3, 0.56, 0.84);
	//glColor3f(0.196, 0.196, 0.8);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
	glFlush();
}

void draw_rectangle() {
	if (draw_rect == 1) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(sx1, sy1);
		glVertex2f(sx2, sy2);
		glVertex2f(sx4, sy4);
		glVertex2f(sx3, sy3);
		glEnd();
		sy1 += 10;
		sy2 += 10;
		sy3 += 10;
		sy4 += 10;
	}
	else if (draw_rect == 2) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(sx1, sy1);
		glVertex2f(sx2, sy2);
		glVertex2f(sx4, sy4);
		glVertex2f(sx3, sy3);
		glEnd();
		sx1 += 10;
		sx2 += 10;
		sx3 += 10;
		sx4 += 10;
	}
}