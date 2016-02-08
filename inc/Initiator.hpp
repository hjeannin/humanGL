#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# ifndef M_PI
#  define M_PI		3.1415926535897932384626433832795
# endif

# include <iostream>
# include "Shaders.hpp"
# include "Mat4.hpp"

class Initiator
{

private:
	int			_status;

public:
	struct Point
	{
		GLfloat		x;
		GLfloat		y;
		GLfloat		z;
		GLubyte		r;
		GLubyte		g;
		GLubyte		b;
		GLubyte		a;
	};

	GLFWwindow		*window;
	GLuint			vao;
	GLuint			vbos[2];
	int				vertices_mem_size;
	int				vertices_num_elem;
	Point			*vertices_array;
	int				faces_mem_size;
	int				faces_num_elem;
	GLuint			*faces_array;

	Shaders			shaders;
	GLuint			program;

	GLuint			res_x;
	GLuint			res_y;

	GLfloat			cam_pos[3];

	GLfloat			translate[3];
	GLfloat			rotate[3];
	GLfloat			scale;

	Mat4<GLfloat>	proj_matrix;
	Mat4<GLfloat>	view_matrix;
	Mat4<GLfloat>	model_matrix;

	GLuint			position_loc;
	GLuint			proj_loc;
	GLuint			view_loc;
	GLuint			model_loc;
	GLuint			color_loc;

	Initiator(void);
	Initiator(int _status);
	Initiator(Initiator const &src);
	~Initiator(void);

	void		initData(void);

	void		genMatrices(void);
	void		getLocations(void);
	void		genShaders(void);
	void		generateRandomModel(void);
	void		generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b);

	void		LoadModel(Point *model_vertices_array, GLuint *model_faces_array);
	void		createCBImage(void);
	void		createImage(void);
	bool		drawImage(void);

	void		checkGlError(std::string file, int line);

	int			getStatus(void) const;
	void		setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp);
	void		setViewMatrix(void);
	void		setModelMatrix(void);

	void		printArray(GLuint *a, int size);
	void		printPointArray(Point *a, int size);
	void		debugMatrix(void);

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
