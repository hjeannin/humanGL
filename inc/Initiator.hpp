#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# include <iostream>
# include <SFML/OpenGL.hpp>
# include "Mat4.hpp"
# include "Shaders.hpp"

class Initiator
{

private:
	int			_status;

public:
	GLuint			vao;
	GLuint			vbos[2];
	int				vertices_size;
	int				vertices_num_elem;
	GLfloat			*vertices_array;
	int				faces_size;
	int				faces_num_elem;
	GLuint			*faces_array;

	Shaders			shaders;
	GLuint			program;

	GLuint			res_x;
	GLuint			res_y;

	GLfloat			translate[3];
	GLfloat			rotate[3];
	GLfloat			scale;

	Mat4<GLfloat>	proj_matrix;
	Mat4<GLfloat>	view_matrix;
	Mat4<GLfloat>	trans_matrix;
	Mat4<GLfloat>	rot_matrix;
	Mat4<GLfloat>	scale_matrix;

	GLuint			position_loc;
	GLuint			proj_loc;
	GLuint			view_loc;
	GLuint			trans_loc;
	GLuint			rot_loc;
	GLuint			scale_loc;

	Initiator(void);
	Initiator(int _status);
	Initiator(Initiator const &src);
	~Initiator(void);

	void		initData(void);

	void		genMatrices(void);
	void		genShaders(void);
	void		getLocations(void);
	void		createImage(void);
	bool		drawImage(void);

	void		checkGlError(std::string file, int line);

	int			getStatus(void) const;
	
	void		setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp);
	void		setViewMatrix(void);
	void		setModelMatrix(void);

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
