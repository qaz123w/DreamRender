#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <cctype>
#include <spdlog/spdlog.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <utils.h>

NAMESPACE_BEGIN(dream)

// Use default logger for now...
#define DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger(), __VA_ARGS__)
#define INFO(...)  SPDLOG_LOGGER_INFO(spdlog::default_logger(), __VA_ARGS__)
#define WARN(...)  SPDLOG_LOGGER_WARN(spdlog::default_logger(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger(), __VA_ARGS__)

class Console {
public:
	Console();
	~Console();

	// Portable helpers
	static int Stricmp(const char* s1, const char* s2);
	static int Strnicmp(const char* s1, const char* s2, int n);
	static char* Strdup(const char* s);
	static void Strtrim(char* s);

	void ClearLog();
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	void Draw(const char* title, bool* p_open);
	void ExecCommand(const char* command_line);

	// In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);

	int TextEditCallback(ImGuiInputTextCallbackData* data);

public:
	char input_buffer_[256];
	ImVector<char*> items_;
	ImVector<const char*> commands_;
	ImVector<char*> history_;
	int history_pos_;  // -1: new line, 0..history_.Size-1 browsing history_.
	ImGuiTextFilter filter_;
	bool auto_scroll_;
	bool scroll_to_bottom_;

};

NAMESPACE_END(dream)