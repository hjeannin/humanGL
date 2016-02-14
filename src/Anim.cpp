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
}

void
Anim::runSetup(void)
{
	runTransformVector(setup_transform, this->matrix);
}


/*

for (every parts)
{
	if (Parent == NULL)
	{
		Transform.anim(my_matrix);
		Transform.setup(my_matrix);
	}
	else if (Parent != NULL)
	{
		if (Parent->Parent == NULL)
		{
			Parent->Transform.anim(my_matrix);
			Parent->Transform.setup(my_matrix);
			Transform.anim(my_matrix);
			Transform.setup(my_matrix);
		}
		else if (Parent->Parent != NULL)
		{
			Parent->Parent->Transform.anim(my_matrix);
			Parent->Parent->Transform.setup(my_matrix);
			Parent->Transform.anim(my_matrix);
			Parent->Transform.setup(my_matrix);
			Transform.anim(my_matrix);
			Transform.setup(my_matrix);
		}
	}
}

*/