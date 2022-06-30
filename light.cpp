#include <stdlib.h>
#include<stdio.h>
#include <stdarg.h>
#include <stdio.h>
#include <GL/glut.h>

#define TORUS 0
#define TEAPOT 1
#define DOD 2
#define TET 3
#define ISO 4
#define QUIT 5
#define PAGE 6

static int spin = 0;
static int obj = PAGE;
static int begin;

void *currentfont;
void setFont(void *font)
{
 currentfont=font;                      // Set the currentfont to the font
}
void drawstring(float x,float y,float z,char *string)
{
 char *c;
 glRasterPos3f(80, 2800,0);
 for(c=string;*c!='\0';c++)
 { glColor3f(1.0,1.0,1.0);
  glutBitmapCharacter(currentfont,*c);
 }
}

void
output(GLfloat x, GLfloat y, char *format,...)
{
  va_list args;
  char buffer[200], *p;

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  glPushMatrix();
  glTranslatef(x, y, 0);
  for (p = buffer; *p; p++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
  glPopMatrix();
}


void
menu_select(int item)
{
  if (item == QUIT)
    exit(0);
  obj = item;
  glutPostRedisplay();
}


void
movelight(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    begin = x;
  }
}


void
motion(int x, int y)
{
  spin = (spin + (x - begin)) % 360;
  begin = x;
  glutPostRedisplay();
}

void
myinit(void)
{
glutInitWindowSize(640,480);
glutInitWindowPosition(1000,200);
glutCreateWindow("OBJECTS AND LIGHT");
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
}

void
display(void)
{

	  output(80, 2800, "Welcome ");
          output(80, 2650, "Right mouse button for menu.");
          output(80, 400, "Hold down the left mouse button");
          output(80, 250, "and move the mouse horizontally");
          output(80, 100, "to change the light position.");
          printf("WELCOME");
	glPopMatrix();
	glFlush();	
  glClearColor(0.0,0.0,0.0,0.0);
  glFlush();
  glClear(GL_COLOR_BUFFER_BIT);
  GLfloat position[] =
  {0.0, 0.0, 1.5, 1.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(0.0, 0.0, -5.0);

  glPushMatrix();
  glRotated((GLdouble) spin, 0.0, 1.0, 0.0);
  glRotated(0.0, 1.0, 0.0, 0.0);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glTranslated(0.0, 0.0, 1.5);
  glDisable(GL_LIGHTING);
  glColor3f(0.0, 1.0, 1.0);
  glutWireCube(0.1);
  glEnable(GL_LIGHTING);
  glPopMatrix();

  switch (obj) {
    case PAGE:
         glColor3f(1.0,0.0,1.0);
	 drawstring(150.0,455.0,1.0,"* * * * * * * * * * THE DRAWSTRING FUNCTION DEMO * * * * * * * * * *");
	  output(80, 2800, "Welcome to OBJECTS AND LIGHT");
          output(80, 2650, "Right mouse button for menu.");
          output(80, 400, "Hold down the left mouse button");
          output(80, 250, "and move the mouse horizontally");
          output(80, 100, "to change the light position.");
          printf("pp");
	glPopMatrix();
	glFlush();	

	break;
    case TORUS:
    output(80, 2800, "Welcome to OBJECTS AND LIGHT");
    glutSolidTorus(0.275, 0.85, 20, 20);
    break;
  case TEAPOT:
    glutSolidTeapot(1.0);
    break;
  case DOD:
    glPushMatrix();
    glScalef(.5, .5, .5);
    glutSolidDodecahedron();
    glPopMatrix();
    break;
  case TET:
    glutSolidTetrahedron();
    break;
  case ISO:
    glutSolidIcosahedron();
    break;
  }

  glPopMatrix();
  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 3000, 0, 3000);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
  glutSwapBuffers();
}

void
myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void
tmotion(int x, int y)
{
  printf("Tablet motion x = %d, y = %d\n", x, y);
}

void
tbutton(int b, int s, int x, int y)
{
  printf("b = %d, s = %d, x = %d, y = %d\n", b, s, x, y);
}

void
smotion(int x, int y, int z)
{
  fprintf(stderr, "Spaceball motion %d %d %d\n", x, y, z);
}

void
rmotion(int x, int y, int z)
{
  fprintf(stderr, "Spaceball rotate %d %d %d\n", x, y, z);
}

void
sbutton(int button, int state)
{
  fprintf(stderr, "Spaceball button %d is %s\n",
    button, state == GLUT_UP ? "up" : "down");
}

void
dials(int dial, int value)
{
  fprintf(stderr, "Dial %d is %d\n", dial, value);
  spin = value % 360;
  glutPostRedisplay();
}

void
buttons(int button, int state)
{
  fprintf(stderr, "Button %d is %s\n", button,
    state == GLUT_UP ? "up" : "down");
}


int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow(argv[0]);
  myinit();
  glutMouseFunc(movelight);
  glutMotionFunc(motion);
  glutReshapeFunc(myReshape);
  glutDisplayFunc(display);
  glutTabletMotionFunc(tmotion);
  glutTabletButtonFunc(tbutton);
  glutSpaceballMotionFunc(smotion);
  glutSpaceballRotateFunc(rmotion);
  glutSpaceballButtonFunc(sbutton);
  glutDialsFunc(dials);
  glutButtonBoxFunc(buttons);
  glutCreateMenu(menu_select);
  glutAddMenuEntry("PAGE", PAGE);
  glutAddMenuEntry("Torus", TORUS);
  glutAddMenuEntry("Teapot", TEAPOT);
  glutAddMenuEntry("Dodecahedron", DOD);
  glutAddMenuEntry("Tetrahedron", TET);
  glutAddMenuEntry("Icosahedron", ISO);
  glutAddMenuEntry("Quit", QUIT);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;          
}
