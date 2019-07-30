//
//  main.cpp
//  OpenGLtest1
//
//  Created by apple on 2019/5/3.
//  Copyright © 2019 apple. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void framebuffer_size_callback(GLFWwindow* window, int width, int height); // 在每次窗口大小被调整的时候被调用
void processInput(GLFWwindow *window); //输入控制

// settings 窗口宽和长
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // ----------------------------------
    // 初始化和配置 glfw: initialize and configure
    glfwInit(); //初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //使用 glfwWindowHint 函数来配置GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // //适配 OS X 的编译
#endif
    // ----------------------------------
    // 创建一个窗口对象 glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); //创建窗口
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //（Terminate终止） 释放/删除之前的分配的所有资源
        return -1;
    }
    glfwMakeContextCurrent(window); //将创建的窗口设置为当前窗口（通知GLFW将我们窗口的上下文设置为当前线程的主上下文）
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //每当窗口调整大小的时候调用framebuffer_size_callback
    // ----------------------------------
    // 加载所有OpenGL函数指针 glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // ----------------------------------
    
    
    
    
    
    
    
    //========================================================================
    Shader ourShader("/书/OGL_Test/vertexSource.txt", "/书/OGL_Test/fragmentSource.txt");
    //========================================================================
    
    
    
    
    
    
    //========================================================================
    // 三个顶点，标准化设备坐标 set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        //位置                   //颜色                  //纹理坐标
         0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,   // 右上角 top right
         0.5f, -0.5f,  0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,   // 右下角 bottom right
        -0.5f, -0.5f,  0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,   // 左下角 bottom left
        -0.5f,  0.5f,  0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f    // 左上角 top left
    };
    
    unsigned int indices[] = {  // 注意索引从0开始 note that we start from 0!
        0, 1, 3,  // 第一个三角形 first Triangle
        1, 2, 3   // 第二个三角形 second Triangle
    };
    
    
    
    //-----------------------------------------------------
    unsigned int VBO, VAO, EBO; //VBO：顶点缓冲对象的ID；VAO：顶点数组对象的ID；EBO：索引缓冲对象的ID
    
    glGenVertexArrays(1, &VAO); //创建1个 顶点数组对象
    glGenBuffers(1, &VBO); //创建1个 顶点缓冲对象
    glGenBuffers(1, &EBO); //创建1个 索引缓冲对象
    
    glBindVertexArray(VAO); //绑定VAO
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //把顶点缓冲对象绑定到GL_ARRAY_BUFFER（顶点缓冲对象的缓冲类型）目标上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把 顶点数据vertices 复制到缓冲的内存中
    //glBufferData参数：目标缓冲的类型（顶点缓冲），大小，数据，数据不会或几乎不会改变。
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //把索引缓冲对象绑定到GL_ELEMENT_ARRAY_BUFFER（索引缓冲对象的缓冲类型）目标上
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//把 索引数据indices 复制到缓冲的内存中
    //glBufferData参数：目标缓冲的类型（索引缓冲），大小，数据，数据不会或几乎不会改变。
    //-----------------------------------------------------
    
    
    
    //——————————————————————————————————————————————————————————————
    //位置属性 position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //告诉OpenGL该如何解析顶点数据
    //参数：Location=0 ，3个值（坐标vec3），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在8个float之后），起始位置的偏移量0
    glEnableVertexAttribArray(0); //启用顶点属性0（顶点的 属性位置 = 0）
    //---------------------------
    //颜色属性 color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //参数：Location=1 ，3个值（颜色vec3），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在8个float之后），起始位置的偏移量3个float
    glEnableVertexAttribArray(1); //启用顶点属性1（顶点的 属性位置 = 1）
    //---------------------------
    //纹理坐标属性 texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //参数：Location=2 ，2个值（纹理坐标vec2），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在8个float之后），起始位置的偏移量6个float
    glEnableVertexAttribArray(2); //启用顶点属性2（顶点的 属性位置 = 2）
    //———————————————————————————————————————————————————————————————
    
    
    //================================================================================
    
    
    
    
    
    
    //================================================================================
    // 生成纹理 load and create a texture
    // ----------------------------------------------------------
    unsigned int texture1, texture2; //纹理ID
    
    // texture 1
    // ----------------------------------
    glGenTextures(1, &texture1); //生成 1 个纹理，保存ID到texture
    glBindTexture(GL_TEXTURE_2D, texture1); // 绑定纹理，接下来所有GL_TEXTURE_2D操作都是对此纹理
    // 设置纹理环绕方式参数 set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置纹理过滤参数 set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //纹理被缩小的时候使用线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //纹理被放大的时候使用线性过滤
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // 让stb_image.h在加载图片时翻转y轴
    unsigned char *data = stbi_load("/书/OGL_Test/container.jpg", &width, &height, &nrChannels, 0); //加载图片
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //生成一个纹理
        //参数：纹理目标GL_TEXTURE_2D，Mipmap级别0，纹理存储为RGB格式，宽度，高度，历史遗留总是0，使用RGB值加载，储存为char(byte)数组，图像数据
        glGenerateMipmap(GL_TEXTURE_2D); //自动生成所有需要的多级渐远纹理（Mipmap）
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); //生成了纹理和相应的Mipmap后，释放图像的内存
    
    // texture 2
    // ----------------------------------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // 让stb_image.h在加载图片时翻转y轴
    data = stbi_load("/书/OGL_Test/im.png", &width, &height, &nrChannels, 0); //加载图片
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // 先设置uniform
    ourShader.setInt("texture1", 0); // 告诉OpenGL每个着色器采样器属于哪个纹理单元
    ourShader.setInt("texture2", 1); // 使用着色器类设置
    //================================================================================
    
    
    
    
    
    

    
    // ------------------------------
    // 渲染循环 render loop
    while (!glfwWindowShouldClose(window)) //每次循环的开始前检查一次GLFW是否被要求退出
    {
        // 输入 input
        processInput(window); //输入控制（检查是否按下Esc）
        
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设置清空屏幕后填充的颜色
        glClear(GL_COLOR_BUFFER_BIT); //清空屏幕的颜色缓冲
        
        
        // draw
        //=========================================================================
        
        // 在相应的纹理单元上绑定纹理 bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0); // 先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture1); //绑定纹理
        glActiveTexture(GL_TEXTURE1); // 先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture2); //绑定纹理
        
        
        
        // activate shader
        ourShader.use();
        
        
        
        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // 模型矩阵
        glm::mat4 view          = glm::mat4(1.0f); // 观察矩阵
        glm::mat4 projection    = glm::mat4(1.0f); // 投影矩阵
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // 查询uniform变量的地址retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model"); // 查询uniform变量的地址
        unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view"); // 查询uniform变量的地址
        // 把矩阵数据发送给着色器（3种方法）pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // 注意：目前我们每帧都设置了投影矩阵，但由于投影矩阵很少改变，因此通常最好将它设置在主循环之外一次。
        ourShader.setMat4("projection", projection);
        
        
        
        
        
        
        // 渲染容器 render container
        glBindVertexArray(VAO); // 在绘制物体前简单地把VAO绑定到希望使用的设定上
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //从索引缓冲渲染（绘制三角形，6个顶点，索引的类型m，偏移量）
        //=========================================================================
        
        
        glfwSwapBuffers(window); //交换颜色缓冲，用来绘制，并且将会作为输出显示在屏幕上。
        glfwPollEvents(); //检查有没有触发什么事件
    }
    // -------------------------------
    
    
    
    
    
    //=============================================================================
    // 取消所有资源的分配 optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //=============================================================================
    
    
    
    
    
    // 终止，释放/删除之前的分配的所有资源
    // -------------------------------
    glfwTerminate(); //（Terminate终止） 释放/删除之前的分配的所有资源
    return 0;
}


// 在GLFW中实现一些输入控制 process all input
// --------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检查用户是否按下了返回键(Esc)
        glfwSetWindowShouldClose(window, true); //GLFW被要求退出（渲染循环时检查）
}

// 在每次窗口大小被调整的时候被调用 glfw: whenever the window size changed
// --------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //1,2参数控制窗口左下角的位置。3,4控制渲染窗口的宽度和高度（可以比GLFW的维度小）
}
