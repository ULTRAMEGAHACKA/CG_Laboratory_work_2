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












