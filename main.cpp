#include"include/Header.h"
#include"include/Model.h"
#include"include/camera.h"
#define WIDTH 1280
#define HEIGHT 720
#define INTERVAL 15
//#include "../Library/MicrosoftTeams-image (30).png"
//#include "../Library/MicrosoftTeams-image (32).png"
//#include "../Library/MicrosoftTeams-image (28).png"


using namespace std;

   int rotateX=-10, rotateY=0;

int moveX=0,moveY=0,moveZ=0;


Model CCrji;

void display();
void reshape(int,int);
void timer(int);
void specialKeyFunction(int, int ,int);
void keyFunction(unsigned char,int,int);
void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[]={-1,10,100,1};
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    float white[4]={1,1,1,1};
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);

    CCrji.load("../../Models/RACmodel1.obj");

}

int main(int argc,char**argv){


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH |GLUT_MULTISAMPLE);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV,GL_NICEST);
    //glutSetOption(GLUT_MULTISAMPLE,8);
    int POS_X=(glutGet(GLUT_SCREEN_WIDTH)-WIDTH)>>1;
    int POS_Y=(glutGet(GLUT_SCREEN_HEIGHT)-HEIGHT)>>1;


    glutInitWindowPosition(POS_X,POS_Y);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Animation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeyFunction);
    glutKeyboardFunc(keyFunction);
    //glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    glutTimerFunc(0,timer,0);
    init();

    glutMainLoop();

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glViewport(0,60,WIDTH,HEIGHT-60);
     //cameraLookAt(-500,-500,-500, 1000,1000,1000,0,0,1);
    //cameraSetLimits(-5,5,-5,5,-10,-10);
    glLoadIdentity();

    //glTranslatef(-5,-5.5,-5);
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
    //gluPerspective()
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

    if( key== 'D'|| key=='d' )
        moveY+=1;
    else if(key== 'U'|| key=='u')
        moveY-=1;

    glutPostRedisplay();

}


