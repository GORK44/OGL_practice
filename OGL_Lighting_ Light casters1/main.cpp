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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Shader.hpp"
#include "Camera.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height); // 在每次窗口大小被调整的时候被调用
void processInput(GLFWwindow *window); //输入控制
void mouse_callback(GLFWwindow* window, double xpos, double ypos);//鼠标移动控制方向
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);//滚轮控制FOV
unsigned int loadTexture(const char *path);

// settings 窗口宽和长
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 相机 camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f); //光源在世界空间的坐标


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
    
    
    
    
    glfwSetCursorPosCallback(window, mouse_callback);//鼠标一移动mouse_callback函数就会被调用
    glfwSetScrollCallback(window, scroll_callback);//滚轮一滚动scroll_callback函数就会被调用
    
    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
    
    
    // ----------------------------------
    // 加载所有OpenGL函数指针 glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // ----------------------------------
    
    
    
    
    
    
    //配置全局opengl状态
    //========================================================================
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    //========================================================================

    
    
    //构建并编译着色器程序
    //========================================================================
//    Shader ourShader("/书/OGL_Test/vertexSource.txt", "/书/OGL_Test/fragmentSource.txt");
    Shader lightingShader("/书/OGL_Test/colorsVS.txt", "/书/OGL_Test/colorsFS.txt");
    Shader lampShader("/书/OGL_Test/lampVS.txt", "/书/OGL_Test/lampFS.txt");
    //========================================================================
    
    
    
    
    
    
    //========================================================================
    // 三个顶点，标准化设备坐标 set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    
//    unsigned int indices[] = {  // 注意索引从0开始 note that we start from 0!
//        0, 1, 3,  // 第一个三角形 first Triangle
//        1, 2, 3   // 第二个三角形 second Triangle
//    };
    
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    
    //-----------------------------------------------------
    unsigned int VBO, cubeVAO; //VBO：顶点缓冲对象的ID；VAO：顶点数组对象的ID；EBO：索引缓冲对象的ID
    
    glGenVertexArrays(1, &cubeVAO); //创建1个 顶点数组对象
    glGenBuffers(1, &VBO); //创建1个 顶点缓冲对象
//    glGenBuffers(1, &EBO); //创建1个 索引缓冲对象
    glBindVertexArray(cubeVAO); //绑定VAO
    
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //把顶点缓冲对象绑定到GL_ARRAY_BUFFER（顶点缓冲对象的缓冲类型）目标上
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把 顶点数据vertices 复制到缓冲的内存中
    //glBufferData参数：目标缓冲的类型（顶点缓冲），大小，数据，数据不会或几乎不会改变。
    
    
    //位置属性 position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //告诉OpenGL该如何解析顶点数据
    //参数：Location=0 ，3个值（坐标vec3），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在6个float之后），起始位置的偏移量0
    glEnableVertexAttribArray(0); //启用顶点属性0（顶点的 属性位置 = 0）
    
    //颜色属性 color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //参数：Location=1 ，3个值（法向量），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在6个float之后），起始位置的偏移量3个float
    glEnableVertexAttribArray(1); //启用顶点属性1（顶点的 属性位置 = 1
    
    //纹理属性 texture coords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //参数：Location=1 ，3个值（法向量），数据类型为GL_FLOAT，不标准化，步长（下个顶点组位置数据在6个float之后），起始位置的偏移量3个float
    glEnableVertexAttribArray(2); //启用顶点属性1（顶点的 属性位置 = 1
    
    //-----------------------------------------------------
    // 配置灯的VAO（VBO保持不变;灯光对象的顶点相同，也是3D立方体）
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    
    // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//忽略后三个法向量数据
    glEnableVertexAttribArray(0);
    
    //-----------------------------------------------------
    
    //================================================================================
    
    
    
    
    
    
    
    
    //================================================================================
    // 生成纹理 load and create a texture
    // ----------------------------------------------------------
    unsigned int diffuseMap = loadTexture("/书/OGL_Test/container2.jpg");
    unsigned int specularMap = loadTexture("/书/OGL_Test/container2_specular.jpg");

    
    lightingShader.use(); //use 对应的着色器程序（来设定uniform）
    lightingShader.setInt("material.diffuse", 0); //将要用的纹理单元赋值到material.diffuse这个uniform采样器
    lightingShader.setInt("material.specular", 1); //将要用的纹理单元赋值到material.specular这个uniform采样器
    
    
    
    
    
    

    
    // ------------------------------
    // 渲染循环 render loop
    while (!glfwWindowShouldClose(window)) //每次循环的开始前检查一次GLFW是否被要求退出
    {
        
        
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime(); //获取当前时间
        deltaTime = currentFrame - lastFrame; //上一帧时间间隔
        lastFrame = currentFrame; //保存时间，留在下一帧用
        
        
        // 输入 input
        processInput(window); //输入控制（检查是否按下Esc）
        
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设置清空屏幕后填充的颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空屏幕的 颜色缓冲 和 深度缓冲
        
        
        // 随着时间的推移改变灯的位置值
        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
        
        
        
        // draw
        //=========================================================================
        
        // 在相应的纹理单元上绑定纹理 bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0); // 先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, diffuseMap); //绑定纹理
        glActiveTexture(GL_TEXTURE1); // 先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, specularMap); //绑定纹理
        
        
        
        
        // 绘制物体 
        // ------------
        lightingShader.use(); //use 对应的着色器程序（来设定uniform）
        lightingShader.setVec3("light.position", lightPos); //设定uniform（光源位置）
//        lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setVec3("viewPos", camera.Position); //设定uniform（相机位置）
        
        // light properties
        glm::vec3 lightColor = glm::vec3(1.0f);
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
        
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.9f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响
        lightingShader.setVec3("light.ambient",  ambientColor); // 设定uniform（光源的环境光强度）
        lightingShader.setVec3("light.diffuse",  diffuseColor); // 设定uniform（光源的漫反射强度）
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); //设定uniform（光源的镜面反射强度）
        lightingShader.setFloat("light.constant",  1.0f); //点光源衰减 常数项
        lightingShader.setFloat("light.linear",    0.09f); //点光源衰减 一次项
        lightingShader.setFloat("light.quadratic", 0.032f); //点光源衰减 二次项
        
        
        // 材质属性 material properties（物体在三种光照下反射的颜色）// 改用贴图了
        lightingShader.setFloat("material.shininess", 32.0f); //镜面高光的散射/半径
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); //投影矩阵
        glm::mat4 view = camera.GetViewMatrix(); //观察变换矩阵
        lightingShader.setMat4("projection", projection); //将 投影矩阵 传给着色器
        lightingShader.setMat4("view", view); //将 观察变换矩阵 传给着色器
        
