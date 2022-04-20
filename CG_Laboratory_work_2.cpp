#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "PipeLine.h"
using namespace std;

GLuint VBO;
double Scale = 0.0;
glm::vec3 Vertices[3];

void RenderSceneCB()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 3); // GL_TRIANGLES // GL_LINE_LOOP // GL_LINE_STRIP
    Scale += 0.003;
    //glDrawArrays(GL_LINE_LOOP, 3, 3);
    
    Pipeline p;
    p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
    p.WorldPos(sinf(Scale), sinf(Scale), 0.0f);
    p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);

    glLoadMatrixf(reinterpret_cast<const float*>(p.GetTrans()));

    glDisableVertexAttribArray(0);
    glutSwapBuffers();
    glutIdleFunc(RenderSceneCB);
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
    
    Vertices[0] = glm::vec3(-0.5f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 0.5f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязка array buff к указателю VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
    glEnable(GL_BLEND); //enable alpha blending

    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();
}
