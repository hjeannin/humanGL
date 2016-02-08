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
	res_x = 1920;
	res_y = 1080;
	cam_pos[0] = 0.0f;
	cam_pos[1] = 0.0f;
	cam_pos[2] = 0.0f;
	translate[0] = 0.0f;
	translate[1] = 0.0f;
	translate[2] = 0.0f;
	rotate[0] = 0.0f;
	rotate[1] = 0.0f;
	rotate[2] = 0.0f;
	scale[0] = 0.2f;
	scale[1] = 0.2f;
	scale[2] = 0.2f;
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
Initiator::generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b)
{
	// TODO adapt to struct Model
	int				number_of_lines = size;
	int				nolk = number_of_lines + 1;
	int				index = 0;
	int				index2 = 0;
	double			pi = M_PI;
	double			tmp1 = 0;
	double			tmp2 = 0;
	double			tmp3 = 0;
	float			color_decr = 0.1;
	int				number_of_points = number_of_lines * nolk;
	int				number_of_faces = (number_of_points * 2) - (number_of_lines * 2);

	this->vertices_num_elem = number_of_points;
	this->faces_num_elem = 3 * number_of_faces;
	this->vertices_array = new Point[this->vertices_num_elem];
	this->faces_array = new GLuint[this->faces_num_elem];
	this->vertices_mem_size = sizeof(GLfloat) * this->vertices_num_elem * 4;
	this->faces_mem_size = sizeof(GLuint) * this->faces_num_elem;

		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
	for (int k = 0; k < nolk ; k++)
	{
		color_r -= color_decr;
		color_g -= color_decr;
		color_b -= color_decr;
		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
		for (int i = 0; i < number_of_lines ; i++)
		{
			tmp1 = sin(pi * k / number_of_lines) * cos(2.0 * pi * i / number_of_lines);
			tmp2 = sin(pi * k / number_of_lines) * sin(2.0 * pi * i / number_of_lines);
			tmp3 = cos(pi * k / number_of_lines);
			this->vertices_array[index] = {static_cast<GLfloat>(tmp1),
										static_cast<GLfloat>(tmp2),
										static_cast<GLfloat>(tmp3),
										color_r, color_g, color_b, 0};
			// std::cout << vertices_array[i].x << "," << vertices_array[i].y << "," << vertices_array[i].z << std::endl;
			index++;
		}
	}
	for (int j = 0; j < faces_num_elem; j += 6)
	{
		this->faces_array[j] = index2;
		this->faces_array[j + 1] = index2 + 1;
		this->faces_array[j + 2] = index2 + number_of_lines;
		this->faces_array[j + 3] = index2 + 1;
		this->faces_array[j + 4] = index2 + number_of_lines;
		this->faces_array[j + 5] = index2 + number_of_lines + 1;
		index2++;
	}
	// printArray(faces_array, faces_num_elem);
	// printPointArray(this->vertices_array, this->vertices_num_elem);
}

