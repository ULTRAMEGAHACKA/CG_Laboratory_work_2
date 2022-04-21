#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "PipeLine.h"
using namespace std;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLuint VBO1;
GLuint VBO2;
GLuint IBO1;
GLuint IBO2;

GLuint pyramid1VertexArrayObjectId;
GLuint pyramid2VertexArrayObjectId;


glm::vec3 Vertices1[4];
glm::vec3 Vertices2[4];

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    static float Scale2 = 0.0f;
    Scale += 0.05;
    Scale2 += 0.005;
    
    Pipeline p;
    Pipeline p1;

    //p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));//sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)
    p.WorldPos(sinf(Scale2), 0.0f, 10.0f);//sinf(Scale)
    p.Rotate(Scale, Scale ,  Scale );//sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f

    glm::vec3 CameraPos(1.0f, 1.0f, -3.0f);
    glm::vec3 CameraTarget(0.0f, 0.0f, 2.0f);
    glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
    p.SetCamera(CameraPos, CameraTarget, CameraUp);

    p.SetPerspectiveProj(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);
    
    glLoadMatrixf(reinterpret_cast<const float*>(p.GetTrans()));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);

    glColor4f(1.0f, 1.0f, 0.0f, 1.0);
    glDrawElements(GL_LINE_LOOP, 12, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    p1.WorldPos(0.0f/*sinf(Scale2)*/, 0.0f/*sinf(Scale2)*/, 10.0f);//sinf(Scale)
    p1.Rotate(0.0f/*Scale2*/, 0.0f/*Scale2*/, 0.0f/*Scale2*/);//sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f
    glm::vec3 CameraPos1(1.0f, 1.0f, -3.0f);
    glm::vec3 CameraTarget1(0.0f, 0.0f, 2.0f);
    glm::vec3 CameraUp1(0.0f, 1.0f, 0.0f);
    p1.SetCamera(CameraPos1, CameraTarget1, CameraUp1);

    p1.SetPerspectiveProj(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);
    
    glLoadMatrixf(reinterpret_cast<const float*>(p1.GetTrans()));
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);
    
    glColor4f(1.0f, 1.0f, 0.0f, 1.0);
    glDrawElements(GL_LINE_LOOP, 12, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
    glutIdleFunc(RenderSceneCB);
}
static void CreateVertexBuffer()
{
    Vertices1[0] = glm::vec3(-1.0f, -1.0f, 0.5773f);
    Vertices1[1] = glm::vec3(0.0f, -1.0f, -1.15475);
    Vertices1[2] = glm::vec3(0.5f, -1.0f, 0.5773f);
    Vertices1[3] = glm::vec3(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);

    Vertices2[0] = glm::vec3(-1.0f, -1.0f, -0.7f);
    Vertices2[1] = glm::vec3(0.0f, -1.0f, -1.5f);
    Vertices2[2] = glm::vec3(1.0f, -1.0f, -1.0f);
    Vertices2[3] = glm::vec3(0.0f, 1.0f, -0.8f);

    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
}
static void CreateIndexBuffer()
{
    unsigned int Indices[] = {  0, 3, 1,
                                1, 3, 2,
                                2, 3, 0,
                                0, 2, 1 };

    glGenBuffers(1, &IBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    unsigned int Indices2[] = { 0, 3, 1,
                                1, 3, 2,
                                2, 3, 0,
                                0, 2, 1 };

    glGenBuffers(1, &IBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}
int main(int argc, char** argv)
{

    glutInit(&argc, argv); // инициализируем GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //устанавливает начальный режим отображения 

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Window");

    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    
    /*Vertices[0] = glm::vec3(-0.5f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 0.5f, 0.0f);
    Vertices[3] = glm::vec3(0.0f, 1.0f, 0.0f);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);*/

    /*Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.5773f);
    Vertices[1] = glm::vec3(0.0f, -1.0f, -1.15475);
    Vertices[2] = glm::vec3(1.0f, -1.0f, 0.5773f);
    Vertices[3] = glm::vec3(0.0f, 1.0f, 0.0f);*/

    CreateVertexBuffer();
    CreateIndexBuffer();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
    glEnable(GL_BLEND); //enable alpha blending

    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();
}
