/*
 * |-----------------------------------------------------
 * | [Program] Shader.h
 * |-----------------------------------------------------
 * | 說明     : Class Shader
 * | 來源     ：中譯   https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/05%20Shaders/
 * |           原文   https://learnopengl.com/Getting-started/Shaders
 * |           原代碼 https://learnopengl.com/code_viewer.php?type=header&code=shader
 * |
 */
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

/*
 *
 * |-----------------------------------------------------
 * | [Class] Shader
 * |-----------------------------------------------------
 * | 程式用途  :  處理Shader的程序讀取與連結到我們的程序上
 * | 全域變數  :  Program
 * | 全域函數  :  Shader(...) : 建構子
 * |             void Use()  : 使用當前的shader的方法
 * |
 */
class Shader{
    public:
        //[public][Value]glew庫Create的Program
        GLuint Program;

        //[public][建構子]構造函數動態生成著色器
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
            //1.從filePath中vertex/fragment 
            //filePath中vertex位置即為vertexPath傳入之位置
            //filePath中fragment位置即為vertexPath傳入之位置

            string vertexCode;
            string fragmentCode;
            ifstream vShaderFile;
            ifstream fShaderFile;

            //確保ifstream對象可以拋出異常（使用try...catch實做）
            vShaderFile.exceptions (ifstream::badbit);
            fShaderFile.exceptions (ifstream::badbit);
            try{
                //開啟檔案
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                stringstream vShaderStream, fShaderStream;

                //將讀取文件的buffer內容讀入至資料流中
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                //關閉文件處理程序
                vShaderFile.close();
                fShaderFile.close();

                //將讀取的資料流轉換為字符串
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();

            }catch (ifstream::failure e){
                //IO錯誤時則輸出錯誤訊息
                cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
            }

            const GLchar* vShaderCode = vertexCode.c_str();
            const GLchar* fShaderCode = fragmentCode.c_str();

            //2.編譯著色器
            GLuint vertex, fragment;
            GLint success;
            GLchar infoLog[512];

            //Vertex Shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);

            //如果Vertex Shader編譯錯誤，輸出錯誤資訊
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

            if (!success){
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
            }

            //Fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);

            //如果Fragment Shader編譯錯誤，輸出錯誤資訊
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success){
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
            }

            // Shader Program
            this->Program = glCreateProgram();
            glAttachShader(this->Program, vertex);
            glAttachShader(this->Program, fragment);
            glLinkProgram(this->Program);
            
            //如果在輸出linking時發生錯誤，則輸出錯誤資訊
            glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
            if (!success){
                glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
                cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
            }
            
            //刪除shaders，因為它們現在已鏈接到我們的程序中，不再需要
            glDeleteShader(vertex);
            glDeleteShader(fragment);

        }

        //[public][function] 使用當前的shader
        void Use(){ 
            glUseProgram(this->Program); 
        }
};

#endif
