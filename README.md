Laboratory work №1 (Computer graphics)
======================================
*In this lab work we create a window, point and triangles*

main.cpp
==============
```cpp 
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 
``` 
Set a constant value of the window size

```cpp 
GLuint VBO1, VBO2, IBO1, IBO2;
``` 
We add two more pointers to the buffer object for the vertex buffer(VBO1, VBO2) and two more pointers to the index buffer(IBO1, IBO2).

```cpp 
glm::vec3 Vertices1[4];
``` 
Initializing a vertex array.

```cpp 
static void CreateVertexBuffer() {}
``` 
function that is called in main(). It initializes the vertex arrays Vertices1 and Vertices2, and binds them to the buffer and also allocates memory for them in the GPU.

```cpp 
static void CreateIndexBuffer() {}
```
function that is called in main(). It initializes the indices arrays Indices and Indices2 and binds them to the buffer and also allocates memory for them in the GPU.

*in RenderSceneCB*
==============

```cpp 
static float Scale = 0.0f;
``` 

variable which is changed in the RenderSceneCB() function. We put it as a parameter sinf(Scale) in the function.

```cpp
Pipeline p;
```
create a PipeLine object

```cpp
p.WorldPos
```
set parameters to change the transformation  matrix to move our vertices 

```cpp
p.Rotate
```
set parameters to change the transformation  matrix to rotate our pyramid

```cpp
p.Scale
```
set parameters to change the transition matrix to scale up our pyramid

```cpp
    glm::vec3 CameraPos(1.0f, 1.0f, -3.0f);
    glm::vec3 CameraTarget(0.0f, 0.0f, 2.0f);
    glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
    p.SetCamera(CameraPos, CameraTarget, CameraUp);
```
create three vectors that are responsible for the camera position, direction, and height, and send them as a parameter to p.SetCamera()

```cpp
glLoadMatrixf(reinterpret_cast<const float*>(p.GetTrans()));
```
replace the current matrix with the specified matrix. In our case it's p.GetTrans()
```cpp
p.GetTrans()
```
returns the matrix with the set parameters

```cpp
p.SetPerspectiveProj(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1000.0f);
```
set the parameters for the projection matrix

```cpp
glDrawElements(GLenum mode,
 	GLsizei count,
 	GLenum type,
 	const void * indices);
```
render primitives from array data. *mode* - Specifies what kind of primitives to render. *count* - Specifies the number of elements to be rendered. *type* - Specifies the type of the values in indices. *indices* - Specifies a pointer to the location where the indices are stored.

Pipeline.h
==============

*private attributes*
===================
```cpp
    glm::vec3 m_scale;
    glm::vec3 m_worldPos;
    glm::vec3 m_rotateInfo;
```
declare 3 vectors that are responsible for size, position, and rotation
```cpp
    struct {
        float FOV;
        float Width;
        float Height;
        float zNear;
        float zFar;
    } m_persProj;
```
a structure that stores the vertical view height (FOV), window width (Wigth), window height (Height), and how close (zNear) or far (zFar) the object is located.

```cpp
    struct {
        glm::vec3 Pos;
        glm::vec3 Target;
        glm::vec3 Up;
    } m_camera;
```
the structure in which there is a vector responsible for the camera position, a vector responsible for the direction and a vector responsible for the height.

*public attributes*
===================
```cpp
    Pipeline()
    {
        m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
        m_worldPos = glm::vec3(0.0f, 0.0f, 0.0f);
        m_rotateInfo = glm::vec3(0.0f, 0.0f, 0.0f);
    }
```
constructor that sets standard parameters

```cpp
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
    void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
    {
        m_persProj.FOV = FOV;
        m_persProj.Width = Width;
        m_persProj.Height = Height;
        m_persProj.zNear = zNear;
        m_persProj.zFar = zFar;
    }
    void SetCamera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
    {
        m_camera.Pos = Pos;
        m_camera.Target = Target;
        m_camera.Up = Up;
    }
```
these methods set custom values for the parameters described in the private field.

```cpp
    void Normalize(glm::vec3 vector)
    {
        const float Length = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        vector.x /= Length;
        vector.y /= Length;
        vector.z /= Length;
    }
```
In this method we normalize the vector, that is, we divide all the components of the vector by its length.

```cpp
    glm::vec3 Cross(const glm::vec3& v1, glm::vec3 v2) const
    {
        const float _x = v2.y * v1.z - v2.z * v1.y;
        const float _y = v2.z * v1.x - v2.x * v1.z;
        const float _z = v2.x * v1.y - v2.y * v1.x;

        return glm::vec3(_x, _y, _z);
    }
```
method that returns a vector perpendicular to the plane defined by the original vectors.

```cpp
    const glm::mat4* GetTrans() 
    {
        //=========================================
        glm::mat4 ScaleTrans(
            sinf(m_scale.x), 0.0f, 0.0f, 0.0f,
            0.0f, sinf(m_scale.y), 0.0f, 0.0f,
            0.0f, 0.0f, sinf(m_scale.z), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); // размер
        //=========================================
        glm::mat4 TranslationTrans(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f  ,
            m_worldPos.x, m_worldPos.y, m_worldPos.z, 1.0f); // положение
        //=========================================
        const float x = glm::radians(m_rotateInfo.x);
        const float y = glm::radians(m_rotateInfo.y);
        const float z = glm::radians(m_rotateInfo.z);

        glm::mat4x4 transformMatrixZ(
            cosf(z), -sinf(z), 0.0f, 0.0f,
            sinf(z), cosf(z), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); //вокруг Z
        glm::mat4x4 transformMatrixY(
            cosf(y), 0.0f, -sinf(x), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            sinf(x), 0.0f, cosf(y), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); //вокруг Y
        glm::mat4x4 transformMatrixX(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosf(x), -sinf(x), 0.0f,
            0.0f, sinf(x), cosf(x), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f); // вокруг X
        glm::mat4x4 RotateTrans = transformMatrixZ * transformMatrixY * transformMatrixX;
        //=========================================
        const float ar = m_persProj.Width / m_persProj.Height;
        const float zNear = m_persProj.zNear;
        const float zFar = m_persProj.zFar;
        const float zRange = zNear - zFar;
        const float tanHalfFOV = tanf(glm::radians(m_persProj.FOV / 2.0));
        glm::mat4 PersProjTrans(
            1.0f / (tanHalfFOV * ar), cosf(x), sinf(x), 0.0f,
            0.0f, 1.0f / tanHalfFOV, cosf(x), 0.0f,
            0.0f, 0.0f, (-zNear - zFar) / zRange, 1.0f,
            0.0f, 0.0f, 2.0f * zFar * zNear / zRange, 0.0f);
        //=========================================
        glm::vec3 N = m_camera.Target; // m_camera.Target, m_camera.Up
        Normalize(N);
        glm::vec3 U = m_camera.Up;
        Normalize(U);
        U = Cross(m_camera.Target,U);
        glm::vec3 V = Cross(U,N);

        glm::mat4 CameraRotateTrans(
            U.x, V.x, N.x, 0.0f,
            U.y, V.y, N.y, 0.0f,
            U.z, V.z, N.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        //=========================================
        glm::mat4 CameraTranslationTrans(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z, 1.0f);
        //=========================================

        glm::mat4 m_transformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * TranslationTrans * RotateTrans * ScaleTrans;
        return &m_transformation;
    }
```
method in which size, rotation, position, projection and camera position matrices are defined. As a result, the method returns the final matrix - the matrices multiplied with each other


























