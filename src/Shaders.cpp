#include "Shaders.hpp"

Shaders::Shaders(void)
{
	return;
}

Shaders::Shaders(Shaders const &src)
{
	*this = src;
	return;
}

Shaders::~Shaders(void)
{
	return;
}

void
Shaders::load(void)
{
	if (loadShader(GL_VERTEX_SHADER, "./shaders/vertex_shader.gls", &this->vertex_shader) == false)
	{
		std::cout << "Vertex shader failed to load." << std::endl;
	}
// 	if (loadShader(GL_GEOMETRY_SHADER, "./shaders/geometry_shader.gls", &this->geometry_shader) == false)
// 	{
// 		std::cout << "Geometry shader failed to load." << std::endl;
// 	}
	if (loadShader(GL_FRAGMENT_SHADER, "./shaders/fragment_shader.gls", &this->fragment_shader) == false)
	{
		std::cout << "Fragment shader failed to load." << std::endl;
	}
}

bool
Shaders::loadShader(GLenum type, std::string file_name, GLuint *current_shader)
{
	std::ifstream		source_file(file_name.c_str());
	std::string			shader_string;
	const GLchar		*shader_source;

	if (!source_file)
		return (false);

	shader_string.assign(std::istreambuf_iterator<char>(source_file),
						 std::istreambuf_iterator<char>());
	
	if ((*current_shader = glCreateShader(type)) == 0)
		return (false);

	shader_source = shader_string.c_str();
	glShaderSource(*current_shader, 1, (const GLchar**)&shader_source, NULL);

	return (true);
}

void
Shaders::compile(void)
{
	if (compileShader(&this->vertex_shader) == false)
		std::cout << "Vertex shader failed to compile." << std::endl;
// 	if (compileShader(this->geometry_shader) == false)
// 		std::cout << "Geometry shader failed to compile." << std::endl;
	if (compileShader(&this->fragment_shader) == false)
		std::cout << "Fragment shader failed to compile." << std::endl;
}

bool
Shaders::compileShader(GLuint *current_shader)
{
	GLint		status;

	status = 0;
	glCompileShader(*current_shader);
	std::cout << "CURRENT SHADER FUCKING ID = " << *current_shader << std::endl;
	glGetShaderiv(*current_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint	max_length = 0;
		glGetShaderiv(*current_shader, GL_INFO_LOG_LENGTH, &max_length);
		std::cout << "SHADER ERROR FUCKING LENGTH = " << max_length << std::endl;
		std::vector<GLchar> comp_log(max_length);
		glGetShaderInfoLog(*current_shader, max_length, &max_length, &comp_log[0]);
		
		for (std::vector<char>::const_iterator i = comp_log.begin() ; i != comp_log.end() ; ++i)
		{
			std::cout << *i << std::endl;
		}

		glDeleteShader(*current_shader);
		return (false);
	}
	return (true);
}

Shaders
&Shaders::operator=(Shaders const &rhs)
{
	this->vertex_shader = rhs.vertex_shader;
	this->geometry_shader = rhs.geometry_shader;
	this->fragment_shader = rhs.fragment_shader;
	return *this;
}
