# include "Transformation.hpp"

Transformation::Transformation(void) : _transformation_type(0), _x(0.0f), _y(0.0f), _z(0.0f), _angle(0.0f), _start_frame(0), _end_frame(0)
{
	return;
}

Transformation::Transformation(int tt, GLfloat x, GLfloat y, GLfloat z, GLfloat angle, GLuint sf, GLuint ef) :
	_transformation_type(tt), _x(x), _y(y), _z(z), _angle(angle), _start_frame(sf), _end_frame(ef)
{
	return;
}

Transformation::~Transformation(void)
{
	return;
}

void
Transformation::runSetup(Mat4<GLfloat> *matrix)
{
	if (_start_frame - _end_frame == 0)
	{
		if (_transformation_type == T_TRANSLATE)
		{
			matrix->translate(_x, _y, _z);
		}
		else if (_transformation_type == T_ROTATE)
		{
			matrix->rotate(_angle, _x, _y, _z);
		}
		else if (_transformation_type == T_SCALE)
		{
			matrix->scale(_x, _y, _z);
		}
	}		
	return;
}

void
Transformation::runAnimation(Mat4<GLfloat> *matrix)
{
	if (_transformation_type == T_TRANSLATE)
	{
		matrix->translate(_x, _y, _z);
	}
	else if (_transformation_type == T_ROTATE)
	{
		matrix->rotate(_angle, _x, _y, _z);
	}
	else if (_transformation_type == T_SCALE)
	{
		matrix->scale(_x, _y, _z);
	}		
	return;
}

void
Transformation::setAngle(GLfloat a)
{
	if (this->_transformation_type == T_ROTATE)
	{
		this->_angle = a;
	}
}

void
Transformation::setX(GLfloat x)
{
	if (this->_transformation_type == T_TRANSLATE)
	{
		this->_x = x;
	}
}

void
Transformation::setY(GLfloat y)
{
	if (this->_transformation_type == T_TRANSLATE)
	{
		this->_y = y;
	}
}