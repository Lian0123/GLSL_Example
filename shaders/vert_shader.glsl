/*
 * |-----------------------------------------------------
 * | [Program] vert_shader.glsl
 * |-----------------------------------------------------
 * | 說明     : 頂點著色器
 * | 來源     ：中譯   https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/
 * |           原文   https://learnopengl.com/Getting-started/Shaders
 * |           原代碼 https://learnopengl.com/code_viewer.php?type=vertex&code=getting-started/basic
 * |
 */

#version 330 core
layout (location = 0) in vec3 position; //位置變量的屬性位置值為 0
layout (location = 1) in vec3 color;    //颜色变量的属性位置值为 1

out vec3 ourColor; //向Fragment Shader輸出一個顏色

void main(){
    gl_Position = vec4(position, 1.0f);
    ourColor = color;
}