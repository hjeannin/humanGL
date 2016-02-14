#ifndef TRANSFORMATION_HPP
# define TRANSFORMATION_HPP

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

# define T_SCALE		201
# define T_TRANSLATE	202
# define T_ROTATE		203

# include <glfw3.h>
# include "Mat4.hpp"

class Transformation
{
private:
	int			_transformation_type;
	GLfloat		_x;
	GLfloat		_y;
	GLfloat		_z;
	GLfloat		_angle;

public:
	Transformation(void);
	Transformation(int tt, GLfloat x, GLfloat y, GLfloat z, GLfloat angle = 0.0f);
	~Transformation(void);

	void		setAngle(GLfloat a);
	void		run(Mat4<GLfloat> *matrix);
};

#endif