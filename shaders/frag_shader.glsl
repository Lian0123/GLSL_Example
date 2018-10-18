/*
 * |-----------------------------------------------------
 * | [Program] frag_shader.glsl
 * |-----------------------------------------------------
 * | 說明     : 片段著色器
 * | 來源     ：中譯   https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/
 * |           原文   https://learnopengl.com/Getting-started/Shaders
 * |           原代碼 https://learnopengl.com/code_viewer.php?type=fragment&code=getting-started/basic
 * |
 */

#version 330 core
in vec3 ourColor;  //接收Fragment Shader的輸出一個顏色

out vec4 color; //Vertex Shader輸出的變量名可以任意命名，類型必須是vec4

void main(){
    color = vec4(ourColor, 1.0f); //ourColor : R,G,B
}