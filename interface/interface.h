#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <utils.h>
#include <console.h>

NAMESPACE_BEGIN(dream)

class Interface {
public:
	Interface(int width = 2048, int height = 1024);
	~Interface();

	void Render();

protected:
	void RegisterLogCallback();
	void ConfigureAndSubmitDockspace(int display_w, int display_h);
	void SelectableOptionFromFlag(const char* name, bool& flag);
	void CreateMenuBar();
	void ApplyDarkTheme();

public:
	GLFWwindow* window_;
	std::unique_ptr<Console> console_;
	int width_;
	int height_;
};

NAMESPACE_END(dream)