# include "Transformation.hpp"

Transformation::Transformation(void)
{
	return;
}

Transformation::Transformation(int transformation_type, Mat4<GLfloat> *matrix, GLfloat x, GLfloat y, GLfloat z, GLfloat angle)
{
	if (transformation_type == T_SCALE)
	{
		matrix->scale(x, y, z);
	}
	else if (transformation_type == T_TRANSLATE)
	{
		matrix->translate(x, y, z);
	}
	else if (transformation_type == T_ROTATE)
	{
		matrix->rotate(angle, x, y, z);
	}
	return;
}

Transformation::~Transformation(void)
{
	return;
}