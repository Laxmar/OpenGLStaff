#include "..\include\Color.h"

Color::Color()
{
	value = glm::vec4(0, 0, 0, 0);
}

Color::Color(glm::vec4& color)
{
	value = color;
}


Color::~Color()
{
}


Color & Color::red()
{
	static Color c = Color(glm::vec4(1, 0, 0, 1)); return c;
};

Color & Color::black()
{
	static Color c = Color(glm::vec4(1, 1, 1, 1)); return c;
}

Color& Color::yellow()
{
	static Color c = Color(glm::vec4(1, 1, 0, 1)); return c;
}

Color& Color::blue()
{
	static Color c = Color(glm::vec4(0, 0, 1, 1)); return c;
}

Color& Color::green()
{
	static Color c = Color(glm::vec4(0, 1, 0, 1)); return c;
}

Color& Color::pink()
{
	static Color c = Color(glm::vec4(1, 0, 0.5f, 1)); return c;
}

Color& Color::oragne()
{
	static Color c = Color(glm::vec4(1, 0.45f, 0, 1)); return c;
};
