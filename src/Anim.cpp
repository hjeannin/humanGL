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

