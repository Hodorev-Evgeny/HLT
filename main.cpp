#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
    //инциализация
    glfwInit();

    // настройка
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // задаём кординаты
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) / 3, 0.
    };

    // создания окно
    GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    // отлов ошибки
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // привязка opengl к окну

    gladLoadGL(); // инциализация glad
    glViewport(0, 0, 800, 800); // настройка корд

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // содаём шейдер
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // данные шейдера
    glCompileShader(vertexShader); //применения настроек

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource , NULL);
    glCompileShader(fragmentShader);

    GLuint ShaderProgram = glCreateProgram(); // создания програмы через которую и будет применять шейдеры
    glAttachShader(ShaderProgram, vertexShader); // применения через програму
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram); // передача ссылку на програму

    // очистка пямяти послек применения шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // настройка хронений кординат в видеокарте
    // vao кусок памяти в видео карте
    // vbo контексное меню, настройки
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // привязка
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // копирования данных
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // обяснения данных(видеокарта не знает что значут числа которые были переданы)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //развяка
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // настройка света
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // очистка буфера цвета(можно чистить и другие)
    glfwSwapBuffers(window); // замена нынешнего кадра на отрисованый

    while (!glfwWindowShouldClose(window)) // цыкл что бы окно не закрывалось
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(ShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents(); // оброботчик действия
    }

    // очистка памяти
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}