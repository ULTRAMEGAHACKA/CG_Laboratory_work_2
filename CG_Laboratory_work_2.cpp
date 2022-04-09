#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;

GLuint VBO;
float scale = 0.0;
//class Vertexx
//{
//private:
//    float x;
//    float y;
//    float z;
//    float w = 1.0f;
//    glm::vec4 TranslationVector[3];
//public:
//    Vertexx(glm::vec3 some_vertex)
//    {
//        x = some_vertex.x;
//        y = some_vertex.y;
//        z = some_vertex.z;
//    }
//    glm::vec4 multiply(glm::mat4 TranslationMatrix)
//    {
//        for (int i = 0; i < 4; i++) {
//
//        }
//    }
//};
void RenderSceneCB()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glColor4f(0.0f, 1.0f, 0.0f, 0.5);
    glDrawArrays(GL_LINE_LOOP, 0, 3); // GL_TRIANGLES // GL_LINE_LOOP // GL_LINE_STRIP
    //glDrawArrays(GL_LINE_LOOP, 3, 3);
    glm::vec3 Vertices[3];
    scale += rand()%1-1;
    Vertices[0] = glm::vec3(0.5f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(1.0f, 0.5f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::mat4 TranslationMatrix(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        sinf(scale), 0.0f, 0.0f, 1.0f);

    for (int i = 0; i < 3; i++)
    {
        Vertices[i] = TranslationMatrix * glm::vec4(Vertices[i], 1.0f);
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязка array buff к указателю VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
    glEnable(GL_BLEND); //enable alpha blending

    glDisableVertexAttribArray(0);
    glutSwapBuffers();
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

    //glm::vec3 Vertices[3];
    //Vertices[0] = glm::vec3(0.5f, 0.0f, 0.0f);
    //Vertices[1] = glm::vec3(1.0f, 0.5f, 0.0f);
    //Vertices[2] = glm::vec3(0.0f, 0.5f, 0.0f);
    //glm::mat4 TranslationMatrix( 1.0f, 0.0f, 0.0f, 0.0f,
    //                             0.0f, 1.0f, 0.0f, 0.0f,
    //                             0.0f, 0.0f, 1.0f, 0.0f,
    //                             sinf(1), 0.0f, 0.0f, 1.0f);
    //for (int i = 0; i < 3; i++)
    //{
    //    Vertices[i] = TranslationMatrix * glm::vec4(Vertices[i], 1.0f);
    //}
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO); //привязка array buff к указателю VBO
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
    //glEnable(GL_BLEND); //enable alpha blending

    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();
}
