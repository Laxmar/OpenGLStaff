#pragma once
#include <glm/detail/type_vec4.hpp>

class Color
{
public:
	Color();
	Color(glm::vec4& color);
	~Color();
	
	static Color& red();
	static Color& black();
	static Color& yellow();
	static Color& blue();
	static Color& green();
	static Color& pink();
	static Color& oragne();

	glm::vec4 value;

	const static glm::vec4 a = glm::vec4(1, 1, 1,1);
private:
};

