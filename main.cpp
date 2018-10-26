/*
 * |-----------------------------------------------------
 * | [Program] main.cpp
 * |-----------------------------------------------------
 * | 說明     : 主程式
 * | 來源     ：中譯   https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/
 * |           原文   https://learnopengl.com/Getting-started/Shaders
 * |           原代碼 https://learnopengl.com/code_viewer.php?code=getting-started/shaders-using-object
 * |
 */

//基本IO函式庫
#include <iostream>

//GLEW 相關函式庫引入
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

//GLFW 相關函式庫引入
#include <GLFW/glfw3.h>

//其他部份
#include "./Shader.h"


///視窗大小
const GLuint WIDTH  = 600,
             HEIGHT = 600;

//main函數，從這裡我們啟動應用程序並運行loop
int main()
{
    //初始化 GLFW
    glfwInit();

    //設置GLFW所需的所有選項
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //創建一個GLFWwindow對象，我們可以將它用於GLFW的功能
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "[程式標題]", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    //將此設置為true，以便GLEW知道使用現代方法檢索函數指針和擴展
    glewExperimental = GL_TRUE;
    
    //初始化GLEW以設置OpenGL函數指針
    glewInit();
    
    /*
    //制定畫面視圖大小 X偏移量,Y偏移量,縮放（目標收放大小/實際的WIDTH）,縮放（目標收放大小/實際的HEIGHT）
    glViewport(0, 0, WIDTH, HEIGHT);
    */

    //構建並編譯著色器程序
    Shader ourShader("shaders/vert_shader.glsl", "shaders/frag_shader.glsl");

    //設置頂點數據（和緩衝區）和屬性指針
    GLfloat vertices[] = {
        //位置                //色彩
       -0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // 1
       -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // 2
        0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  // 3
       -0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // 1
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,  // 2
        0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  // 3
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //首先綁定Vertex Array對象，然後綁定並設置頂點緩衝區(vertex buffer)和屬性指針。
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //位置屬性（對應Location=0 、取得3個、屬性、旗標、大小、偏移量0）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //顏色屬性（對應Location=1 、取得3個、屬性、旗標、大小、偏移量3）
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); //取消綁定VAO


    //當視窗未關閉前，執行迴圈
    while (!glfwWindowShouldClose(window))
    {
        //檢查是否已激活任何事件（按下鍵，鼠標移動等）並調用相應的響應函數
        //刪除，會使得我們對程式的事件操作都無法被操作，如：關閉視窗時，是無法回應，陷入死循環。
        glfwPollEvents();

        //Render
        //設定背景，再清除顏色緩衝區
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //使用Shader ourShader
        ourShader.Use();
      
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6); //原始為 glDrawArrays(GL_TRIANGLES, 0, 3); 要n>=1且3*n點才能形成三角形，否則總點數m%3的餘數不會被繪製
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    //一旦他們的資源耗盡，就適當地取消所有資源的分配
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //終止GLFW，清除GLFW分配的所有資源。
    glfwTerminate();
    return 0;
}
