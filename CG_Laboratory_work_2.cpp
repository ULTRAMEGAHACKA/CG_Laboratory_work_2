#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

GLuint VBO;
double scale = 0.0;
glm::vec3 Vertices[3];

void RenderSceneCB()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glColor4f(0.0f, 1.0f, 0.0f, 0.5);
    glDrawArrays(GL_TRIANGLES, 0, 3); // GL_TRIANGLES // GL_LINE_LOOP // GL_LINE_STRIP
    scale += 0.003;
    //glDrawArrays(GL_LINE_LOOP, 3, 3);

    glm::mat4 transformMatrix(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        sinf(scale), 0.0f, 0.0f, 1.0f);
    glm::mat4 transformMatrixZ(
        cosf(scale), sinf(scale), 0.0f, 0.0f,
        -sinf(scale), cosf(scale), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f); //вокруг Z
    glm::mat4 transformMatrixY(
        cosf(scale), 0.0f, sinf(scale), 0.0f,
        0.0f, 1.0f, cosf(scale), 0.0f,
        -sinf(scale), 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f); //вокруг Y
    glm::mat4 transformMatrixX(
        1.0f, cosf(scale), sinf(scale), 0.0f,
        0.0f, -sinf(scale), cosf(scale), 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f); // вокруг X
    glm::mat4 transformMatrix5(
        sinf(scale), 0.0f, 0.0f, 0.0f,
        0.0f, sinf(scale), 0.0f, 0.0f,
        0.0f, 0.0f, sinf(scale), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);


    glm::mat4 BASEtransformMatrix = transformMatrixZ * transformMatrixX * transformMatrix5;
    glLoadMatrixf(reinterpret_cast<const float*>(&BASEtransformMatrix));

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
