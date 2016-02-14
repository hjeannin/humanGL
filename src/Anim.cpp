#include "Anim.hpp"

Anim::Anim(void) : matrix(0), part_index(0), parent_id(0)
{
	return;
}

Anim::Anim(Mat4<GLfloat> *m, GLuint pi, int p_id) : matrix(m), part_index(pi), parent_id(p_id)
{
	return;
}

Anim::~Anim(void)
{
	return;
}

void
Anim::runAnim(void)
{
	for (GLuint i = 0; i < anim.size(); i++)
	{
		anim[i]->run(this->matrix);
	}
}

void
Anim::runSetup(void)
{
	for (GLuint i = 0; i < setup.size(); i++)
	{
		setup[i]->run(this->matrix);
	}
}
