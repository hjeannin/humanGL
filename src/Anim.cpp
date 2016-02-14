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
	return;
}

void
Anim::runTransformVector(std::vector<Transformation *> &v, Mat4<GLfloat> *m)
{
	for (GLuint i = 0; i < v.size(); i++)
	{
		v[i]->run(m);
	}
}

void
Anim::runAnim(void)
{
	// std::cerr << "Matrix IN: " << matrix << std::endl << *matrix << std::endl;
	if (parent == NULL)
	{
		runTransformVector(animation_transform, this->matrix);
		runTransformVector(setup_transform, this->matrix);			
	}
	else if (parent != NULL)
	{
		if (parent->parent == NULL)
		{
			runTransformVector(parent->animation_transform, this->matrix);			
			runTransformVector(parent->setup_transform, this->matrix);			
			runTransformVector(animation_transform, this->matrix);			
			runTransformVector(setup_transform, this->matrix);			
		}
		else if (parent->parent != NULL)
		{
			runTransformVector(parent->parent->animation_transform, this->matrix);			
			runTransformVector(parent->parent->setup_transform, this->matrix);			
			runTransformVector(parent->animation_transform, this->matrix);			
			runTransformVector(parent->setup_transform, this->matrix);			
			runTransformVector(animation_transform, this->matrix);						
			runTransformVector(setup_transform, this->matrix);			
		}
	}
	// std::cerr << "Matrix OUT: " << matrix << std::endl << *matrix << std::endl;
}

void
Anim::runSetup(void)
{
	runTransformVector(setup_transform, this->matrix);
}