//        glm::mat4 model = glm::mat4(1.0f); //初始化矩阵
//        lightingShader.setMat4("model", model); //将 模型变换矩阵 传给着色器
        
//        glBindVertexArray(cubeVAO); // 在绘制物体前简单地把VAO绑定到希望使用的设定上
//        glDrawArrays(GL_TRIANGLES, 0, 36); // 绘制三角形，起始索引为0，顶点数36
        
        glBindVertexArray(cubeVAO); // 在绘制物体前简单地把VAO绑定到希望使用的设定上
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        //-----------
        
        
        // 绘制光源立方体 also draw the lamp object
        lampShader.use();
        lampShader.setMat4("projection", projection); //将 投影矩阵 传给着色器
        lampShader.setMat4("view", view); //将 观察变换矩阵 传给着色器
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f); //初始化
        model = glm::translate(model, lightPos); //模型变换：位移
        model = glm::scale(model, glm::vec3(0.2f)); // 模型变换：缩放
        lampShader.setMat4("model", model); //将 模型变换矩阵 传给着色器

        glBindVertexArray(lightVAO); // 在绘制物体前简单地把VAO绑定到希望使用的设定上
        glDrawArrays(GL_TRIANGLES, 0, 36); // 绘制三角形，起始索引为0，顶点数36
        
       
        
        //=========================================================================


        
        
        glfwSwapBuffers(window); //交换颜色缓冲，用来绘制，并且将会作为输出显示在屏幕上。
        glfwPollEvents(); //检查有没有触发什么事件
    }
    // -------------------------------
    
    
    
    
    
    //=============================================================================
    // 取消所有资源的分配 optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
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
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// 在每次窗口大小被调整的时候被调用 glfw: whenever the window size changed
// --------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //1,2参数控制窗口左下角的位置。3,4控制渲染窗口的宽度和高度（可以比GLFW的维度小）
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID); //生成 1 个纹理，保存ID到textureID
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0); //加载图片，得到长宽等信息
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID); // 绑定纹理，接下来所有GL_TEXTURE_2D操作都是对此纹理
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); //生成一个纹理
        //参数：纹理目标GL_TEXTURE_2D，Mipmap级别0，纹理存储为RGB格式，宽度，高度，历史遗留总是0，使用RGB值加载，储存为char(byte)数组，图像数据
        glGenerateMipmap(GL_TEXTURE_2D); //自动生成所有需要的多级渐远纹理（Mipmap）
        
        // 设置纹理环绕方式参数 set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // 设置纹理过滤参数 set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//纹理被缩小的时候使用Mipmap
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理被放大的时候使用线性过滤
        
        stbi_image_free(data); //生成了纹理和相应的Mipmap后，释放图像的内存
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    
    return textureID;
    
}

