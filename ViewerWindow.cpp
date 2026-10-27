#include "ViewerWindow.h"
#include "glad/glad.h"

#include <cstdlib>
#include <iostream>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ViewerWindow* wnd = reinterpret_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
	if (wnd && wnd->m_keyClBck)
		wnd->m_keyClBck(static_cast<KeyCode>(key), static_cast<Action>(action), static_cast<Modifier>(mods));
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	ViewerWindow* wnd = reinterpret_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
	if (wnd && wnd->m_mouseClBck)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		wnd->m_mouseClBck(static_cast<ButtonCode>(button),
						static_cast<Action>(action),
						static_cast<Modifier>(mods), xpos, ypos);
	}
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	ViewerWindow* wnd = reinterpret_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
	if (wnd && wnd->m_cursorPosClBck)
		wnd->m_cursorPosClBck(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ViewerWindow* wnd = reinterpret_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
	if (wnd && wnd->m_scrollClBck)
		wnd->m_scrollClBck(xoffset, yoffset);
}

ViewerWindow::ViewerWindow(const std::string& title, uint32_t width, uint32_t height)
	: m_width(width)
	, m_height(height)
{
	if (glfwInit() == GLFW_FALSE)
	{
		const char* errorDesc = nullptr;
		glfwGetError(&errorDesc);
		std::cerr << "Не вдалося ініціалізувати GLFW";
		if (errorDesc)
			std::cerr << ": " << errorDesc;
		std::cerr << "\n";
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_ptrHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_ptrHandle)
	{
		std::cerr << "Не вдалося створити вікно\n";
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_ptrHandle);

	static bool initGLAD = false;
	if (!initGLAD)
	{
		initGLAD = true;
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	glfwSetWindowUserPointer(m_ptrHandle, this);

	glfwSetKeyCallback(m_ptrHandle, &keyCallback);
	glfwSetMouseButtonCallback(m_ptrHandle, &mouseButtonCallback);
	glfwSetCursorPosCallback(m_ptrHandle, &cursorCallback);
	glfwSetScrollCallback(m_ptrHandle, &scrollCallback);
}

ViewerWindow::~ViewerWindow()
{
	glfwDestroyWindow(m_ptrHandle);
}

uint32_t ViewerWindow::getWidth() const
{
	return m_width;
}

uint32_t ViewerWindow::getHeight() const
{
	return m_height;
}

void ViewerWindow::setKeyCallback(const KeyCallback& callback)
{
	m_keyClBck = callback;
}

void ViewerWindow::setCursorPosCallback(const CursorPosCallback& callback)
{
	m_cursorPosClBck = callback;
}

void ViewerWindow::setMouseCallback(const MouseCallback& callback)
{
	m_mouseClBck = callback;
}

void ViewerWindow::setScrollCallback(const ScrollCallback& callback)
{
	m_scrollClBck = callback;
}

GLFWwindow* ViewerWindow::getGLFWHandle() const
{
	return m_ptrHandle;
}