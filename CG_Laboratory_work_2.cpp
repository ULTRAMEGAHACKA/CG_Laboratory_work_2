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

GLuint VBO;
GLuint IBO;
glm::vec3 Vertices[4];

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.003;
    
    Pipeline p;
    //p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));//sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)
    p.WorldPos(sinf(Scale), 0.0f, 10.0f);
    p.Rotate(sinf(Scale) * 90, sinf(Scale) * 90, sinf(Scale) * 90);//sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f
    p.SetPerspectiveProj(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);

    glLoadMatrixf(reinterpret_cast<const float*>(p.GetTrans()));

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0);
    //glDrawArrays(GL_LINE_LOOP, 0, 3); // GL_TRIANGLES // GL_LINE_LOOP // GL_LINE_STRIP
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
    glutIdleFunc(RenderSceneCB);
}
static void CreateVertexBuffer()
{
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.5773f);
    Vertices[1] = glm::vec3(0.0f, -1.0f, -1.15475);
    Vertices[2] = glm::vec3(1.0f, -1.0f, 0.5773f);
    Vertices[3] = glm::vec3(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}
static void CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 2, 1 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
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
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    CreateVertexBuffer();
    CreateIndexBuffer();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
    glEnable(GL_BLEND); //enable alpha blending

    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();
}
