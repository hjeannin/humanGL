#ifndef SHADERS_HPP
# define SHADERS_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <SFML/OpenGL.hpp>

class Shaders
{

public:
	GLuint		vertex_shader;
	GLuint		geometry_shader;
	GLuint		fragment_shader;

	Shaders(void);
	Shaders(Shaders const &src);
	~Shaders(void);

	void		load(void);
	bool		loadShader(GLenum type, std::string file_name, GLuint *current_shader);

	void		compile(void);
	bool		compileShader(GLuint *current_shader);

	Shaders		&operator=(Shaders const &rhs);
};

#endif
