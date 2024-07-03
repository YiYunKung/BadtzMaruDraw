#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

// 設定視窗大小
int windowWidth = 500;
int windowHeight = 500;

GLfloat angle = 0.0f; // 初始角度
GLfloat delta = 1.0f; // 每次增加的角度值
GLfloat leftEyeX = -2.5f; // 眼睛x座標
GLfloat rightEyeX = 2.5f;
GLfloat move = 0.02f;   // 眼睛移動
GLfloat size = 1.0;
float posX = 0;
float posY = 0;

void myReshape(int w, int h)    // 維持圖形形狀比例
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   
    if (w <= h)
        glOrtho(-20.0, 20.0, -20.0 * (GLfloat)h / (GLfloat)w,
            20.0 * (GLfloat)h / (GLfloat)w, -20.0, 20.0);
    else
        glOrtho(-20.0 * (GLfloat)w / (GLfloat)h,
            20.0 * (GLfloat)w / (GLfloat)h, -20.0, 20.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void badtzMaru()
{
    GLUquadricObj* quadricPtr;
    quadricPtr = gluNewQuadric();

    gluQuadricDrawStyle(quadricPtr, GLU_FILL);
    gluQuadricNormals(quadricPtr, GLU_NONE);
    gluQuadricTexture(quadricPtr, GLU_FALSE);

    // gluSphere(quadricPtr, 半徑, 多邊形(30), 10)
    // gluPartialDisk(quadricPtr, 內圈半徑, 外圈半徑, 多邊形, 1, 扇形起始角度, 結束角度);

    glLoadIdentity();    // 座標回到初始

    glColor3f(0, 0, 0);
    glTranslatef(0, 6, 0);
    gluSphere(quadricPtr, 8, 30, 10);    // 頭
    glTranslatef(0, -8, 0);
    gluSphere(quadricPtr, 7, 30, 10);    // 身體

    glBegin(GL_POLYGON);    // 頭上的角
        glVertex3f(-3, 15, 0);
        glVertex3f(-1.5, 17.5, 0);
        glVertex3f(0.5, 15, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(-2, 14, 0);
        glVertex3f(-4.5, 17, 0);
        glVertex3f(-5.5, 13, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(3, 15, 0);
        glVertex3f(1.5, 17.5, 0);
        glVertex3f(-0.5, 15, 0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(2, 14, 0);
        glVertex3f(4.5, 17, 0);
        glVertex3f(5.5, 13, 0);
    glEnd();
    
    glColor3f(1, 1, 1);
    glLoadIdentity();    // 座標回到初始
    glTranslatef(0, -6.5, 0);
    gluSphere(quadricPtr, 4.5, 20, 10);    // 身體的白色部分(肚子)

    glLoadIdentity();
    glBegin(GL_POLYGON);    // 眼睛的白色部分
        glVertex3f(0.7, 8.5, -1);
        glVertex3f(5.7, 8.5, -1);
        glVertex3f(5.7, 8.7, -1);
        glVertex3f(0.7, 8.7, -1);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(-0.7, 8.5, -1);
        glVertex3f(-5.7, 8.5, -1);
        glVertex3f(-5.7, 8.7, -1);
        glVertex3f(-0.7, 8.7, -1);
    glEnd();

    glTranslatef(3.2, 8.5, 0);
    gluPartialDisk(quadricPtr, 0, 2.5, 15, 1, -90, -180);   // 眼睛的白色部分
    glTranslatef(-6.4, 0, 0);
    gluPartialDisk(quadricPtr, 0, 2.5, 15, 1, -90, -180);

    
    glColor3f(0, 0, 0);
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(leftEyeX, 8.5, 0);
        gluSphere(quadricPtr, 0.8, 15, 10);  // 眼睛的黑色部分
        glLoadIdentity();
        glTranslatef(rightEyeX, 8.5, 0);
        gluSphere(quadricPtr, 0.8, 15, 10);
    glPopMatrix();

    glLoadIdentity();
    glColor3f(1, 0.9, 0);
    glBegin(GL_POLYGON);    // 嘴巴
        glVertex3f(0, 6, 0);
        glVertex3f(2, 4.5, 0);
        glVertex3f(0, 3.5, 0);
        glVertex3f(-2, 4.5, 0);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex3f(2, 4.5, 0);
        glVertex3f(-2, 4.5, 0);
    glEnd();


    glutSwapBuffers();
    glFlush();
}

void shake()
{
    GLUquadricObj* quadricPtr;
    quadricPtr = gluNewQuadric();
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadricPtr, GLU_FALSE);

    glColor3f(0, 0, 0);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glRotatef(angle, 0.0f, 1.0f, 1.0f);     // 將物件旋轉到指定角度
    glRotatef(270, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    gluCylinder(quadric, 2, 0.3, 6, 15, 20);    // 左手

    glLoadIdentity();
    glTranslatef(5, 0, 0);
    glRotatef(angle, 0.0f, 1.0f, 1.0f);
    glRotatef(90, 0, 1, 0);
    glRotatef(30, 1, 0, 0);
    gluCylinder(quadric, 2, 0.3, 6, 15, 20);    // 右手

    glLoadIdentity();
    glColor3f(1, 0.9, 0);
    glTranslatef(-3.5, -7.2, 0);
    glRotatef(-angle-15, 1.0f, 0.0f, 0.0f);
    glRotatef(270, 0, 1, 0);
    glRotatef(85, 1, 0, 0);
    gluCylinder(quadric, 0.8, 2, 2.5, 15, 20);    // 左腳

    glLoadIdentity();
    glColor3f(1, 0.9, 0);
    glTranslatef(3.5, -7.2, 0);
    glRotatef(15-angle, 1.0f, 0.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glRotatef(85, 1, 0, 0);
    gluCylinder(quadric, 0.8, 2, 2.5, 15, 20);    // 右腳


    gluDeleteQuadric(quadric);
    glPopMatrix();


    glLineWidth(3);
    glBegin(GL_LINES);    // 肚子下的黑線
    glColor3f(0, 0, 0);
    glVertex3f(-4.6, -7.2, 0);
    glVertex3f(4.6, -7.2, 0);
    glEnd();

    glutSwapBuffers();
    glFlush();
}

void update(int value)
{
    angle += delta;
    if (angle > 15.0f || angle < -15.0f) {
        delta = -delta;     // 如果角度超出一定範圍，就改變角度增加的方向
    }

    if (leftEyeX >= -1.8) {
        move = -0.02f;
    }
    else if (leftEyeX <= -3.2){
        move = 0.02f;
    }
    leftEyeX += move;    // 左眼移動
    rightEyeX += move;   // 右眼移動

    glutPostRedisplay();
    glutTimerFunc(25, update, 0); // 設置定時器，以25ms的間隔不斷更新畫面
}

void studentID()
{
    glColor3f(0.5, 0.2, 0.8);
    glLineWidth(3.0);
    glLoadIdentity();
    glTranslatef(-10, -15.5, 0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-5.0, 2.5);
    glVertex2f(-7.5, 2.5);
    glVertex2f(-7.5, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-5.0, 0.0);
    glVertex2f(-5.0, -2.5);
    glVertex2f(-7.5, -2.5);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0, 2.5);
    glVertex2f(0.0, -2.5);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(7.5, 2.5);
    glVertex2f(7.5, -2.5);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(5.0, 2.5);
    glVertex2f(5.0, 0.0);
    glVertex2f(7.5, 0.0);
    glEnd();

    glFlush();
}

// 滑鼠按鍵操作
/*void mouse_callback_func(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = (x - 250) / 12.5;
        y = (250 - y) / 12.5;

        glLoadIdentity();      // 圓心重置
        glTranslatef(x, y, 0);      // 圓心座標平移
        openOpen();

        glutPostRedisplay();    // 重新繪製視窗
    }
}*/

// 鍵盤按鍵操作
/*void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(1);
    if (key == 'w' || key == 'W')
        posY += 0.5;
    else if (key == 's' || key == 'S')
        posY -= 0.5;
    else if (key == 'a' || key == 'A')
        posX -= 0.5;
    else if (key == 'd' || key == 'D')
        posX += 0.5;
    glutPostRedisplay();    // 重新呼叫 mydisplay()
}*/

// 選單
/*void demo_menu(int id)
{
    if (id == 1)  exit(1);
    else if (id == 2) size = 2 * size;
    else size = size / 2;
    glutPostRedisplay();
}*/

void mydisplay()
{
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1.0, 0.0, 0.0);

     badtzMaru();
     studentID();
     shake();


     glFlush();
     glutSwapBuffers();
}

void init()
{          
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();      // 呼叫單位矩陣
     glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);    // 垂直投影法
     //glFrustum(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);  // 俯視投影法，比例會很大！
	 glMatrixMode(GL_MODELVIEW);
     //gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);    // 切換視角
}


void main(int argc, char** argv){
     glutInitWindowSize(windowWidth, windowHeight);
     glutCreateWindow("1102914");
     glutDisplayFunc(mydisplay);
     //glutReshapeFunc(myReshape);

     init();

     //glutIdleFunc(Idle);
     glutReshapeFunc(myReshape);
     glutTimerFunc(25, update, 0); // 設置定時器，以25ms的間隔不斷更新畫面

     //glutMouseFunc(mouse_callback_func);    // Mouse Events
     //glutKeyboardFunc(keyboard);     // Keyboard Events 

     /*glutCreateMenu(demo_menu);
     glutAddMenuEntry("quit", 1);
     glutAddMenuEntry("increase square size", 2);
     glutAddMenuEntry("decrease square size", 3);
     glutAttachMenu(GLUT_RIGHT_BUTTON);     // 滑鼠右鍵 */


     glutMainLoop();
}

