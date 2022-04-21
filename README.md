Laboratory work №1 (Computer graphics)
======================================
*In this lab work we create a window, point and triangles*

main.cpp
==============
```cpp #define WINDOW_WIDTH 800```
```cpp #define WINDOW_HEIGHT 600 ``` - set a constant value of the window size

```cpp GLuint VBO1, VBO2, IBO1, IBO2;``` - We add two more pointers to the buffer object for the vertex buffer(VBO1, VBO2) and two more pointers to the index buffer(IBO1, IBO2).

```cpp glm::vec3 Vertices1[4];``` - Initializing a vertex array.

```cpp static void CreateVertexBuffer() {}``` - function that is called in main(). It initializes the vertex arrays Vertices1 and Vertices2, and binds them to the buffer and also allocates memory for them in the GPU.

```cpp static void CreateIndexBuffer() {}``` - function that is called in main(). It initializes the indices arrays Indices and Indices2 and binds them to the buffer and also allocates memory for them in the GPU.

```cpp static float Scale = 0.0f;``` - 
