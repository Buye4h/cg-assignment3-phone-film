#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cmath>

#include "Libs/Shader.h"
#include "Libs/Window.h"
#include "Libs/Mesh.h"
#include "Libs/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
std::vector<Mesh *> meshList;
std::vector<Shader> shaderList;

// Assignment 3
// Tharita Watanapa 
// Pilada Prasan 

// Vertex Shader
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void CreateTriangle()
{
    GLfloat vertices_mount_mid[] =
        {
            -1.0f, -1.0f, 0.3f, 0.0f, 0.0f, // 0
            -0.3f, -1.0f, 1.0f, 0.5f, 0.0f, // 1
            1.3f, -1.0f, 0.3f, 1.0f, 0.0f,  // 2
            0.0f, 1.3f, 0.0f, 0.5f, 1.0f    // 3
        };
    unsigned int indices_mount_mid[] =
        {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2};

    // Snowball-----------------------------------------
    GLfloat vertices_Snowball[] =
        {
            -0.8f, -1.0f, -0.54f, 0.0f, 0.0f, // 0
            -0.5f, -1.0f, 1.54f, 1.0f, 0.0f,  // 1
            0.8f, -1.0f, -0.54f, 1.0f, 1.0f,  // 2
            0.8f, -1.0f, 1.54f, 0.0f, 1.5f,   // 3
            -0.4f, 1.5f, 1.0f, 0.7f, 0.0f,    // 4
            0.5f, 1.5f, 1.0f, 1.3f, 0.2f,     // 5
            -0.4f, 1.5f, 0.0f, 0.4f, 0.5f,    // 6
            0.5f, 1.5f, 0.0f, 0.0f, 0.0f      // 7
        };
    unsigned int indices_Snowball[] =
        {
            0, 6, 1, // face 1
            1, 6, 4, // face 2
            4, 1, 3, // face 3
            3, 4, 5,
            5, 3, 2,
            2, 5, 7,
            7, 2, 6,
            6, 2, 0 // face 4
        };

    // Cube ground
    GLfloat vertices_Cube[] =
        {
            -1.0f, -1.0f, 0.0f, 1.0f, 1.2f,  // 0
            1.0f, -1.0f, 1.0f, 0.5f, 1.1f,   // 1
            1.0f, 1.0f, 1.0f, 1.5f, 0.5f,    // 2
            -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // 3
            -1.0f, -1.0f, -1.0f, 0.5f, 1.3f, // 4
            1.0f, -1.0f, -1.0f, 0.7f, 0.2f,  // 5
            1.0f, 1.0f, -1.0f, 1.0f, 0.6f,   // 6
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f   // 7
        };

    unsigned int indices_Cube[] =
        {
            3, 2, 0,
            0, 2, 1,
            1, 2, 6,
            1, 6, 5,
            5, 6, 4,
            7, 4, 6,
            7, 4, 3,
            0, 3, 4,
            7, 3, 6, // up_one
            2, 6, 3  // up_two
        };

    // Moon
    GLfloat vertices_Moon[] =
        {
            0.0f, 2.0f, 1.0f, 0.0f, 0.1f,   // 0
            0.5f, 2.13f, 1.0f, 0.0f, 0.5f,  // 1
            1.0f, 2.0f, 1.0f, 0.0f, 0.1f,   // 2
            1.4f, 1.5f, 1.0f, 0.0f, 0.8f,   // 3
            1.5f, 1.0f, 1.0f, 0.0f, 0.5f,   // 4
            1.35f, 0.5f, 1.0f, 0.0f, 1.0f,  // 5
            1.0f, 0.0f, 1.0f, 0.2f, 0.1f,   // 6
            0.5f, 0.0f, 1.0f, 0.1f, 0.0f,   // 7
            0.0f, 0.0f, 1.0f, 0.3f, 0.0f,   // 8
            -0.36f, 0.5f, 1.0f, 0.1f, 0.5f, // 9
            -0.5f, 1.0f, 1.0f, 0.4f, 0.0f,  // 10
            -0.41f, 1.5f, 1.0f, 0.0f, 0.5f, // 11
            0.5f, 1.0f, 1.5f, 1.0f, 0.2f    // 12 center
        };

    unsigned int indices_Moon[] =
        {
            0, 12, 11,
            11, 12, 10,
            10, 12, 9,
            9, 12, 8,
            8, 12, 7,
            7, 12, 6,
            6, 12, 5,
            5, 12, 4,
            4, 12, 3,
            3, 12, 2,
            2, 12, 1,
            1, 12, 0

        };

    // Grass plant
    GLfloat vertices_Grass[] =
        {
            0.0f, 0.0f, 1.0f, 0.5f, 1.0f,    // 0
            0.0f, 1.0f, 1.0f, 0.3f, 1.0f,    // 1
            -0.24f, 1.91f, 1.0f, 2.0f, 0.4f, // 2
            -1.1f, 2.97f, 1.0f, 0.3f, 3.0f,  // 3
            0.58f, 2.14f, 1.0f, 0.0f, 0.0f,  // 4
            1.0f, 1.0f, 1.0f, 0.5f, 0.0f,    // 5
            1.0f, 0.0f, 1.0f, 0.0f, 1.0f     // 7
        };
    unsigned int indices_Grass[] =
        {4, 3, 2,
         2, 4, 5,
         5, 2, 1,
         1, 0, 6,
         6, 1, 5};

    // Bird
    GLfloat vertices_Bird[] =
        {
            -0.5f, 1.00f, 1.00f, 1.5f, 1.0f,  // 0
            0.21f, 1.31f, 1.00f, 3.5f, 1.2f,  // 1
            0.21f, 1.11f, 1.0f, 0.5f, 1.0f,   // 2
            1.25f, 0.9f, 0.66f, 1.5f, 0.4f,   // 3
            1.25f, 1.11f, 0.66f, 0.5f, 1.6f,  // 4
            1.61f, 1.31f, 1.00f, 0.5f, 1.0f,  // 5
            1.651f, 1.11f, 1.00f, 2.5f, 1.8f, // 6
            2.50f, 1.00f, 1.00f, 0.5f, 2.0f   // 7
        };
    unsigned int indices_Bird[] =
        {
            1, 0, 2,
            2, 1, 4,
            4, 2, 3,
            3, 6, 4,
            4, 5, 6,
            6, 7, 5};

    Mesh *mount1 = new Mesh();
    mount1->CreateMesh(vertices_mount_mid, indices_mount_mid, 20, 12);

    Mesh *snowball = new Mesh();
    snowball->CreateMesh(vertices_Snowball, indices_Snowball, 40, 24);

    Mesh *cube = new Mesh();
    cube->CreateMesh(vertices_Cube, indices_Cube, 40, 30);

    Mesh *moon = new Mesh();
    moon->CreateMesh(vertices_Moon, indices_Moon, 65, 36);

    Mesh *grass = new Mesh();
    grass->CreateMesh(vertices_Grass, indices_Grass, 40, 15);

    Mesh *bird = new Mesh();
    bird->CreateMesh(vertices_Bird, indices_Bird, 40, 18);

    meshList.push_back(mount1);
    meshList.push_back(mount1);
    meshList.push_back(mount1);
    meshList.push_back(cube);
    meshList.push_back(cube);
    meshList.push_back(moon);
    meshList.push_back(snowball); // snowball
    meshList.push_back(snowball); // snowball
    // grass_right_hand
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    // grass_left_hand
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    // bird
    meshList.push_back(bird);
    meshList.push_back(bird);
    meshList.push_back(bird);
    // grass_small
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);
    meshList.push_back(grass);

    // sky
    meshList.push_back(moon);
}

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = Window(WIDTH, HEIGHT, 3, 3);
    mainWindow.initialise();

    CreateTriangle();
    CreateShaders();

    GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.5f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);

    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, up));
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, -cameraRight));

    /////////////////////////////////////////////////////////////////////////////////////////////

    // texture
    // 0
    unsigned int texture; // mount mid 0 right left
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels; // mount mid 0 right left
    unsigned char *data = stbi_load("Textures/4.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // 1 base soil
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    unsigned char *data1 = stbi_load("Textures/25.jpg", &width, &height, &nrChannels, 0);
    if (data1)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1);

    // 2 baseSnow
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    unsigned char *data2 = stbi_load("Textures/25.jpg", &width, &height, &nrChannels, 0);
    if (data2)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);

    // 3 Moon
    unsigned int texture3;
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);

    unsigned char *data3 = stbi_load("Textures/49.jpg", &width, &height, &nrChannels, 0);
    if (data3)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data3);

    // 4 grass
    unsigned int texture4;
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data4 = stbi_load("Textures/44.jpg", &width, &height, &nrChannels, 0);
    if (data4)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data4);

    // 5 sky
    unsigned int texture5;
    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data5 = stbi_load("Textures/53.jpg", &width, &height, &nrChannels, 0);
    if (data5)
    {
        // bind image with texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data5);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        // Get + Handle user input events
        glfwPollEvents();

        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraDirection * 0.01f;
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraDirection * 0.01f;
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= cameraRight * 0.01f;
        if (glfwGetKey(mainWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += cameraRight * 0.01f;

        // Clear window เปลี่ยนสีพื้นหลัง
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw here
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetUniformLocation("model");
        uniformView = shaderList[0].GetUniformLocation("view");
        uniformProjection = shaderList[0].GetUniformLocation("projection");

        //ตำแหน่ง Object
        glm::vec3 pyramidPositions[] =
            {
                glm::vec3(-0.1f, -0.2f, -5.5f), // mount mid                  0
                glm::vec3(3.0f, 0.0f, -6.5f),   // mount right                1
                glm::vec3(-3.5f, 0.0f, -7.5f),  // mount left-----------------2--

                glm::vec3(0.0f, -1.6f, -5.5f), // base soil                  3
                glm::vec3(0.0f, -1.8f, -2.8f), // base lake                  4

                glm::vec3(-1.1f, -0.5f, -8.8f), // moon-------------------     5

                glm::vec3(-0.8f, -0.5f, -1.15f),  // snowball                   6
                glm::vec3(-0.45f, -0.5f, -0.85f), // snowball small-------------7-----
                glm::vec3(0.8f, -0.8f, -1.08f),   // grass_right_1              8
                glm::vec3(0.8f, -0.8f, -1.0f),    // grass_right_2              9
                glm::vec3(0.72f, -0.8f, -0.8f),   // grass_right_3              10
                glm::vec3(0.71f, -0.8f, -0.7f),   // grass_right_4              11
                glm::vec3(0.72f, -0.8f, -0.65f),  // grass_right_5--------------12-----
                glm::vec3(-0.8f, -0.8f, -1.08f),  // grass_left_1               13
                glm::vec3(-0.8f, -0.8f, -1.0f),   // grass_left_2               14
                glm::vec3(-0.72f, -0.8f, -0.8f),  // grass_left_3               15
                glm::vec3(-0.71f, -0.8f, -0.7f),  // grass_left_4               16
                glm::vec3(-0.72f, -0.8f, -0.65f), // grass_left_5---------------17----
                glm::vec3(1.1f, 1.5f, -4.8f),     // bird 1                     18
                glm::vec3(0.5f, 1.9f, -6.8f),     // bird 2                     19
                glm::vec3(1.9f, 2.3f, -9.5f),     // bird 3-------------------  20
                glm::vec3(0.65f, -0.8f, -1.14f),  // grass_small_1              21
                glm::vec3(0.60f, -0.8f, -1.14f),  // grass_small_2              22
                glm::vec3(0.40f, -0.8f, -1.14f),  // grass_small_3              23
                glm::vec3(0.46f, -0.8f, -1.14f),  // grass_small_4              24
                glm::vec3(0.67f, -0.8f, -1.14f),  // grass_small_5              25

                glm::vec3(-7.0f, -15.0f, -13.8f), // sky-------------------     5
            };

        glm::vec3 pyramidScale[] =
            {
                glm::vec3(1.5f, 1.0f, 1.0f), // mount mid
                glm::vec3(2.5f, 1.5f, 1.0f), // mount right
                glm::vec3(2.0f, 1.2f, 1.0f), // mount left-------------------

                glm::vec3(6.0f, 0.4f, 4.0f), // base soil
                glm::vec3(2.0f, 0.6f, 3.0f), // base lake

                glm::vec3(2.0f, 2.0f, 0.1f),   // moon-------------------
                glm::vec3(0.32f, 0.07f, 0.1f), // snowball

                glm::vec3(0.12f, 0.03f, 0.05f), // snowball small-------------------
                glm::vec3(0.05f, 0.13f, 0.1f),  // grass_right_1
                glm::vec3(0.05f, 0.21f, 0.1f),  // grass_right_2
                glm::vec3(0.03f, 0.16f, 0.1f),  // grass_right_3
                glm::vec3(0.04f, 0.19f, 0.1f),  // grass_right_4

                glm::vec3(0.03f, 0.17f, 0.1f), // grass_right_5-------------------
                glm::vec3(0.05f, 0.13f, 0.1f), // grass_left_1
                glm::vec3(0.05f, 0.21f, 0.1f), // grass_left_2
                glm::vec3(0.03f, 0.26f, 0.1f), // grass_left_3
                glm::vec3(0.04f, 0.19f, 0.1f), // grass_left_4
                glm::vec3(0.03f, 0.17f, 0.1f), // grass_left_5--------------------

                glm::vec3(0.30f, 0.2f, 0.65f), // bird 1
                glm::vec3(0.30f, 0.2f, 0.65f), // bird 2
                glm::vec3(0.30f, 0.2f, 0.65f), // bird 3-------------------

                glm::vec3(0.05f, 0.05f, 0.2f), // grass_small_1
                glm::vec3(0.05f, 0.04f, 0.2f), // grass_small_2
                glm::vec3(0.03f, 0.06f, 0.2f), // grass_small_3
                glm::vec3(0.04f, 0.04f, 0.2f), // grass_small_4
                glm::vec3(0.03f, 0.06f, 0.2f), // grass_small_5

                glm::vec3(14.0f, 14.0f, 0.1f), // moon-------------------

            };

        glm::mat4 view(1.0f);

        glm::mat4 cameraPosMat(1.0f);
        cameraPosMat[0][3] = cameraPos.x;
        cameraPosMat[1][3] = cameraPos.y;
        cameraPosMat[2][3] = cameraPos.z;

        glm::mat4 cameraRotateMat(1.0f);
        cameraRotateMat[0] = glm::vec4(cameraRight.x, cameraUp.x, cameraDirection.x, 0.0f);
        cameraRotateMat[1] = glm::vec4(cameraRight.y, cameraUp.y, cameraDirection.y, 0.0f);
        cameraRotateMat[2] = glm::vec4(-cameraRight.z, -cameraUp.z, -cameraDirection.z, 0.0f);

        view = glm::lookAt(cameraPos, cameraPos + cameraDirection, up);

        // Mountain mid
        for (int i = 0; i < 27; i++)
        {
            glm::mat4 model(1.0f);

            // translate เพราะตอนแรกวัตถุอยู่หลังกล้อง
            // -x <---      ---> +x
            model = glm::translate(model, pyramidPositions[i]);
            // rotate 90 องศา รอบแกน Z
            // model = glm::rotate(model, 90.0f * 3.1416f / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, pyramidScale[i]);
            // model = glm::rotate(model, glm::radians(2.0f * 6), glm::vec3(0.0f, 0.0f, 1.0f));
            // model = glm::rotate(model, pyramidRotate[i], glm::vec3(0.0f, 0.0f, 1.0f));
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

            if (i >= 0 && i <= 2) // mount mid 0, mount right ,mount left

            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                meshList[0]->RenderMesh();
            }

            if (i == 3) // base soil
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                meshList[3]->RenderMesh();
            }
            if (i == 4) // base lake
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture2);
                meshList[4]->RenderMesh();
            }
            if (i == 5) // moon
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture3);
                meshList[5]->RenderMesh();
            }
            if (i == 6) // snowball
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                meshList[6]->RenderMesh();
            }
            if (i == 7) // snowball
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                meshList[7]->RenderMesh();
            }
            if (i >= 8 && i <= 17) // ground grass
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture4);
                meshList[8]->RenderMesh();
            }
            if (i >= 18 && i <= 20) // bird
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture3);
                meshList[18]->RenderMesh();
            }
            if (i >= 21 && i <= 25) // small grass
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture4);
                meshList[21]->RenderMesh();
            }
            if (i == 26)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture5);
                meshList[26]->RenderMesh();
            }
        }

        glUseProgram(0);
        // end draw

        mainWindow.swapBuffers();
    }

    return 0;
}
