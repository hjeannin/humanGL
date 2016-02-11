#ifndef MODEL_HPP
# define MODEL_HPP

# if defined(__APPLE_CC__)
#  ifndef GLFW_INCLUDE_GLCOREARB
#   define GLFW_INCLUDE_GLCOREARB
#  endif
#  ifndef GLFW_INCLUDE_GLEXT
#   define GLFW_INCLUDE_GLEXT
#  endif
# else
#  define GL_GLEXT_PROTOTYPES
# endif

# define TYPE_CUBE		42
# define TYPE_SPHERE	43

# include <glfw3.h>

# include "Mat4.hpp"

class Model
{
private:
	GLuint			_part_count;

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

	struct Part
	{
		Mat4<GLfloat>	matrix;
		GLuint			num_vertices_before = 0;
		GLuint			num_faces_before = 0;
		GLuint			v_mem_size;
		GLuint			v_num_elem;
		Point			*v_array;
		GLuint			f_mem_size;
		GLuint			f_num_elem;
		GLuint			*f_array;
		int				type;		
	};

	Part			*part;

	Model(void);
	Model(GLuint part_count);
	~Model(void);

	GLuint		getPartCount(void) const;
	
	void		genCubes(void);
	void		generateCube(Part *current_part, int nfb, int nvb);
	void		changePartColor(GLuint id, GLuint color);
	// void		generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b);

};

#endif