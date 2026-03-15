#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

// Scene controls
float rotationAngle = 0.0f;
float verticalOffset = 0.0f;
float zoom = -15.0f;

bool rotateScene = false;
bool stopped = false;

// Cube positions
float cube1x=-2.5, cube1y=0, cube1z=0;
float cube2x=-1.0, cube2y=1.5, cube2z=-1.5;
float cube3x=1.0, cube3y=-1.5, cube3z=1.5;
float cube4x=2.5, cube4y=0.5, cube4z=-2;

// Velocities
float v1=0.03;
float v2=0.02;
float v3=-0.025;
float v4=-0.035;

const float LEFT_WALL = -4.0;
const float RIGHT_WALL = 4.0;


// ------------------------------------------------
// Original RGB Rainbow Cube
// ------------------------------------------------
namespace Cube {

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
{0,0,0},{0,0,1},{0,1,0},{0,1,1},
{1,0,0},{1,0,1},{1,1,0},{1,1,1}
};

GLint faces[NUM_FACES][4] = {
{1,5,7,3},{5,4,6,7},{4,0,2,6},
{3,7,6,2},{0,1,3,2},{0,4,5,1}
};

GLfloat vertexColors[NUM_VERTICES][3] = {
{0,0,0},{0,0,1},{0,1,0},{0,1,1},
{1,0,0},{1,0,1},{1,1,0},{1,1,1}
};

void draw() {

glBegin(GL_QUADS);

for(int i=0;i<NUM_FACES;i++)
{
for(int j=0;j<4;j++)
{
glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
glVertex3iv((GLint*)&vertices[faces[i][j]]);
}
}

glEnd();
}

}


// ------------------------------------------------
// Draw vertical planes
// ------------------------------------------------
void drawWalls()
{
glDisable(GL_LIGHTING);
glColor3f(0.8,0.8,0.8);

glBegin(GL_QUADS);

// Left wall
glVertex3f(LEFT_WALL,-5,-5);
glVertex3f(LEFT_WALL,5,-5);
glVertex3f(LEFT_WALL,5,5);
glVertex3f(LEFT_WALL,-5,5);

// Right wall
glVertex3f(RIGHT_WALL,-5,-5);
glVertex3f(RIGHT_WALL,5,-5);
glVertex3f(RIGHT_WALL,5,5);
glVertex3f(RIGHT_WALL,-5,5);

glEnd();
}


// ------------------------------------------------
// Display
// ------------------------------------------------
void display()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();

glTranslatef(0, verticalOffset, zoom);

if(rotateScene)
rotationAngle += 0.5;

glRotatef(rotationAngle,0,1,0);

drawWalls();


// ------------------------------------------------
// Rainbow cube (NO LIGHTING so colors stay correct)
// ------------------------------------------------
glDisable(GL_LIGHTING);

glPushMatrix();
glTranslatef(cube1x,cube1y,cube1z);
Cube::draw();
glPopMatrix();


// ------------------------------------------------
// Enable lighting for the other cubes
// ------------------------------------------------
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

GLfloat light_pos[] = {0.0f,4.0f,4.0f,1.0f};
glLightfv(GL_LIGHT0,GL_POSITION,light_pos);


// ------------------------------------------------
// Red cube (dim lighting)
// ------------------------------------------------
GLfloat red_ambient[]  = {0.3f,0.0f,0.0f,1.0f};
GLfloat red_diffuse[]  = {0.6f,0.0f,0.0f,1.0f};
GLfloat red_specular[] = {0.2f,0.2f,0.2f,1.0f};
GLfloat red_shine[]    = {10};

glMaterialfv(GL_FRONT,GL_AMBIENT,red_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,red_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,red_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,red_shine);

glPushMatrix();
glTranslatef(cube2x,cube2y,cube2z);
glutSolidCube(1);
glPopMatrix();


// ------------------------------------------------
// Blue cube (bright + shiny)
// ------------------------------------------------
GLfloat blue_ambient[]  = {0.0f,0.0f,0.4f,1.0f};
GLfloat blue_diffuse[]  = {0.0f,0.0f,1.0f,1.0f};
GLfloat blue_specular[] = {0.8f,0.8f,1.0f,1.0f};
GLfloat blue_shine[]    = {80};

glMaterialfv(GL_FRONT,GL_AMBIENT,blue_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,blue_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,blue_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,blue_shine);

glPushMatrix();
glTranslatef(cube3x,cube3y,cube3z);
glutSolidCube(1);
glPopMatrix();


// ------------------------------------------------
// Yellow cube (very bright)
// ------------------------------------------------
GLfloat yellow_ambient[]  = {0.6f,0.6f,0.0f,1.0f};
GLfloat yellow_diffuse[]  = {1.0f,1.0f,0.0f,1.0f};
GLfloat yellow_specular[] = {1.0f,1.0f,0.5f,1.0f};
GLfloat yellow_shine[]    = {40};

glMaterialfv(GL_FRONT,GL_AMBIENT,yellow_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,yellow_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,yellow_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,yellow_shine);

glPushMatrix();
glTranslatef(cube4x,cube4y,cube4z);
glutSolidCube(1);
glPopMatrix();

glDisable(GL_LIGHTING);

glutSwapBuffers();
}


// ------------------------------------------------
// Cube movement
// ------------------------------------------------
void updateCubes()
{

if(stopped) return;

cube1x += v1;
cube2x += v2;
cube3x += v3;
cube4x += v4;

if(cube1x > RIGHT_WALL-1 || cube1x < LEFT_WALL) v1 *= -1;
if(cube2x > RIGHT_WALL-1 || cube2x < LEFT_WALL) v2 *= -1;
if(cube3x > RIGHT_WALL-1 || cube3x < LEFT_WALL) v3 *= -1;
if(cube4x > RIGHT_WALL-1 || cube4x < LEFT_WALL) v4 *= -1;

}


// ------------------------------------------------
// Timer
// ------------------------------------------------
void timer(int v)
{

updateCubes();

glutPostRedisplay();

glutTimerFunc(1000/60,timer,v);

}


// ------------------------------------------------
// Keyboard
// ------------------------------------------------
void keyboard(unsigned char key,int x,int y)
{

switch(key)
{

case 'r':
rotateScene = !rotateScene;
break;

case 's':
stopped = true;
break;

case 'c':
stopped = false;
break;

case 'u':
verticalOffset += 0.5;
break;

case 'd':
verticalOffset -= 0.5;
break;

case '+':
zoom += 1;
break;

case '-':
zoom -= 1;
break;

}

glutPostRedisplay();

}


// ------------------------------------------------
// Reshape
// ------------------------------------------------
void reshape(int w,int h)
{

glViewport(0,0,w,h);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

gluPerspective(60,(float)w/h,0.5,40);

glMatrixMode(GL_MODELVIEW);

}


// ------------------------------------------------
// Init
// ------------------------------------------------
void init()
{

glEnable(GL_DEPTH_TEST);

glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);

GLfloat light_ambient[] = {0.2f,0.2f,0.2f,1.0f};
GLfloat light_diffuse[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat light_specular[] = {1.0f,1.0f,1.0f,1.0f};

glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

}


// ------------------------------------------------
// Main
// ------------------------------------------------
int main(int argc,char** argv)
{

glutInit(&argc,argv);

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

glutInitWindowSize(600,600);

glutCreateWindow("RGB Cube Flyby");

glutDisplayFunc(display);

glutReshapeFunc(reshape);

glutKeyboardFunc(keyboard);

glutTimerFunc(100,timer,0);

init();

glutMainLoop();

}