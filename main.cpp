#include"include/Header.h"
#include"include/Model.h"
#include"include/camera.h"
#define WIDTH 1280
#define HEIGHT 720
#define INTERVAL 15

GLuint texture;
int rotateX=-10, rotateY=0;
int moveX=0,moveY=0,moveZ=0;
using namespace std;


Model CCrji;

void display();
void reshape(int,int);
void timer(int);
void init(){
    glEnable(GL_LIGHTING);//light source included
    glEnable(GL_LIGHT0);
    GLfloat light_pos[]={14.685,1.9495,24.678,1};//coordinates of light sources
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);

    CCrji.load("../../Models/RACmodel1.obj");//loading the model i.e. '.obj' files

}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH |GLUT_MULTISAMPLE);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV,GL_NICEST);
    //glutSetOption(GLUT_MULTISAMPLE,8);
    int POS_X=(glutGet(GLUT_SCREEN_WIDTH)-WIDTH)>>1;//getting window position
    int POS_Y=(glutGet(GLUT_SCREEN_HEIGHT)-HEIGHT)>>1;
    glutInitWindowPosition(POS_X,POS_Y);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("3D Simulation of RAC Building Thapathali Campus ");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeyFunction);
    glutKeyboardFunc(keyFunction);//keyboard click function
    glutMouseFunc(trackballMouseFunction);//Mouse motion function
    glutTimerFunc(0,timer,0);//timer callback to be trigerred in specific time
    init();
    glutMainLoop();

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(moveX,moveY,moveZ);
    glRotatef(rotateX,rotateY,-200,0);
    CCrji.draw();
    glutSwapBuffers();
}


void reshape(int w,int h){

    const float ar = (float) w / (float) h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1,1, 2, 500);
    glMatrixMode(GL_MODELVIEW);

}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(5000,timer,0);
}


void specialKeyFunction(int key, int x, int y) {
        // Change rotation amounts in response to arrow and home keys.
    if ( key == GLUT_KEY_LEFT )
       moveX += 1;
    else if ( key == GLUT_KEY_RIGHT )
       moveX -= 1;
    else if ( key == GLUT_KEY_DOWN)
       moveZ -= 1;
    else if ( key == GLUT_KEY_UP )
       moveZ += 1;

    glutPostRedisplay();
}

void keyFunction(unsigned char key,int x,int y){
//using special keys 'u' for up and 'd' for down for moving along Y-axis
    if( key== 'D'|| key=='d' )
        moveY+=1;
    else if(key== 'U'|| key=='u')
        moveY-=1;

    glutPostRedisplay();

}

void trackballMouseFunction(int button, int buttonState, int x, int y) {
if(button==GLUT_LEFT_BUTTON)
{
    if (buttonState==GLUT_UP)
    {
if(x<750){
       rotateX+=20;
}
else
{
    rotateX-=20;
}
    }
glutPostRedisplay();
}

}


