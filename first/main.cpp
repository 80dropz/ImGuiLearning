#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Windows.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>





const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, aPos.y,size *aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";


float couting;

bool drawtriangle = true;
void Subscribebutton();
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat Vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 3 / 4, 0.0f
	};


	GLFWwindow* window = glfwCreateWindow(800, 800, "Testing", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertexShader);

	GLuint Fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(Fragmentshader);

	GLuint shaderprgram = glCreateProgram();

	glAttachShader(shaderprgram, VertexShader);
	glAttachShader(shaderprgram, Fragmentshader);
	glLinkProgram(shaderprgram);

	glDeleteShader(VertexShader);
	glDeleteShader(Fragmentshader);



	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);






	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	float size = 1.0f;
	float color[4] = {0.8f, 0.3f, 0.02f, 1.0f};
	glUseProgram(shaderprgram);
	glUniform1f(glGetUniformLocation(shaderprgram, "size"), size);
	glUniform4f(glGetUniformLocation(shaderprgram, "color"), color[0], color[1], color[2], color[3]);
	int count = 0;
	std::string CurStyleColor = "Light";
	std::string StyleColor = "Light";
	std::string StyleColorFin = StyleColor + " Mode";
	while (!glfwWindowShouldClose(window))
	{
		// Clear the OpenGL buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Background color: black

		// Start a new ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Create ImGui GUI
		ImGui::SetCursorScreenPos(ImVec2(300.0f, 400.0f));
		ImGui::SetNextWindowSize(ImVec2(400, 300));
		ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_Once);
		ImGui::Begin("This is a test window");
		ImGui::Text("Testing");
		ImGui::SliderFloat("Cout", &couting, 0.0f, 10.0f);
		ImGui::Text("Cout: %.3f", couting);
		ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		ImGui::ColorEdit4("Color", color);

		ImGui::End();

		// Render ImGui data
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderprgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void testing()
{
	std::cout << "Testing" << "\n";
}


void Subscribebutton() 
{
	LPCTSTR subscribeurl = L"https://youtube.com";
	ShellExecute(NULL, L"open", subscribeurl, NULL, NULL, SW_SHOWNORMAL);
}
