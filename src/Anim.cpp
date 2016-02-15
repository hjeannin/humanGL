#include "Anim.hpp"

Anim::Anim(void) : matrix(0), parent(NULL)
{
	return;
}

Anim::Anim(Mat4<GLfloat> *m, Anim *p) : matrix(m), parent(p)
{
	return;
}

Anim::~Anim(void)
{
	delete (scale);
	return;
}

void
Anim::setScale(GLfloat x, GLfloat y, GLfloat z)
{
	this->scale = new Transformation(T_SCALE, x, y, z);
}

void
Anim::addRotation(bool isAnimation, int axis, GLfloat angle, GLuint start_frame, GLuint end_frame)
{
	Transformation		*new_transformation;

	if (axis == X_AXIS)
	{
		new_transformation = new Transformation(T_ROTATE, 1.0f, 0.0f, 0.0f, angle, start_frame, end_frame);
	}
	else if (axis == Y_AXIS)
	{
		new_transformation = new Transformation(T_ROTATE, 0.0f, 1.0f, 0.0f, angle, start_frame, end_frame);
	}
	else if (axis == Z_AXIS)
	{
		new_transformation = new Transformation(T_ROTATE, 0.0f, 0.0f, 1.0f, angle, start_frame, end_frame);
	}
	else
	{
		std::cerr << "addRotation Error, invalid axis" << std::endl;
	}
	if (isAnimation == true)
	{
		this->animation_transform.push_back(new_transformation);
	}
	if (isAnimation == false)
	{
		this->setup_transform.push_back(new_transformation);
	}
}

void
Anim::addTranslation(bool isAnimation, GLfloat x, GLfloat y, GLfloat z, GLuint start_frame, GLuint end_frame)
{
	Transformation		*new_transformation;

	new_transformation = new Transformation(T_TRANSLATE, x, y, z, 0.0f, start_frame, end_frame);
	if (isAnimation == true)
	{
		this->animation_transform.push_back(new_transformation);
	}
	if (isAnimation == false)
	{
		this->setup_transform.push_back(new_transformation);
	}
}

void
Anim::addScale(bool isAnimation, GLfloat x, GLfloat y, GLfloat z, GLuint start_frame, GLuint end_frame)
{
	Transformation		*new_transformation;

	new_transformation = new Transformation(T_SCALE, x, y, z, 0.0f, start_frame, end_frame);
	if (isAnimation == true)
	{
		this->animation_transform.push_back(new_transformation);
	}
	if (isAnimation == false)
	{
		this->setup_transform.push_back(new_transformation);
	}
}

void
Anim::runSetupTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m)
{
	for (GLuint i = 0; i < v.size(); i++)
	{
		v[i]->runSetup(m);
	}
}

void
Anim::runAnimationTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m, GLuint current_frame)
{
	for (GLuint i = 0; i < v.size(); i++)
	{
		v[i]->runAnimation(m, current_frame);
	}
}

void
Anim::runAnim(GLuint current_frame)
{
	// std::cerr << "Matrix IN: " << matrix << std::endl << *matrix << std::endl;
	scale->runSetup(this->matrix);	
	if (parent == NULL)
	{
		runAnimationTransformVector(animation_transform, this->matrix, current_frame);
		runSetupTransformVector(setup_transform, this->matrix);			
	}
	else if (parent != NULL)
	{
		if (parent->parent == NULL)
		{
			runAnimationTransformVector(parent->animation_transform, this->matrix, current_frame);			
			runSetupTransformVector(parent->setup_transform, this->matrix);			
			runAnimationTransformVector(animation_transform, this->matrix, current_frame);			
			runSetupTransformVector(setup_transform, this->matrix);			
		}
		else if (parent->parent != NULL)
		{
			runAnimationTransformVector(parent->parent->animation_transform, this->matrix, current_frame);			
			runSetupTransformVector(parent->parent->setup_transform, this->matrix);			
			runAnimationTransformVector(parent->animation_transform, this->matrix, current_frame);			
			runSetupTransformVector(parent->setup_transform, this->matrix);			
			runAnimationTransformVector(animation_transform, this->matrix, current_frame);						
			runSetupTransformVector(setup_transform, this->matrix);			
		}
	}
	// std::cerr << "Matrix OUT: " << matrix << std::endl << *matrix << std::endl;
}