void
Initiator::generateCube(Model *model, int rank)
{
	model->v_num_elem = 8;
	model->f_num_elem = 36;
	model->v_array = new Point[model->v_num_elem];
	model->f_array = new GLuint[model->f_num_elem];
	model->v_mem_size = sizeof(GLfloat) * 4 * model->v_num_elem;
	model->f_mem_size = sizeof(GLuint) * model->f_num_elem;

	model->m_matrix.setIdentity();

	model->v_array[0] = {-0.5f, 0.5f, 0.5f, 123, 123, 123, 0};
	model->v_array[1] = {0.5f, 0.5f, 0.5f, 255, 0, 0, 0};
	model->v_array[2] = {0.5f, -0.5f, 0.5f, 255, 255, 255, 0};
	model->v_array[3] = {-0.5f, -0.5f, 0.5f, 0, 0, 255, 0};
	model->v_array[4] = {-0.5f, 0.5f, -0.5f, 255, 255, 0, 0};
	model->v_array[5] = {0.5f, 0.5f, -0.5f, 255, 0, 255, 0};
	model->v_array[6] = {0.5f, -0.5f, -0.5f, 0, 255, 255, 0};
	model->v_array[7] = {-0.5f, -0.5f, -0.5f, 0, 255, 0, 0};

	model->f_array[0] = 0;
	model->f_array[1] = 1;
	model->f_array[2] = 3;

	model->f_array[3] = 1;
	model->f_array[4] = 2;
	model->f_array[5] = 3;
	
	model->f_array[6] = 4;
	model->f_array[7] = 5;
	model->f_array[8] = 7;
	
	model->f_array[9] = 5;
	model->f_array[10] = 6;
	model->f_array[11] = 7;
	
	model->f_array[12] = 1;
	model->f_array[13] = 5;
	model->f_array[14] = 2;
	
	model->f_array[15] = 5;
	model->f_array[16] = 6;
	model->f_array[17] = 2;
	
	model->f_array[18] = 0;
	model->f_array[19] = 4;
	model->f_array[20] = 3;
	
	model->f_array[21] = 4;
	model->f_array[22] = 7;
	model->f_array[23] = 3;
	
	model->f_array[24] = 0;
	model->f_array[25] = 4;
	model->f_array[26] = 1;
	
	model->f_array[27] = 4;
	model->f_array[28] = 5;
	model->f_array[29] = 1;
	
	model->f_array[30] = 3;
	model->f_array[31] = 7;
	model->f_array[32] = 2;
	
	model->f_array[33] = 7;
	model->f_array[34] = 6;
	model->f_array[35] = 2;

	model->num_faces_before = rank * 36;
	model->type = TYPE_CUBE;
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
Initiator::createImage(void)
{
	this->model_count = 4;
	this->models = new Model[model_count];

	for (int i = 0; i < this->model_count; i++)
	{
		generateCube(&this->models[i], i);
	}
	this->models[0].m_matrix.scale(1.0f, 0.2f, 0.5f);
	this->models[1].m_matrix.scale(0.3f, 0.8f, 0.5f);
	this->models[2].m_matrix.scale(1.0f, 0.5f, 0.5f);
	this->models[2].m_matrix.rotate(0.2f, 0, 0);
	this->models[3].m_matrix.scale(1.0f, 0.5f, 0.5f);

	ConbineModels();

	LoadModels();

	delete (this->vertices_array);
	delete (this->faces_array);
}

bool
Initiator::drawImage(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->program);
	glUniformMatrix4fv(this->proj_loc, 1, GL_FALSE, this->proj_matrix.val);
	glUniformMatrix4fv(this->view_loc, 1, GL_FALSE, this->view_matrix.val);

	for (int i = 0; i < this->model_count; i++)
	{
		glUniformMatrix4fv(this->model_loc, 1, GL_FALSE, this->models[i].m_matrix.val);
		glDrawElements(GL_TRIANGLES, this->models[i].f_num_elem, GL_UNSIGNED_INT,
			reinterpret_cast<void*>(this->models[i].num_faces_before * sizeof(GLuint)));
	}
	// glUniformMatrix4fv(this->model_loc, 1, GL_FALSE, this->object1_matrix.val);
	// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(36 * sizeof(GLuint)));
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
	view_matrix.translate(cam_pos[0], cam_pos[1], cam_pos[2] - 1.0f);
}

void
Initiator::setModelMatrix(void)
{
	model_matrix.setIdentity();
	model_matrix.translate(translate[0], translate[1], translate[2]);
	model_matrix.rotate(rotate[0], rotate[1], rotate[2]);
	model_matrix.scale(scale[0], scale[1], scale[2]);
}

/////////////////////
//  DEBUG AND TEST //
/////////////////////

void
Initiator::debugMatrix(void)
{
	Mat4<GLfloat>		all;

	all = proj_matrix * view_matrix * model_matrix;
	std::cout << "-----------------------" << std::endl;
	std::cout << "proj" << std::endl << this->proj_matrix << std::endl;
	std::cout << "view" << std::endl << this->view_matrix << std::endl;
	std::cout << "model" << std::endl << this->model_matrix << std::endl;
	std::cout << "all" << std::endl << all << std::endl;
}

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
