# include "Transformation.hpp"

Transformation::Transformation(void) : _transformation_type(0), _x(0.0f), _y(0.0f), _z(0.0f), _angle(0.0f), _start_frame(0), _end_frame(0)
{
	this->_frame_range = 0.0f;
	return;
}

Transformation::Transformation(int tt, GLfloat x, GLfloat y, GLfloat z, GLfloat angle, GLuint sf, GLuint ef) :
	_transformation_type(tt), _x(x), _y(y), _z(z), _angle(angle), _start_frame(sf), _end_frame(ef)
{
	this->_frame_range = _end_frame - _start_frame;
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
	else
	{
		std::cerr << "runSetup error: _frame_range = " << _frame_range
						<< " _start_frame = " << _start_frame
						<< " _end_frame = " << _end_frame
						<< std::endl;
	}
}

void
Transformation::runAnimation(Mat4<GLfloat> *matrix, GLuint current_frame)
{
	if (_frame_range > 0.0f)
	{
		if (current_frame >= _start_frame && current_frame < _end_frame)
		{
			if (_transformation_type == T_TRANSLATE)
			{
				matrix->translate(	_x / _frame_range * current_frame,
									_y / _frame_range * current_frame,
									_z / _frame_range * current_frame);
			}
			else if (_transformation_type == T_ROTATE)
			{
				matrix->rotate(_angle / _frame_range * current_frame, _x, _y, _z);
			}
			else if (_transformation_type == T_SCALE)
			{
				matrix->scale(	_x / _frame_range * current_frame,
								_y / _frame_range * current_frame,
								_z / _frame_range * current_frame);
			}				
		}
		else if (current_frame >= _end_frame || current_frame < _start_frame)
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
				matrix->scale(	_x, _y, _z);
			}				
		}
		// else
		// {
		// 	std::cerr 	<< "runAnimation error, current_frame = " << current_frame
		// 				<< " _frame_range = " << _frame_range
		// 				<< " _start_frame = " << _start_frame
		// 				<< " _end_frame = " << _end_frame
		// 				<< std::endl;
		// }
	}
	else
	{
		std::cerr << "runAnimation error, frame_range = " << _frame_range << std::endl;
	}
}
