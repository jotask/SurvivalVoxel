#include <stdio.h>

#include "engine.h"

int main()
{

    glm::vec3 vector(1, 0, 1);
    printf("%f %f %f\n", vector.x, vector.y, vector.z);

    if (glfwInit() == false)
    {
        fprintf(stderr, "Failed to init GLFW\n");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    printf("GLFW version: %s\n", glfwGetVersionString());

    GLFWwindow* window = glfwCreateWindow(500, 300, "Window Title", NULL, NULL);

    if (window == nullptr)
    {
        fprintf(stderr, "Failed to create GLFW window");
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        fprintf(stderr, "Failed to init GLAD\n");
        return EXIT_FAILURE;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;

    while (glfwWindowShouldClose(window) == false)
    {

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window == true)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::Render();
        int display_w = 0;
        int display_h = 0;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return EXIT_SUCCESS;

}
