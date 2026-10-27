#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <functional>
#include <string>

enum class Modifier
{
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Super = 8,
};

enum class Action
{
	Release = 0,
	Press = 1,
	Repeat = 2,
};

enum class ButtonCode
{
	Button_0 = 0,
	Button_1 = 1,
	Button_2 = 2,
	Button_3 = 3,
	Button_4 = 4,
	Button_5 = 5,
	Button_6 = 6,
	Button_7 = 7,
};

enum class KeyCode
{
	UNKNOWN = -1,
	Space = 32,
	APOSTROPHE = 39,
	COMMA = 44,
	MINUS = 45,
	PERIOD = 46,
	SLASH = 47,
	Key0 = 48,
	Key1 = 49,
	Key2 = 50,
	Key3 = 51,
	Key4 = 52,
	Key5 = 53,
	Key6 = 54,
	Key7 = 55,
	Key8 = 56,
	Key9 = 57,
	SEMICOLON = 59,
	EQUAL = 61,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	LEFT_BRACKET = 91,
	BACKSLASH = 92,
	RIGHT_BRACKET = 93,
	GRAVE_ACCENT = 96,
	WORLD_1 = 161,
	WORLD_2 = 162,
	ESCAPE = 256,
	ENTER = 257,
	TAB = 258,
	BACKSPACE = 259,
	INSERT = 260,
	DELETE = 261,
	RIGHT = 262,
	LEFT = 263,
	DOWN = 264,
	UP = 265,
	PAGE_UP = 266,
	PAGE_DOWN = 267,
	HOME = 268,
	END = 269,
	CAPS_LOCK = 280,
	SCROLL_LOCK = 281,
	NUM_LOCK = 282,
	PRINT_SCREEN = 283,
	PAUSE = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,
	KP_0 = 320,
	KP_1 = 321,
	KP_2 = 322,
	KP_3 = 323,
	KP_4 = 324,
	KP_5 = 325,
	KP_6 = 326,
	KP_7 = 327,
	KP_8 = 328,
	KP_9 = 329,
	KP_DECIMAL = 330,
	KP_DIVIDE = 331,
	KP_MULTIPLY = 332,
	KP_SUBTRACT = 333,
	KP_ADD = 334,
	KP_ENTER = 335,
	KP_EQUAL = 336,
	LEFT_SHIFT = 340,
	LEFT_CONTROL = 341,
	LEFT_ALT = 342,
	LEFT_SUPER = 343,
	RIGHT_SHIFT = 344,
	RIGHT_CONTROL = 345,
	RIGHT_ALT = 346,
	RIGHT_SUPER = 347,
	MENU = 348,
};

class ViewerWindow
{
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	friend void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	friend void scrollCallback(GLFWwindow* window, double xpos, double ypos);

public:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	using CursorPosCallback = std::function<void(double, double)>;
	using MouseCallback = std::function<void(ButtonCode, Action, Modifier, double, double)>;
	using ScrollCallback = std::function<void(double, double)>;

	ViewerWindow(const std::string& title, uint32_t width, uint32_t height);
	~ViewerWindow();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	void setKeyCallback(const KeyCallback& callback);
	void setCursorPosCallback(const CursorPosCallback& callback);
	void setMouseCallback(const MouseCallback& callback);
	void setScrollCallback(const ScrollCallback& callback);

	GLFWwindow* getGLFWHandle() const;

private:
	GLFWwindow* m_ptrHandle;
	uint32_t m_width;
	uint32_t m_height;

	KeyCallback m_keyClBck;
	CursorPosCallback m_cursorPosClBck;
	MouseCallback m_mouseClBck;
	ScrollCallback m_scrollClBck;
};