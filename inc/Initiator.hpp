#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# ifndef M_PI
#  define M_PI		3.1415926535897932384626433832795
# endif

# define TYPE_CUBE		42
# define TYPE_SPHERE	43

# include <iostream>
# include "Shaders.hpp"
# include "Mat4.hpp"
# include "StackMat4.hpp"
# include "Camera.hpp"
# include "Human.hpp"

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

	struct Model
	{
		int				v_mem_size;
		int				v_num_elem;
		Point			*v_array;
		int				f_mem_size;
		int				f_num_elem;
		GLuint			*f_array;
		Mat4<GLfloat>	m_matrix;
		GLuint			num_faces_before = 0;
		GLuint			num_vertices_before = 0;
		int				type;		
	};

	GLFWwindow		*window;
	Camera			camera;
	GLuint			vao;
	GLuint			vbos[2];
	Model			*models;
	int				model_count;
	int				vertices_mem_size;
	int				vertices_num_elem;
	Point			*vertices_array;
	int				faces_mem_size;
	int				faces_num_elem;
	GLuint			*faces_array;

	Shaders			shaders;
	GLuint			program;

	Human			*human;

	GLuint			res_x;
	GLuint			res_y;

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
	void		generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b);
	void		generateCube(Model *model, int nfb, int nvb, int color = 0x00000000);

	void		LoadModels(void);
	void		ConbineModels(void);
	void		createImage(void);
	bool		drawImage(void);

	void		checkGlError(std::string file, int line);

	int			getStatus(void) const;
	void		setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp);
	void		setViewMatrix(void);
	void		setModelMatrix(void);

		// DEBUG AND TEST //

	void		printArray(GLuint *a, int size);
	void		printPointArray(Point *a, int size);
	void		debugMatrix(void);

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
