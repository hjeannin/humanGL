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
	vao = 0;
	vbos[0] = 0;
	vbos[1] = 0;
	vertices_size = 0;
	vertices_num_elem = 0;
	vertices_array = NULL;
	faces_size = 0;
	faces_num_elem = 0;
	faces_array = NULL;
	program = 0;
	res_x = 1920;
	res_y = 1080;
	translate[0] = 0.0f;
	translate[1] = 0.0f;
	translate[2] = -1.0f;
	rotate[0] = 0.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	scale = 0.2f;
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
	checkGlError(__FILE__, __LINE__);
}

void
Initiator::getLocations(void)
{
	this->position_loc = glGetAttribLocation(this->program, "position");
	this->color_loc = glGetAttribLocation(this->program, "color");
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

void
Initiator::generateModel(void)
{
	this->vertices_num_elem = 4 * 4;
	this->faces_num_elem = 2 * 3;
	this->vertices_array = new Point[this->vertices_num_elem];
	this->faces_array = new GLuint[this->faces_num_elem];

	// SQUARE of 2 triangles.
	this->vertices_array[0] = {-0.5f, 0.5f, 0.5f, 255, 0, 0, 0};
	this->vertices_array[1] = {0.5f, 0.5f, 0.5f, 0, 255, 0, 0};
	this->vertices_array[2] = {0.5f, -0.5f, 0.5f, 0, 0, 255, 0};
	this->vertices_array[3] = {-0.5f, -0.5f, 0.5f, 123, 123, 123, 0};

	// vertices count start at 0
	this->faces_array[0] = 0;
	this->faces_array[1] = 1;
	this->faces_array[2] = 2;

	this->faces_array[3] = 0;
	this->faces_array[4] = 2;
	this->faces_array[5] = 3;
}

void
Initiator::createImage(void)
{
	generateModel();
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(2, &this->vbos[0]);

	this->vertices_size = sizeof(GLfloat) * this->vertices_num_elem;
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices_size, this->vertices_array,
					GL_STATIC_DRAW);

	glVertexAttribPointer(this->position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(this->position_loc);
	glVertexAttribPointer(this->color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Point), reinterpret_cast<void*>(4 * 3));
	glEnableVertexAttribArray(this->color_loc);

	this->faces_size = sizeof(GLuint) * this->faces_num_elem;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->faces_size, this->faces_array,
					GL_STATIC_DRAW);
	delete (this->vertices_array);
	delete (this->faces_array);
}

void
Initiator::createCBImage(void)
{

	// COLORED CUBE
	this->vertices_num_elem = 4 * 8;
	this->faces_num_elem = 36;

	Point		cube_array[8] = 
	{
		{-0.5f, 0.5f, 0.5f, 123, 123, 123, 0},
		{0.5f, 0.5f, 0.5f, 255, 0, 0, 0},
		{0.5f, -0.5f, 0.5f, 255, 255, 255, 0},
		{-0.5f, -0.5f, 0.5f, 0, 0, 255, 0},
		{-0.5f, 0.5f, -0.5f, 255, 255, 0, 0},
		{0.5f, 0.5f, -0.5f, 255, 0, 255, 0},
		{0.5f, -0.5f, -0.5f, 0, 255, 255, 0},
		{-0.5f, -0.5f, -0.5f, 0, 255, 0, 0},
	};

	int			cube_faces_array[36] =
	{
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		1, 5, 2,
		5, 6, 2,
		0, 4, 3,
		4, 7, 3,
		0, 4, 1,
		4, 5, 1,
		3, 7, 2,
		7, 6, 2
	};

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(2, &this->vbos[0]);

	this->vertices_size = sizeof(GLfloat) * this->vertices_num_elem;
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices_size, cube_array,
					GL_STATIC_DRAW);

	glVertexAttribPointer(this->position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(this->position_loc);
	glVertexAttribPointer(this->color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Point), reinterpret_cast<void*>(4 * 3));
	glEnableVertexAttribArray(this->color_loc);

	this->faces_size = sizeof(GLuint) * this->faces_num_elem;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->faces_size, cube_faces_array,
					GL_STATIC_DRAW);	
}

bool
Initiator::drawImage(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->program);
	glUniformMatrix4fv(this->proj_loc, 1, GL_FALSE, this->proj_matrix.val);
	glUniformMatrix4fv(this->view_loc, 1, GL_FALSE, this->view_matrix.val);
	glUniformMatrix4fv(this->trans_loc, 1, GL_FALSE, this->trans_matrix.val);
	glUniformMatrix4fv(this->rot_loc, 1, GL_FALSE, this->rot_matrix.val);
	glUniformMatrix4fv(this->scale_loc, 1, GL_FALSE, this->scale_matrix.val);
	glDrawElements(GL_TRIANGLES, this->faces_size, GL_UNSIGNED_INT, 0);
	checkGlError(__FILE__, __LINE__);
    return (true);
}

void
Initiator::checkGlError(std::string file, int line)
{
    GLenum        err;

    err = glGetError();
    if (err != GL_NO_ERROR)
    {
        if (err == GL_INVALID_ENUM)
			std::cerr << "GL: Invalid enum in " << file << " line " << line << std::endl;
        else if (err == GL_INVALID_VALUE)
			std::cerr << "GL: Invalid value in " << file << " line " << line << std::endl;
        else if (err == GL_INVALID_OPERATION)
			std::cerr << "GL: Invalid operation in " << file << " line " << line << std::endl;
        else if (err == GL_INVALID_FRAMEBUFFER_OPERATION)
			std::cerr << "GL: Invalid framebuffer operation in " << file << " line " << line << std::endl;
        else if (err == GL_OUT_OF_MEMORY)
			std::cerr << "GL: Out of memory in " << file << " line " << line << std::endl;
		exit(0);
    }
}

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
	trans_matrix.setIdentity();
	trans_matrix.translate(translate[0], translate[1], translate[2]);
	
	rot_matrix.setIdentity();
	// rot_matrix.rotate(20, 1, 0, 0);
	Mat4<GLfloat>	tempx;
	Mat4<GLfloat>	tempy;	
	Mat4<GLfloat>	tempz;

	tempx.set(5, cos(rotate[0]));
	tempx.set(6, sin(rotate[0]));
	tempx.set(9, -sin(rotate[0]));
	tempx.set(10, cos(rotate[0]));

	tempy.set(0, cos(rotate[1]));
	tempy.set(2, -sin(rotate[1]));
	tempy.set(8, sin(rotate[1]));
	tempy.set(10, cos(rotate[1]));

	tempz.set(0, cos(rotate[2]));
	tempz.set(1, sin(rotate[2]));
	tempz.set(4, -sin(rotate[2]));
	tempz.set(5, cos(rotate[2]));

	rot_matrix = tempz * tempy * tempx;

	scale_matrix.setIdentity();
	scale_matrix.scale(this->scale, this->scale, this->scale);
}

void
Initiator::debugMatrix(void)
{
	Mat4<GLfloat>		all;

	all = proj_matrix * view_matrix * trans_matrix * rot_matrix * scale_matrix;
	std::cout << "-----------------------" << std::endl;
	std::cout << "proj" << std::endl << this->proj_matrix << std::endl;
	std::cout << "view" << std::endl << this->view_matrix << std::endl;
	std::cout << "trans" << std::endl << this->trans_matrix << std::endl;
	std::cout << "rot" << std::endl << this->rot_matrix << std::endl;
	std::cout << "scale" << std::endl << this->scale_matrix << std::endl;
	std::cout << "all" << std::endl << all << std::endl;
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
