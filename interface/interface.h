#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <utils.h>
#include <console.h>

NAMESPACE_BEGIN(dream)

class Interface {
public:
	Interface(float width = 2048.0f, float height = 1024.0f);
	~Interface();

	void Render();

protected:
	void RegisterLogCallback();
	void ConfigureAndSubmitDockspace();
	void SelectableOptionFromFlag(const char* name, bool& flag);
	void CreateMenuBar();
	void ApplyDarkTheme();

public:
	GLFWwindow* window_;
	std::unique_ptr<Console> console_;
	float width_;
	float height_;
};

NAMESPACE_END(dream)