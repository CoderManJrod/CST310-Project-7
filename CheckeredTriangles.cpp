// CheckeredTriangles.cpp
//
// Controls:
//   C       - Start/continue spinning
//   P       - Pause/stop spinning
//   U       - Move image up
//   D       - Move image down
//   L       - Move image left
//   R       - Move image right
//   +       - Zoom in
//   -       - Zoom out
//
// Compile:
//   g++ CheckeredTriangles.cpp -o CheckeredTriangles -lGL -lGLU -lglut -std=c++17
// Run:
//   ./CheckeredTriangles

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

// ─── Texture ────
#define red     {0xff, 0x00, 0x00}
#define yellow  {0xff, 0xff, 0x00}
#define magenta {0xff, 0x00, 0xff}

GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// ─── State ────
float angle     = 0.0f;   // current rotation angle
bool  spinning  = true;   // is the image spinning?
float offsetX   = 0.0f;   // horizontal translation
float offsetY   = 0.0f;   // vertical translation
float zoomLevel = 80.0f;  // field of view (smaller = zoomed in)

// ─── Timer ────
// Called every 16ms (~60fps). Advances rotation if spinning is active.
void timer(int) {
    if (spinning) {
        angle += 1.0f;
        if (angle >= 360.0f) angle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ─── Reshape ────
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // zoomLevel controls the FOV — lower value = zoomed in, higher = zoomed out
    gluPerspective(zoomLevel, GLfloat(width) / height, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 3,
                 2, 2,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// ─── Display ────
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Camera
    gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);

    // Apply translation (up/down/left/right)
    glTranslatef(offsetX, offsetY, 0.0f);

    // Apply rotation around Z axis (spin)
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Draw the three textured triangles (original geometry unchanged)
    glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5, 1.0);  glVertex2f(-3,  3);
        glTexCoord2f(0.0, 0.0);  glVertex2f(-3,  0);
        glTexCoord2f(1.0, 0.0);  glVertex2f( 0,  0);

        glTexCoord2f(4,   8);    glVertex2f( 3,  3);
        glTexCoord2f(0.0, 0.0);  glVertex2f( 0,  0);
        glTexCoord2f(8,   0.0);  glVertex2f( 3,  0);

        glTexCoord2f(5,   5);    glVertex2f( 0,  0);
        glTexCoord2f(0.0, 0.0);  glVertex2f(-1.5,-3);
        glTexCoord2f(4,   0.0);  glVertex2f( 1.5,-3);
    glEnd();

    glutSwapBuffers();
}

// ─── Keyboard ───
// Handles all key input. Uses lowercase and uppercase for each control.
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Spin controls
        case 'c': case 'C': spinning = true;  break;  // continue spinning
        case 'p': case 'P': spinning = false; break;  // pause spinning

        // Vertical movement
        case 'u': case 'U': offsetY += 0.3f; break;   // move up
        case 'd': case 'D': offsetY -= 0.3f; break;   // move down

        // Horizontal movement
        case 'l': case 'L': offsetX -= 0.3f; break;   // move left
        case 'r': case 'R': offsetX += 0.3f; break;   // move right

        // Zoom (adjust FOV and re-apply projection)
        case '+':
            zoomLevel -= 5.0f;
            if (zoomLevel < 10.0f) zoomLevel = 10.0f; // clamp min zoom
            {
                int w = glutGet(GLUT_WINDOW_WIDTH);
                int h = glutGet(GLUT_WINDOW_HEIGHT);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(zoomLevel, GLfloat(w) / h, 1, 40);
                glMatrixMode(GL_MODELVIEW);
            }
            break;
        case '-':
            zoomLevel += 5.0f;
            if (zoomLevel > 170.0f) zoomLevel = 170.0f; // clamp max zoom
            {
                int w = glutGet(GLUT_WINDOW_WIDTH);
                int h = glutGet(GLUT_WINDOW_HEIGHT);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(zoomLevel, GLfloat(w) / h, 1, 40);
                glMatrixMode(GL_MODELVIEW);
            }
            break;

        // Escape to quit
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

// ─── Main ────
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffer for smooth animation
    glutInitWindowSize(520, 390);
    glutCreateWindow("Textured Triangles - Part 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}
