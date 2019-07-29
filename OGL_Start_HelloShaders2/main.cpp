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


void framebuffer_size_callback(GLFWwindow* window, int width, int height); // 在每次窗口大小被调整的时候被调用
void processInput(GLFWwindow *window); //输入控制

// settings 窗口宽和长
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//================================================================
const char *vertexShaderSource = "#version 330 core\n" //顶点着色器代码；版本声明OpenGL 3.3
"layout (location = 0) in vec3 aPos;\n"   // 位置 变量的 属性位置 为 0  (从顶点数据获得坐标)
"layout (location = 1) in vec3 aColor;\n" // 颜色 变量的 属性位置 为 1  (从顶点数据获得颜色)

"out vec3 ourColor;\n" // 向片段着色器输出一个颜色

"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"   // 将ourColor设置为从顶点数据得到的输入颜色
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n" //out 输出颜色

"in vec3 ourColor;\n" // 从顶点着色器传来的ourColor

"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";
//================================================================

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
    // 顶点着色器 Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER); //创建一个顶点着色器，得到它的ID
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //把 顶点着色器源码（1个） 附加到 顶点着色器对象
    glCompileShader(vertexShader); //编译顶点着色器
    
    //-----------------------------------------
    // 检测编译是否成功 check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //-----------------------------------------
    
    // 片段着色器 Fragment Shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //创建一个片段着色器，得到它的ID
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //把 片段着色器源码（1个） 附加到 片段着色器对象
    glCompileShader(fragmentShader); //编译片段着色器
    
    //-----------------------------------------
    // 检测编译是否成功 check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //-----------------------------------------
    
    // 着色器程序。把两个 着色器对象 链接到一个用来渲染的 着色器程序 link shaders
    int shaderProgram = glCreateProgram(); //创建一个着色器程序，得到它的的ID
    glAttachShader(shaderProgram, vertexShader); //把 顶点着色器 附加到 着色器程序 对象上
    glAttachShader(shaderProgram, fragmentShader); //把 片段着色器 附加到 着色器程序 对象上
    glLinkProgram(shaderProgram); //链接（把每个着色器的输出链接到下个着色器的输入）
    
    //-----------------------------------------
    // 检测编译是否成功 check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //-----------------------------------------
    
    glDeleteShader(vertexShader); // 删除着色器对象（已经链接到程序对象）
    glDeleteShader(fragmentShader); // 删除着色器对象（已经链接到程序对象）
    //========================================================================
    
    
    
    
    
    
    //========================================================================
    // 三个顶点，标准化设备坐标 set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        //位置                   //颜色
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,  // 右上角 top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,  // 右下角 bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  // 左下角 bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f   // 左上角 top left
    };
    
    unsigned int indices[] = {  // 注意索引从0开始 note that we start from 0!
        0, 1, 3,  // 第一个三角形 first Triangle
        1, 2, 3   // 第二个三角形 second Triangle
    };
    
    unsigned int VBO, VAO, EBO; //VBO：顶点缓冲对象的ID；VAO：顶点数组对象的ID；EBO：索引缓冲对象的ID
    
    glGenVertexArrays(1, &VAO); //创建1个 顶点数组对象
    glGenBuffers(1, &VBO); //创建1个 顶点缓冲对象
    glGenBuffers(1, &EBO); //创建1个 索引缓冲对象
    
    glBindVertexArray(VAO); //绑定VAO
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //把顶点缓冲对象绑定到GL_ARRAY_BUFFER（顶点缓冲对象的缓冲类型）目标上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把 顶点数据vertices 复制到缓冲的内存中
    //glBufferData参数：目标缓冲的类型（顶点缓冲），大小，数据，数据不会或几乎不会改变。
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //把索引缓冲对象绑定到GL_ELEMENT_ARRAY_BUFFER（索引缓冲对象的缓冲类型）目标上
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //——————————————————————————————————————————————————————————————
    //位置属性 position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //告诉OpenGL该如何解析顶点数据
    //参数：Location=0 ，3个值（坐标vec3），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在6个float之后），起始位置的偏移量0
    glEnableVertexAttribArray(0); //启用顶点属性0（顶点的 属性位置 = 0）
    //---------------------------
    //颜色属性 color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //参数：Location=1 ，3个值（坐标vec3），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在6个float之后），起始位置的偏移量3个float
    glEnableVertexAttribArray(1); //启用顶点属性1（顶点的 属性位置 = 1）
    //———————————————————————————————————————————————————————————————
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); //取消绑定
    
    // 当VAO处于活动状态时，不要取消绑定EBO，VAO会储存glBindBuffer的函数调用，这也意味着它也会储存解绑调用。
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0); //取消绑定
    //================================================================================
    
    //因为只有一个着色器，所以也可以事先激活我们的着色器（本来在下面while里）
    glUseProgram(shaderProgram); //激活着色器程序
    
    
    
    
    
    
    // ------------------------------
    // 渲染循环 render loop
    while (!glfwWindowShouldClose(window)) //每次循环的开始前检查一次GLFW是否被要求退出
    {
        // 输入 input
        processInput(window); //输入控制（检查是否按下Esc）
        
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设置清空屏幕后填充的颜色
        glClear(GL_COLOR_BUFFER_BIT); //清空屏幕的颜色缓冲
        
        
        //=========================================================================
        // draw our first triangle
//        glUseProgram(shaderProgram); //激活着色器程序（移到while上面）
        
        
        
        glBindVertexArray(VAO); // 在绘制物体前简单地把VAO绑定到希望使用的设定上
//        glDrawArrays(GL_TRIANGLES, 0, 3); //绘制三角形，起始索引为0，顶点数3
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //从索引缓冲渲染（绘制三角形，6个顶点，索引的类型m，偏移量）
        // glBindVertexArray(0); // no need to unbind it every time
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
