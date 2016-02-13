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
public:
	Transformation(void);
	Transformation(int transformation_type, Mat4<GLfloat> *matrix, GLfloat x, GLfloat y, GLfloat z, GLfloat angle = 0.0f);
	~Transformation(void);
};

#endif