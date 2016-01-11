#include "Initiator.hpp"

Initiator::Initiator(void) : _status(0)
{
	initData();
	return;
}

Initiator::Initiator(int s) : _status(s)
{
	return;
}

Initiator::Initiator(Initiator const &src)
{
	*this = src;
	return;
}

Initiator::~Initiator(void)
{
	return;
}

void
Initiator::initData(void)
{
	res_x = 1920;
	res_y = 1080;
	translate[0] = 0.2f;
	translate[1] = 0.2f;
	translate[2] = -1.0f;
	rotate[0] = 0.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	scale = 0.5f;
	this->_status = 1;
}

void
Initiator::genMatrices(void)
{
	setProjMatrix(70, 0.1, 100);
	setViewMatrix();
	setModelMatrix();
}

void
Initiator::genShaders(void)
{
	this->shaders.load();
	this->shaders.compile();
	this->program = glCreateProgram();
	this->shaders.linkProgram(&this->program);
}

void
Initiator::getLocations(void)
{
	this->position_loc = glGetAttribLocation(this->program, "position");
	this->proj_loc = glGetUniformLocation(this->program, "proj_matrix");
	this->view_loc = glGetUniformLocation(this->program, "view_matrix");
	this->trans_loc = glGetUniformLocation(this->program, "trans_matrix");
	this->rot_loc = glGetUniformLocation(this->program, "rot_matrix");
	this->scale_loc = glGetUniformLocation(this->program, "scale_matrix");
}

int
Initiator::getStatus(void) const
{
	return this->_status;
}

// bool
// Initiator::createImage(void)
// {
// 	this->vertices_array = new GLfloat[this->vertices_num_elem];
// 	this->faces_array = new GLfloat[this->vertices_num_elem];


// 	glGenVertexArrays(1, &this->vao);
// 	glBindVertexArray(this->vao);
// 	glGenBuffers(2, &this->vbos[0]);

// 	this->vertices_size = sizeof(GLfloat) * this->vertices_num_elem;
// 	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
// 	glBufferData(GL_ARRAY_BUFFER, this->vertices_size, this->vertices_array,
// 					GL_STATIC_DRAW);

// 	glVertexAttribPointer(this->position_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
// 	glEnableVertexAttribArray(this->position_loc);

// 	this->faces_size = sizeof(GLuint) * this->faces_num_elem;
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->faces_size, this->faces_array,
// 					GL_STATIC_DRAW);

// 	return (true);
// }

void
Initiator::setProjMatrix(GLfloat fov, GLfloat near_cp, GLfloat far_cp)
{
	GLfloat		scale;
	GLfloat		ratio;

	scale = 1.0f / tan(fov * 0.5 * M_PI / 180);
	ratio = (1.0f * res_x) / (1.0f * res_y);
	proj_matrix.set(0, scale / ratio);
	proj_matrix.set(5, scale);
	proj_matrix.set(10, (far_cp + near_cp) / (near_cp - far_cp));
	proj_matrix.set(11, -1.0f);
	proj_matrix.set(14, (2.0f * far_cp * near_cp) / (near_cp - far_cp));
	proj_matrix.set(15, 0.0f);
}

void
Initiator::setViewMatrix(void)
{
	view_matrix.setIdentity();
}

void
Initiator::setModelMatrix(void)
{
	trans_matrix.set(12, translate[0]);
	trans_matrix.set(13, translate[1]);
	trans_matrix.set(14, translate[2]);
	//TODO rotation matrix
	scale_matrix.set(0, scale);
	scale_matrix.set(5, scale);
	scale_matrix.set(10, scale);
}

Initiator
&Initiator::operator=(Initiator const &rhs)
{
	this->_status = rhs.getStatus();
	return *this;
}

std::ostream
&operator<<(std::ostream &o, Initiator const &i)
{
	o << "I am the Initiator of the world! My status is : " << i.getStatus() << std::endl;
	return o;
}
