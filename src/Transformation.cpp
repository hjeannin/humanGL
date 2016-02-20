# include "Transformation.hpp"

Transformation::Transformation(void) : _transformation_type(0), _x(0.0f), _y(0.0f), _z(0.0f), _angle(0.0f), _start_frame(0), _end_frame(0)
{
	this->_frame_range = 0.0f;
	return;
}

Transformation::Transformation(int tt, GLfloat x, GLfloat y, GLfloat z, GLfloat angle, GLuint sf, GLuint ef) :
	_transformation_type(tt), _x(x), _y(y), _z(z), _angle(angle), _start_frame(sf), _end_frame(ef)
{
	if (_start_frame == 0xFFFFFFFF && _end_frame == 0xFFFFFFFF)
	{
		this->_frame_range = -1.0f;
	}
	else
	{
		this->_frame_range = _end_frame - _start_frame;
	}
	return;
}

Transformation::~Transformation(void)
{
	return;
}

void
Transformation::runSetup(Mat4<GLfloat> *matrix)
{
	if (_frame_range == 0.0f)
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
}

void
Transformation::runAnimation(Mat4<GLfloat> *matrix, GLuint current_frame, GLuint global_frame)
{
	if (_frame_range > 0.0f)
	{
		if (current_frame >= _start_frame && current_frame < _end_frame)
		{
			if (_transformation_type == T_TRANSLATE)
			{
				matrix->translate(	_x / _frame_range * (current_frame - _start_frame),
									_y / _frame_range * (current_frame - _start_frame),
									_z / _frame_range * (current_frame - _start_frame));
			}
			else if (_transformation_type == T_ROTATE)
			{
				matrix->rotate(_angle / _frame_range * (current_frame - _start_frame), _x, _y, _z);
			}
			else if (_transformation_type == T_SCALE)
			{
				matrix->scale(	_x / _frame_range * (current_frame - _start_frame),
								_y / _frame_range * (current_frame - _start_frame),
								_z / _frame_range * (current_frame - _start_frame));
			}				
			// std::cerr << "DEBUG: " << "current angle[" << _angle / _frame_range * (current_frame - _start_frame) << "] given angle[" << _angle <<  "] fr[" << _frame_range << "] sf[" << _start_frame  << "] ef[" << _end_frame << "] " << std::endl;
		}
		if (current_frame >= _end_frame)
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
	}
	// NEVER ENDING TRANFORMATION
	else if (_frame_range < 0.0f)
	{
		if (_transformation_type == T_TRANSLATE)
		{
			matrix->translate(_x * global_frame, _y * global_frame, _z * global_frame);
		}
		else if (_transformation_type == T_ROTATE)
		{
			matrix->rotate(_angle * global_frame, _x, _y, _z);
		}
		else if (_transformation_type == T_SCALE)
		{
			matrix->scale(_x * global_frame, _y * global_frame, _z * global_frame);
		}
	}
}
