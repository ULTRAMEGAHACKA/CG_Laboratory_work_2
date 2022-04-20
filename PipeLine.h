#pragma once
#ifndef PIPELINE_H
#define	PIPELINE_H
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;
const double M_PI = 3.141592653589793;

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

class Pipeline
{
public:
    Pipeline()
    {
        m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
        m_worldPos = glm::vec3(0.0f, 0.0f, 0.0f);
        m_rotateInfo = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    void Scale(float ScaleX, float ScaleY, float ScaleZ)
    {
        m_scale.x = ScaleX;
        m_scale.y = ScaleY;
        m_scale.z = ScaleZ;
    }

    void WorldPos(float x, float y, float z)
    {
        m_worldPos.x = x;
        m_worldPos.y = y;
        m_worldPos.z = z;
    }

    void Rotate(float RotateX, float RotateY, float RotateZ)
    {
        m_rotateInfo.x = RotateX;
        m_rotateInfo.y = RotateY;
        m_rotateInfo.z = RotateZ;
    }

    const glm::mat4* GetTrans() 
    {
        glm::mat4 ScaleTrans(
            sinf(m_scale.x), 0.0f, 0.0f, 0.0f,
            0.0f, sinf(m_scale.y), 0.0f, 0.0f,
            0.0f, 0.0f, sinf(m_scale.z), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); // размер
        
        glm::mat4 TranslationTrans(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f  ,
            m_worldPos.x, m_worldPos.y, m_worldPos.z, 1.0f); // положение

        const float x = ToRadian(m_rotateInfo.x);
        const float y = ToRadian(m_rotateInfo.y);
        const float z = ToRadian(m_rotateInfo.z);

        glm::mat4 transformMatrixZ(
            cosf(z), sinf(z), 0.0f, 0.0f,
            -sinf(z), cosf(z), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); //вокруг Z
        glm::mat4 transformMatrixY(
            cosf(y), 0.0f, sinf(y), 0.0f,
            0.0f, 1.0f, cosf(y), 0.0f,
            -sinf(y), 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); //вокруг Y
        glm::mat4 transformMatrixX(
            1.0f, cosf(x), sinf(x), 0.0f,
            0.0f, -sinf(x), cosf(x), 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); // вокруг X
        glm::mat4 RotateTrans = transformMatrixX * transformMatrixY * transformMatrixZ;

        glm::mat4 m_transformation = TranslationTrans * ScaleTrans * RotateTrans;
        return &m_transformation;
    }

private:
    glm::vec3 m_scale;
    glm::vec3 m_worldPos;
    glm::vec3 m_rotateInfo;
};

#endif	/* PIPELINE_H */