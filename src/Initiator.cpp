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
	models = NULL;
	model_count = 0;
	vertices_mem_size = 0;
	vertices_num_elem = 0;
	vertices_array = NULL;
	faces_mem_size = 0;
	faces_num_elem = 0;
	faces_array = NULL;
	program = 0;
	human = NULL;
	res_x = 1920;
	res_y = 1080;
	camera.init();
}

void
Initiator::genMatrices(void)
{
	setProjMatrix(70, 0.1, 100);
	setViewMatrix();
	setModelMatrix();
}

void
Initiator::getLocations(void)
{
	this->position_loc = glGetAttribLocation(this->program, "position");
	this->color_loc = glGetAttribLocation(this->program, "color");
	this->proj_loc = glGetUniformLocation(this->program, "proj_matrix");
	this->view_loc = glGetUniformLocation(this->program, "view_matrix");
	this->model_loc = glGetUniformLocation(this->program, "model_matrix");
}

void
Initiator::genShaders(void)
{
	this->shaders.load();
	this->shaders.compile();
	this->program = glCreateProgram();
	this->shaders.linkProgram(&this->program);
	getLocations();
	checkGlError(__FILE__, __LINE__);
}

int
Initiator::getStatus(void) const
{
	return this->_status;
}

void
Initiator::createImage(void)
{
	Model		mod(3);

	mod.genCubes(0);
	mod.changePartColor(0, 0x56eeFF00);
	mod.part[0].matrix.scale(1.0f, 1.0f, 1.0f);

	// this->models[0].m_matrix.scale(1.0f, 1.0f, 1.0f);
	// this->models[0].m_matrix.translate(-1.5f, 0.0f, 0.0f);

	// 	// model->v_array[0] = {-0.5f, 0.5f, 0.5f, 123, 123, 123, 0};

	// this->models[1].m_matrix.scale(1.0f, 1.0f, 1.0f);
	// this->models[1].m_matrix.rotate(60.0f, 0.0f, 0.0f, 1.0f);
	// this->models[1].m_matrix.rotate(60.0f, 0.0f, 1.0f, 0.0f);
	// this->models[1].m_matrix.rotate(60.0f, 1.0f, 0.0f, 0.0f);
	// this->models[1].v_array->r = 0;

	// this->models[2].m_matrix.scale(1.0f, 1.0f, 1.0f);
	// this->models[2].m_matrix.translate(1.5f, 0.0f, 0.0f);
	// this->models[2].m_matrix.rotate(60.0f, 1.0f, 1.0f, 1.0f);
	
	ConbineModels();
	LoadModels();
}

void
Initiator::ConbineModels(void)
{
	for (int i = 0; i < this->model_count; i++)
	{
		this->vertices_mem_size += this->models[i].v_mem_size;
		this->vertices_num_elem += this->models[i].v_num_elem;

		this->faces_mem_size += this->models[i].f_mem_size;
		this->faces_num_elem += this->models[i].f_num_elem;
	}

	this->vertices_array = new Point[this->vertices_num_elem];
	this->faces_array = new GLuint[this->faces_num_elem];

	int		v_index = 0;
	int		f_index = 0;

	for (int j = 0; j < this->model_count; j++)
	{
		for (int p = 0; p < this->models[j].v_num_elem; p++)
		{
			this->vertices_array[v_index] = this->models[j].v_array[p];
			v_index++;
		}
		delete (this->models[j].v_array);
		for (int o = 0; o < this->models[j].f_num_elem; o++)
		{
			this->faces_array[f_index] = this->models[j].f_array[o];
			f_index++;
		}
		delete (this->models[j].f_array);
	}
}

void
Initiator::LoadModels(void)
{	
	// Need to Conbine models in vertices and faces;
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(2, &this->vbos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->vertices_mem_size, this->vertices_array, GL_STATIC_DRAW);
	glVertexAttribPointer(this->position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Point), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(this->position_loc);
	glVertexAttribPointer(this->color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Point), reinterpret_cast<void*>(4 * 3));
	glEnableVertexAttribArray(this->color_loc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->faces_mem_size, this->faces_array, GL_STATIC_DRAW);
	delete (this->vertices_array);
	delete (this->faces_array);
}

bool
Initiator::drawImage(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->program);
	glUniformMatrix4fv(this->proj_loc, 1, GL_FALSE, this->proj_matrix.val);
	glUniformMatrix4fv(this->view_loc, 1, GL_FALSE, this->camera.view.val);

	for (int i = 0; i < this->model_count; i++)
	{
		glUniformMatrix4fv(this->model_loc, 1, GL_FALSE, this->models[i].m_matrix.val);
		glDrawElements(GL_TRIANGLES, this->models[i].f_num_elem, GL_UNSIGNED_INT,
			reinterpret_cast<void*>(this->models[i].num_faces_before * sizeof(GLuint)));
	}
	this->models[1].m_matrix.rotate(2.0f, 1.0f, 0.0f, 0.0f);
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
	model_matrix.setIdentity();
}

/////////////////////
//  DEBUG AND TEST //
/////////////////////

void
Initiator::printArray(GLuint *a, int size)
{
	for (int i = 0; i < size ; i++)
	{
		if (i % 3 == 0)
			std::cout << std::endl;
		std::cout << "[" << a[i] << "]";
	}
	std::cout << std::endl;
}

void
Initiator::printPointArray(Point *a, int size)
{
	std::cout << std::endl << "N [X     Y     Z :  R    G    B   A]" << std::endl << std::endl;
	for (int i = 0; i < size ; i++)
	{
		std::cout << i << " [" << a[i].x << ", " << a[i].y << ", " << a[i].z << ": "
		<< (int)a[i].r << ", " << (int)a[i].g << ", " << (int)a[i].b << ", " << (int)a[i].a << "]" << std::endl;
	}
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
