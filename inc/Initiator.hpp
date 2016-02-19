#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# ifndef M_PI
#  define M_PI		3.1415926535897932384626433832795
# endif

# include <iostream>
# include "Shaders.hpp"
# include "Mat4.hpp"
# include "StackMat4.hpp"
# include "Camera.hpp"
# include "Model.hpp"

class Initiator
{

private:
	int			_status;

public:
	int				isSet;
	GLFWwindow		*window;
	Camera			camera;
	GLuint			vao;
	GLuint			vbos[2];
	GLuint			vertices_mem_size;
	GLuint			vertices_num_elem;
	Model::Point	*vertices_array;
	GLuint			faces_mem_size;
	GLuint			faces_num_elem;
	GLuint			*faces_array;

	Shaders			shaders;
	GLuint			program;

	Model			*mod;

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

	void		createImage(void);
	void		ConbineParts(std::vector<Model::Part> &part, GLuint part_count);
	void		LoadModel(void);
	bool		drawModel(std::vector<Model::Part> &part, GLuint part_count);

	void		checkGlError(std::string file, int line);

	int			getStatus(void) const;
	void		setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp);
	void		setViewMatrix(void);
	void		setModelMatrix(void);

		// DEBUG AND TEST //

	void		printArray(GLuint *a, int size);
	void		printPointArray(Model::Point *a, int size);

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
