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

# define CUBE		101
# define SPHERE		102

//HUMAN
typedef enum
{
	BODY,
	HEAD,

	RS,
	RRA,
	RE,
	RFA,
	RH,

	LS,
	LRA,
	LE,
	LFA,
	LH,

	RB,
	RRL,
	RK,
	RFL,
	RF,

	LB,
	LRL,
	LK,
	LFL,
	LF,

	GRASS
}			humanParts;

# define NONE		-1
# define RED		0
# define GREEN		1
# define BLUE		2
# define ORANGE		3
# define WHITE		4

# define GLOBAL		0xFFFFFFFF

# include <glfw3.h>
# include <iostream>
# include <map>
# include <vector>
# include "Mat4.hpp"
# include "Anim.hpp"

class Model
{
private:
	GLuint			_part_count = 0;

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
		int				shape;		
	};

	GLuint					frame = 0;
	GLuint					max_frame = 240;
	GLuint					global_frame = 0;
	std::vector<Part>		part;
	std::vector<Anim *>		anim_vector;

	Model(void);
	~Model(void);

	GLuint		getPartCount(void) const;
	
	void		setNeededPart(GLuint n);
	void		changePartColor(int id, GLuint color);
	Mat4<GLfloat>	*findMatrix(int index);
	void		runAnimVectorAnim(void);
	void		animate(void);
	void		reset(void);

	void		buildPouet(void);
	void		buildHuman(void);
	void		humanWalk(void);
	void		humanBackFlip(void);

	void		buildWTF(void);
	void		multiAnim(void);

	void		genCubes(void);
	void		generateCube(Part *current_part, int nfb, int nvb);
	// void		generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b);

};

#endif