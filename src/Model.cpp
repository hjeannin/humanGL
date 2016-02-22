#include "Model.hpp"

Model::Model(void)
{
	return;
}

Model::~Model(void)
{
	for (GLuint j = 0; j < anim_vector.size(); j++)
	{
		delete anim_vector[j];
	}
	return;
}

GLuint
Model::getPartCount(void) const
{
	return this->_part_count;
}

void
Model::setNeededPart(GLuint n)
{
	_part_count = n;
	part.reserve(n);
}

void
Model::changePartColor(int index, GLuint color)
{
	GLubyte		a = (color >> 0) & 0xFF;
	GLubyte		b = (color >> 8) & 0xFF;
	GLubyte		g = (color >> 16) & 0xFF;
	GLubyte		r = (color >> 24) & 0xFF;

	for (GLuint j = 0; j < part[index].v_num_elem; j++)
	{
		part[index].v_array[j].r = r;
		part[index].v_array[j].g = g;
		part[index].v_array[j].b = b;
		part[index].v_array[j].a = a;
	}
}

Mat4<GLfloat>
*Model::findMatrix(int index)
{
	return (&part[index].matrix);
}

void
Model::runAnimVectorAnim(void)
{
	for (GLuint i = 0; i < anim_vector.size(); i++)
	{
		anim_vector[i]->runAnim(frame, global_frame);
	}	
}

////////////////////////
// SEE use in Initiator->drawModel()
void
Model::animate(void)
{
	if (frame >= max_frame)
		frame = 0;
	frame++;
	global_frame++;
	runAnimVectorAnim();
}

void
Model::reset(void)
{
	for (GLuint i = 0; i < _part_count; i++)
	{
		part[i].matrix.setIdentity();
	}
}
////////////////////////

// void
// Model::deduceChilds(void)
// {
// 	for (GLuint i = 0; i < anim_vector.size(); i++)
// 	{
// 		if (anim_vector[i]->parent != NULL)
// 		{
// 			anim_vector[i]->parent->child = anim_vector[i];
// 		}
// 	}	
// }

void
Model::multiAnim(void)
{
	Anim	*main = new Anim(findMatrix(0), NULL);
	Anim	*sub1 = new Anim(findMatrix(1), main);
	Anim	*sub2 = new Anim(findMatrix(2), main);
	Anim	*sub3 = new Anim(findMatrix(3), main);
	Anim	*sub4 = new Anim(findMatrix(4), main);
	Anim	*sub5 = new Anim(findMatrix(5), main);
	Anim	*sub6 = new Anim(findMatrix(6), main);
	Anim	*sub7 = new Anim(findMatrix(7), main);
	Anim	*sub8 = new Anim(findMatrix(8), main);
	Anim	*sub9 = new Anim(findMatrix(9), main);
	Anim	*sub10 = new Anim(findMatrix(10), main);
	Anim	*sub11 = new Anim(findMatrix(11), main);
	Anim	*sub12 = new Anim(findMatrix(12), main);
	Anim	*sub13 = new Anim(findMatrix(13), main);
	Anim	*sub14 = new Anim(findMatrix(14), main);
	Anim	*sub15 = new Anim(findMatrix(15), main);
	Anim	*sub16 = new Anim(findMatrix(16), main);
	Anim	*sub17 = new Anim(findMatrix(17), main);
	Anim	*sub18 = new Anim(findMatrix(18), main);
	Anim	*sub19 = new Anim(findMatrix(19), main);
	Anim	*sub20 = new Anim(findMatrix(20), main);
	Anim	*sub21 = new Anim(findMatrix(21), main);
	Anim	*sub22 = new Anim(findMatrix(22), main);
	Anim	*sub23 = new Anim(findMatrix(23), main);
	Anim	*sub24 = new Anim(findMatrix(24), main);
	Anim	*sub25 = new Anim(findMatrix(25), main);
	Anim	*sub26 = new Anim(findMatrix(26), main);

	anim_vector.push_back(main);
	anim_vector.push_back(sub1);
	anim_vector.push_back(sub2);
	anim_vector.push_back(sub3);
	anim_vector.push_back(sub4);
	anim_vector.push_back(sub5);
	anim_vector.push_back(sub6);
	anim_vector.push_back(sub7);
	anim_vector.push_back(sub8);
	anim_vector.push_back(sub9);
	anim_vector.push_back(sub10);
	anim_vector.push_back(sub11);
	anim_vector.push_back(sub12);
	anim_vector.push_back(sub13);
	anim_vector.push_back(sub14);
	anim_vector.push_back(sub15);
	anim_vector.push_back(sub16);
	anim_vector.push_back(sub17);
	anim_vector.push_back(sub18);
	anim_vector.push_back(sub19);
	anim_vector.push_back(sub20);
	anim_vector.push_back(sub21);
	anim_vector.push_back(sub22);
	anim_vector.push_back(sub23);
	anim_vector.push_back(sub24);
	anim_vector.push_back(sub25);
	anim_vector.push_back(sub26);
}

void
Model::buildWTF(void)
{
	GLuint		sf = 0;
	GLuint		mf = 30;
	GLuint		ef = 60;

	setNeededPart(27);
	genCubes();
	multiAnim();
	// anim_vector[0]->addRotation(ANIM, X_AXIS, 360.0f, sf, ef);
	// anim_vector[0]->addRotation(ANIM, Y_AXIS, 180.0f, sf, mf);
	// anim_vector[0]->addRotation(ANIM, Y_AXIS, -180.0f, mf, ef);

	anim_vector[1]->addTranslation(SETUP, 1.0f, 0.0f, 0.0f);
	anim_vector[2]->addTranslation(SETUP, -1.0f, 0.0f, 0.0f);
	anim_vector[3]->addTranslation(SETUP, 0.0f, 1.0f, 0.0f);
	anim_vector[4]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[5]->addTranslation(SETUP, 0.0f, 0.0f, 1.0f);
	anim_vector[6]->addTranslation(SETUP, 0.0f, 0.0f, -1.0f);
	anim_vector[7]->addTranslation(SETUP, 1.0f, 1.0f, 0.0f);
	anim_vector[8]->addTranslation(SETUP, 1.0f, -1.0f, 0.0f);
	anim_vector[9]->addTranslation(SETUP, -1.0f, 1.0f, 0.0f);
	anim_vector[10]->addTranslation(SETUP, -1.0f, -1.0f, 0.0f);
	anim_vector[11]->addTranslation(SETUP, 1.0f, 1.0f, 1.0f);
	anim_vector[12]->addTranslation(SETUP, 1.0f, -1.0f, 1.0f);
	anim_vector[13]->addTranslation(SETUP, -1.0f, 1.0f, 1.0f);
	anim_vector[14]->addTranslation(SETUP, -1.0f, -1.0f, 1.0f);
	anim_vector[15]->addTranslation(SETUP, 1.0f, 1.0f, -1.0f);
	anim_vector[16]->addTranslation(SETUP, 1.0f, -1.0f, -1.0f);
	anim_vector[17]->addTranslation(SETUP, -1.0f, 1.0f, -1.0f);
	anim_vector[18]->addTranslation(SETUP, -1.0f, -1.0f, -1.0f);
	anim_vector[19]->addTranslation(SETUP, 0.0f, 1.0f, -1.0f);
	anim_vector[20]->addTranslation(SETUP, 0.0f, -1.0f, -1.0f);
	anim_vector[21]->addTranslation(SETUP, 0.0f, 1.0f, 1.0f);
	anim_vector[22]->addTranslation(SETUP, 0.0f, -1.0f, 1.0f);
	anim_vector[23]->addTranslation(SETUP, 1.0f, 0.0f, -1.0f);
	anim_vector[24]->addTranslation(SETUP, -1.0f, 0.0f, -1.0f);
	anim_vector[25]->addTranslation(SETUP, 1.0f, 0.0f, 1.0f);
	anim_vector[26]->addTranslation(SETUP, -1.0f, 0.0f, 1.0f);

	anim_vector[1]->addTranslation(ANIM, -2.0f, 0.0f, 0.0f, sf, mf);
	anim_vector[1]->addTranslation(ANIM, 2.0f, 0.0f, 0.0f, mf, ef);
	anim_vector[2]->addTranslation(ANIM, 2.0f, 0.0f, 0.0f, sf, mf);
	anim_vector[2]->addTranslation(ANIM, -2.0f, 0.0f, 0.0f, mf, ef);
	anim_vector[3]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[3]->addTranslation(ANIM, 0.0f, 2.0f, 0.0f, mf, ef);	
	anim_vector[4]->addTranslation(ANIM, 0.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[4]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, mf, ef);
	anim_vector[5]->addTranslation(ANIM, 0.0f, 0.0f, -2.0f, sf, mf);
	anim_vector[5]->addTranslation(ANIM, 0.0f, 0.0f, 2.0f, mf, ef);
	anim_vector[6]->addTranslation(ANIM, 0.0f, 0.0f, 2.0f, sf, mf);
	anim_vector[6]->addTranslation(ANIM, 0.0f, 0.0f, -2.0f, mf, ef);
	anim_vector[7]->addTranslation(ANIM, -2.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[7]->addTranslation(ANIM, 2.0f, 2.0f, 0.0f, mf, ef);
	anim_vector[8]->addTranslation(ANIM, -2.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[8]->addTranslation(ANIM, 2.0f, -2.0f, 0.0f, mf, ef);
	anim_vector[9]->addTranslation(ANIM, 2.0f, -2.0f, 0.0f, sf, mf);
	anim_vector[9]->addTranslation(ANIM, -2.0f, 2.0f, 0.0f, mf, ef);
	anim_vector[10]->addTranslation(ANIM, 2.0f, 2.0f, 0.0f, sf, mf);
	anim_vector[10]->addTranslation(ANIM, -2.0f, -2.0f, 0.0f, mf, ef);
	anim_vector[11]->addTranslation(ANIM, -2.0f, -2.0f, -2.0f, sf, mf);
	anim_vector[11]->addTranslation(ANIM, 2.0f, 2.0f, 2.0f, mf, ef);
	anim_vector[12]->addTranslation(ANIM, -2.0f, 2.0f, -2.0f, sf, mf);
	anim_vector[12]->addTranslation(ANIM, 2.0f, -2.0f, 2.0f, mf, ef);
	anim_vector[13]->addTranslation(ANIM, 2.0f, -2.0f, -2.0f, sf, mf);
	anim_vector[13]->addTranslation(ANIM, -2.0f, 2.0f, 2.0f, mf, ef);
	anim_vector[14]->addTranslation(ANIM, 2.0f, 2.0f, -2.0f, sf, mf);
	anim_vector[14]->addTranslation(ANIM, -2.0f, -2.0f, 2.0f, mf, ef);
	anim_vector[15]->addTranslation(ANIM, -2.0f, -2.0f, 2.0f, sf, mf);
	anim_vector[15]->addTranslation(ANIM, 2.0f, 2.0f, -2.0f, mf, ef);
	anim_vector[16]->addTranslation(ANIM, -2.0f, 2.0f, 2.0f, sf, mf);
	anim_vector[16]->addTranslation(ANIM, 2.0f, -2.0f, -2.0f, mf, ef);
	anim_vector[17]->addTranslation(ANIM, 2.0f, -2.0f, 2.0f, sf, mf);
	anim_vector[17]->addTranslation(ANIM, -2.0f, 2.0f, -2.0f, mf, ef);
	anim_vector[18]->addTranslation(ANIM, 2.0f, 2.0f, 2.0f, sf, mf);
	anim_vector[18]->addTranslation(ANIM, -2.0f, -2.0f, -2.0f, mf, ef);
	anim_vector[19]->addTranslation(ANIM, 0.0f, -2.0f, 2.0f, sf, mf);
	anim_vector[19]->addTranslation(ANIM, 0.0f, 2.0f, -2.0f, mf, ef);
	anim_vector[20]->addTranslation(ANIM, 0.0f, 2.0f, 2.0f, sf, mf);
	anim_vector[20]->addTranslation(ANIM, 0.0f, -2.0f, -2.0f, mf, ef);
	anim_vector[21]->addTranslation(ANIM, 0.0f, -2.0f, -2.0f, sf, mf);
	anim_vector[21]->addTranslation(ANIM, 0.0f, 2.0f, 2.0f, mf, ef);
	anim_vector[22]->addTranslation(ANIM, 0.0f, 2.0f, -2.0f, sf, mf);
	anim_vector[22]->addTranslation(ANIM, 0.0f, -2.0f, 2.0f, mf, ef);
	anim_vector[23]->addTranslation(ANIM, -2.0f, 0.0f, 2.0f, sf, mf);
	anim_vector[23]->addTranslation(ANIM, 2.0f, 0.0f, -2.0f, mf, ef);
	anim_vector[24]->addTranslation(ANIM, 2.0f, 0.0f, 2.0f, sf, mf);
	anim_vector[24]->addTranslation(ANIM, -2.0f, 0.0f, -2.0f, mf, ef);
	anim_vector[25]->addTranslation(ANIM, -2.0f, 0.0f, -2.0f, sf, mf);
	anim_vector[25]->addTranslation(ANIM, 2.0f, 0.0f, 2.0f, mf, ef);
	anim_vector[26]->addTranslation(ANIM, 2.0f, 0.0f, -2.0f, sf, mf);
	anim_vector[26]->addTranslation(ANIM, -2.0f, 0.0f, 2.0f, mf, ef);
}

void
Model::buildPouet(void)
{
	GLuint		sf = 0;
	GLuint		mf = 120;
	GLuint		ef = 240;

	(void)sf;
	(void)mf;
	(void)ef;

	setNeededPart(5);
	genCubes();
	
	changePartColor(RED, 0xFF000000);
	changePartColor(GREEN, 0x00FF0000);
	changePartColor(BLUE, 0x0000FF00);
	changePartColor(ORANGE, 0xFFA50000);
	changePartColor(WHITE, 0xFFFFFF00);

	Anim		*red = new Anim(findMatrix(RED), NULL);
	Anim		*green = new Anim(findMatrix(GREEN), red);
	Anim		*blue = new Anim(findMatrix(BLUE), green);
	Anim		*orange = new Anim(findMatrix(ORANGE), red);
	Anim		*white = new Anim(findMatrix(WHITE), orange);
	
	anim_vector = {red, green, blue, orange, white};

	anim_vector[BLUE]->setScale(3.0f, 1.0f, 1.0f);
	anim_vector[BLUE]->addTranslation(SETUP, 2.0f, 0.0f, 0.0f);

	anim_vector[GREEN]->addTranslation(SETUP, 0.0f, 2.0f, 0.0f);

	anim_vector[RED]->setScale(1.0f, 3.0f, 1.0f);

	anim_vector[ORANGE]->setScale(2.0f, 1.0f, 2.0f);
	anim_vector[ORANGE]->addTranslation(SETUP, 0.0f, -2.0f, 0.0f);

	anim_vector[WHITE]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[WHITE]->setScale(3.0f, 1.0f, 3.0f);

	anim_vector[GREEN]->addRotation(ANIM, Z_AXIS, -180.0f, sf, mf);
	anim_vector[GREEN]->addRotation(ANIM, Z_AXIS, 180.0f, mf, ef);
	anim_vector[RED]->addRotation(ANIM, Y_AXIS, 360.0f, sf, ef);
}

void
Model::buildHuman(void)
{
	/////////////////////////////////////////////////////////////////////////////////
	//							BACK VIEW
	//
	//									  [HEAD]
	//LEFT									|								RIGHT
	//	  [LH]--[LFA]--[LE]--[LRA]--[LS]--[BODY]--[RS]--[RRA]--[RE]--[RFA]--[RH]
	//										||
	//										/	\
	//									[LB]	[RB]
	//									  |		  |
	//									[LRL]	[RRL]
	//									  |		  |
	//									[LK]	[RK]
	//									  |		  |
	//									[LFL]	[RFL]
	//									  |		  |
	//									[LF]	[RF]
	//
	////////////////////////////////////////////////////////////////////////////////

	setNeededPart(23);
	genCubes();

	Anim		*body = new Anim(findMatrix(BODY), NULL);
	Anim		*head = new Anim(findMatrix(HEAD), body);

//	right arm
	Anim		*rs = new Anim(findMatrix(RS), body);
	Anim		*rra = new Anim(findMatrix(RRA), rs);
	Anim		*re = new Anim(findMatrix(RE), rra);
	Anim		*rfa = new Anim(findMatrix(RFA), re);
	Anim		*rh = new Anim(findMatrix(RH), rfa);


//	left arm
	Anim		*ls = new Anim(findMatrix(LS), body);
	Anim		*lra = new Anim(findMatrix(LRA), ls);
	Anim		*le = new Anim(findMatrix(LE), lra);
	Anim		*lfa = new Anim(findMatrix(LFA), le);
	Anim		*lh = new Anim(findMatrix(LH), lfa);


//	right leg
	Anim		*rb = new Anim(findMatrix(RB), body);
	Anim		*rrl = new Anim(findMatrix(RRL), rb);
	Anim		*rk = new Anim(findMatrix(RK), rrl);
	Anim		*rfl = new Anim(findMatrix(RFL), rk);
	Anim		*rf = new Anim(findMatrix(RF), rfl);


//	left leg
	Anim		*lb = new Anim(findMatrix(LB), body);
	Anim		*lrl = new Anim(findMatrix(LRL), lb);
	Anim		*lk = new Anim(findMatrix(LK), lrl);
	Anim		*lfl = new Anim(findMatrix(LFL), lk);
	Anim		*lf = new Anim(findMatrix(LF), lfl);

//	floor grass
	Anim		*grass = new Anim(findMatrix(GRASS), NULL);

	anim_vector = {	body, head,
					rs, rra, re, rfa, rh,
					ls, lra, le, lfa, lh,
					rb, rrl, rk, rfl, rf,
					lb, lrl, lk, lfl, lf,
					grass};

	changePartColor(GRASS, 0x007B0C00);
	anim_vector[GRASS]->setScale(5000.0f, 1.0f, 5000.f);
	anim_vector[GRASS]->addTranslation(SETUP, 0.0f, -9.0f, 0.0f);

	changePartColor(HEAD, 0xB9886500);
	changePartColor(RE, 0xB9886500);
	changePartColor(RFA, 0xB9886500);
	changePartColor(LE, 0xB9886500);
	changePartColor(LFA, 0xB9886500);
	
	changePartColor(RH, 0xCB005C00);
	changePartColor(LH, 0xCB005C00);

	changePartColor(BODY, 0xFFFFFF00);
	changePartColor(RS, 0xDDDDDD00);
	changePartColor(LS, 0xDDDDDD00);
	changePartColor(RRA, 0xFFFFFF00);
	changePartColor(LRA, 0xFFFFFF00);

	changePartColor(RB, 0x00225000);
	changePartColor(LB, 0x00225000);
	changePartColor(RRL, 0x00327000);
	changePartColor(LRL, 0x00327000);
	changePartColor(RK, 0x00225000);
	changePartColor(LK, 0x00225000);
	changePartColor(RFL, 0x00327000);
	changePartColor(LFL, 0x00327000);

	changePartColor(RF, 0xFD9A2900);
	changePartColor(LF, 0xFD9A2900);

	anim_vector[BODY]->setScale(3.0f, 4.0f, 1.0f);
	anim_vector[BODY]->addRotation(SETUP, Y_AXIS, 135.0f);

	anim_vector[HEAD]->setScale(2.0f, 2.0f, 2.0f);
	anim_vector[HEAD]->addTranslation(SETUP, 0.0f, 3.0f, 0.0f);

// right arm
	anim_vector[RS]->addTranslation(SETUP, 2.0f, 1.5f, 0.0f);
	anim_vector[RS]->addRotation(SETUP, Z_AXIS, -8.0f);
	anim_vector[RS]->addRotation(SETUP, X_AXIS, 8.0f);
	anim_vector[RRA]->setScale(0.8f, 1.0f, 0.8f);
	anim_vector[RRA]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	// anim_vector[RE]->setScale(0.8f, 0.8f, 0.8f);
	anim_vector[RE]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RE]->addRotation(SETUP, Z_AXIS, 8.0f);
	anim_vector[RE]->addRotation(SETUP, X_AXIS, -16.0f);
	anim_vector[RFA]->setScale(0.8f, 1.0f, 0.8f);
	anim_vector[RFA]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RH]->setScale(1.0f, 1.5f, 1.0f);
	anim_vector[RH]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);


// left arm
	anim_vector[LS]->addTranslation(SETUP, -2.0f, 1.5f, 0.0f);
	anim_vector[LS]->addRotation(SETUP, Z_AXIS, 8.0f);
	anim_vector[LS]->addRotation(SETUP, X_AXIS, 8.0f);
	anim_vector[LRA]->setScale(0.8f, 1.0f, 0.8f);
	anim_vector[LRA]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[LE]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[LE]->addRotation(SETUP, Z_AXIS, -8.0f);
	anim_vector[LE]->addRotation(SETUP, X_AXIS, -16.0f);
	anim_vector[LFA]->setScale(0.8f, 1.0f, 0.8f);
	anim_vector[LFA]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[LH]->setScale(1.0f, 1.5f, 1.0f);
	anim_vector[LH]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);


// right leg
	anim_vector[RB]->setScale(1.5f, 1.0f, 1.0f);
	anim_vector[RB]->addTranslation(SETUP, 0.8f, -2.5f, 0.0f);
	anim_vector[RRL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[RRL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[RK]->setScale(1.2f, 1.2f, 1.2f);
	anim_vector[RK]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RFL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[RFL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[RF]->setScale(1.0f, 1.0f, 2.0f);
	anim_vector[RF]->addTranslation(SETUP, 0.0f, -1.5f, -0.5f);


//	left leg
	anim_vector[LB]->setScale(1.5f, 1.0f, 1.0f);
	anim_vector[LB]->addTranslation(SETUP, -0.8f, -2.5f, 0.0f);
	anim_vector[LRL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[LRL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[LK]->setScale(1.2f, 1.2f, 1.2f);
	anim_vector[LK]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[LFL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[LFL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[LF]->setScale(1.0f, 1.0f, 2.0f);
	anim_vector[LF]->addTranslation(SETUP, 0.0f, -1.5f, -0.5f);
}

void
Model::humanWalk(void)
{
	GLuint		sf = 0;
	GLuint		mf = 60;
	GLuint		ef = 120;

	max_frame = ef;

//	head
	anim_vector[HEAD]->addRotation(ANIM, X_AXIS, -5.0f, sf, mf);
	anim_vector[HEAD]->addRotation(ANIM, X_AXIS, 5.0f, mf, ef);

//	body tilted
	// anim_vector[BODY]->addRotation(ANIM, X_AXIS, 5.0f, sf, mf);
	// anim_vector[BODY]->addRotation(ANIM, X_AXIS, -5.0f, mf, ef);

//	right arm backward
	anim_vector[RS]->addRotation(SETUP, X_AXIS, 24.0f);

	anim_vector[RS]->addRotation(ANIM, X_AXIS, -42.0f, sf, mf);
	anim_vector[RS]->addRotation(ANIM, X_AXIS, 42.0f, mf, ef);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, -80.0f, sf, mf);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, 80.0f, mf, ef);

//	left arm forward
	anim_vector[LS]->addRotation(SETUP, X_AXIS, -18.0f);
	anim_vector[LE]->addRotation(SETUP, X_AXIS, -80.0f);

	anim_vector[LS]->addRotation(ANIM, X_AXIS, 42.0f, sf, mf);
	anim_vector[LS]->addRotation(ANIM, X_AXIS, -42.0f, mf, ef);
	anim_vector[LE]->addRotation(ANIM, X_AXIS, 80.0f, sf, mf);
	anim_vector[LE]->addRotation(ANIM, X_AXIS, -80.0f, mf, ef);

//	right leg forward
	anim_vector[RB]->addRotation(SETUP, X_AXIS, -30.0f);
	anim_vector[RK]->addRotation(SETUP, X_AXIS, 10.0f);

	anim_vector[RB]->addRotation(ANIM, X_AXIS, 50.0f, sf, mf);
	anim_vector[RB]->addRotation(ANIM, X_AXIS, -50.0f, mf, ef);
	anim_vector[RK]->addRotation(ANIM, X_AXIS, 20.0f, sf, mf);
	anim_vector[RK]->addRotation(ANIM, X_AXIS, -20.0f, mf, ef);
	
//	left leg backward
	anim_vector[LB]->addRotation(SETUP, X_AXIS, 20.0f);
	anim_vector[LK]->addRotation(SETUP, X_AXIS, 20.0f);

	anim_vector[LB]->addRotation(ANIM, X_AXIS, -50.0f, sf, mf);
	anim_vector[LB]->addRotation(ANIM, X_AXIS, 50.0f, mf, ef);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, -20.0f, sf, mf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, 20.0f, mf, ef);
	
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, 0.0f, -0.08f, GLOBAL, GLOBAL);
}

void
Model::humanBackFlip(void)
{
	GLuint		sf = 0;
	GLuint		nsf = 40;
	GLuint		mf = 60;
	GLuint		nef = 80;
	GLuint		ef = 120;

	max_frame = ef;

//	head
	anim_vector[HEAD]->addRotation(ANIM, X_AXIS, 20.0f, sf, mf);
	anim_vector[HEAD]->addRotation(ANIM, X_AXIS, -60.0f, mf, nef);
	anim_vector[HEAD]->addRotation(ANIM, X_AXIS, 40.0f, nef, ef);

//	right arm
	anim_vector[RS]->addRotation(ANIM, X_AXIS, -180.0f, nsf, mf);
	anim_vector[RS]->addRotation(ANIM, X_AXIS, 180.0f, mf, ef);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, -20.0f, nsf, mf);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, 20.0f, mf, ef);

//	left arm
	anim_vector[LS]->addRotation(ANIM, X_AXIS, -180.0f, nsf, mf);
	anim_vector[LS]->addRotation(ANIM, X_AXIS, 180.0f, mf, ef);
	anim_vector[LE]->addRotation(ANIM, X_AXIS, -20.0f, nsf, mf);
	anim_vector[LE]->addRotation(ANIM, X_AXIS, 20.0f, mf, ef);

//	right leg
	anim_vector[RB]->addRotation(ANIM, X_AXIS, -80.0f, sf, nsf);
	anim_vector[RB]->addRotation(ANIM, X_AXIS, 80.0f, nsf, mf);
	anim_vector[RK]->addRotation(ANIM, X_AXIS, 160.0f, sf, nsf);
	anim_vector[RK]->addRotation(ANIM, X_AXIS, -160.0f, nsf, mf);
	
//	left leg
	anim_vector[LB]->addRotation(ANIM, X_AXIS, -80.0f, sf, nsf);
	anim_vector[LB]->addRotation(ANIM, X_AXIS, 80.0f, nsf, mf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, 160.0f, sf, nsf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, -160.0f, nsf, mf);

// body
	anim_vector[BODY]->addRotation(ANIM, X_AXIS, -360.0f, mf, 100);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, sf, nsf);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, 3.0f, 0.0f, nsf, mf);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, -1.0f, 0.0f, mf, ef);
}

void
Model::genCubes(void)
{
	if (_part_count != 0)
	{
		generateCube(&part[0], 0, 0);
		for (GLuint i = 1; i < _part_count; i++)
		{
			generateCube(&part[i],
				part[i - 1].f_num_elem + part[i -1].num_faces_before,
				part[i - 1].v_num_elem + part[i -1].num_vertices_before);
		}
	}
	else
	{
		std::cerr << "parts not allocated" << std::endl;
	}
}

void
Model::generateCube(Part *current_part, int nfb, int nvb)
{
	current_part->num_faces_before = nfb;
	current_part->num_vertices_before = nvb;
	current_part->shape = CUBE;
	current_part->v_num_elem = 8;
	current_part->f_num_elem = 36;
	current_part->v_array = new Point[current_part->v_num_elem];
	current_part->f_array = new GLuint[current_part->f_num_elem];
	current_part->v_mem_size = sizeof(GLfloat) * 4 * current_part->v_num_elem;
	current_part->f_mem_size = sizeof(GLuint) * current_part->f_num_elem;
	current_part->matrix.setIdentity();

	//////////////////////////////////////////////////////////////////
	//                                           glFrontFace(GL_CW);//
    //          4----5		        ^  Y	                     	//
    //         /|   /|              |                     .------.  //
    //       0----1  |              |                    /       |  //
    //       |  7-|--6              |----->  X             .->   )  //
    //       |/   | /              /                      |     /   //
    //       3____2               /                        \___/    //
    //                          |,  Z                               //
	//                                           DEFAULT is GL_CCW  //
	//////////////////////////////////////////////////////////////////

	current_part->v_array[0] = {-0.5f, 0.5f, 0.5f, 123, 123, 123, 0};
	current_part->v_array[1] = {0.5f, 0.5f, 0.5f, 255, 0, 0, 0};
	current_part->v_array[2] = {0.5f, -0.5f, 0.5f, 255, 255, 255, 0};
	current_part->v_array[3] = {-0.5f, -0.5f, 0.5f, 0, 0, 255, 0};
	current_part->v_array[4] = {-0.5f, 0.5f, -0.5f, 255, 255, 0, 0};
	current_part->v_array[5] = {0.5f, 0.5f, -0.5f, 255, 0, 255, 0};
	current_part->v_array[6] = {0.5f, -0.5f, -0.5f, 0, 255, 255, 0};
	current_part->v_array[7] = {-0.5f, -0.5f, -0.5f, 0, 255, 0, 0};

	current_part->f_array[0] = nvb + 0;
	current_part->f_array[1] = nvb + 1;
	current_part->f_array[2] = nvb + 2;

	current_part->f_array[3] = nvb + 2;
	current_part->f_array[4] = nvb + 3;
	current_part->f_array[5] = nvb + 0;
	
	current_part->f_array[6] = nvb + 1;
	current_part->f_array[7] = nvb + 5;
	current_part->f_array[8] = nvb + 6;
	
	current_part->f_array[9] = nvb + 6;
	current_part->f_array[10] = nvb + 2;
	current_part->f_array[11] = nvb + 1;
	
	current_part->f_array[12] = nvb + 5;
	current_part->f_array[13] = nvb + 6;
	current_part->f_array[14] = nvb + 7;
	
	current_part->f_array[15] = nvb + 7;
	current_part->f_array[16] = nvb + 4;
	current_part->f_array[17] = nvb + 5;
	
	current_part->f_array[18] = nvb + 4;
	current_part->f_array[19] = nvb + 0;
	current_part->f_array[20] = nvb + 3;
	
	current_part->f_array[21] = nvb + 3;
	current_part->f_array[22] = nvb + 7;
	current_part->f_array[23] = nvb + 4;
	
	current_part->f_array[24] = nvb + 4;
	current_part->f_array[25] = nvb + 5;
	current_part->f_array[26] = nvb + 1;
	
	current_part->f_array[27] = nvb + 1;
	current_part->f_array[28] = nvb + 0;
	current_part->f_array[29] = nvb + 4;
	
	current_part->f_array[30] = nvb + 2;
	current_part->f_array[31] = nvb + 6;
	current_part->f_array[32] = nvb + 7;
	
	current_part->f_array[33] = nvb + 7;
	current_part->f_array[34] = nvb + 3;
	current_part->f_array[35] = nvb + 2;
}

// void
// Model::generateSphere(int size, GLubyte color_r, GLubyte color_g, GLubyte color_b)
// {
// 	// TODO adapt to struct Model
// 	int				number_of_lines = size;
// 	int				nolk = number_of_lines + 1;
// 	int				index = 0;
// 	int				index2 = 0;
// 	double			pi = M_PI;
// 	double			tmp1 = 0;
// 	double			tmp2 = 0;
// 	double			tmp3 = 0;
// 	float			color_decr = 0.1;
// 	int				number_of_points = number_of_lines * nolk;
// 	int				number_of_faces = (number_of_points * 2) - (number_of_lines * 2);

// 	this->vertices_num_elem = number_of_points;
// 	this->faces_num_elem = 3 * number_of_faces;
// 	this->vertices_array = new Point[this->vertices_num_elem];
// 	this->faces_array = new GLuint[this->faces_num_elem];
// 	this->vertices_mem_size = sizeof(GLfloat) * this->vertices_num_elem * 4;
// 	this->faces_mem_size = sizeof(GLuint) * this->faces_num_elem;

// 		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
// 	for (int k = 0; k < nolk ; k++)
// 	{
// 		color_r -= color_decr;
// 		color_g -= color_decr;
// 		color_b -= color_decr;
// 		// std::cout << "R : " << static_cast<int>(color_r) << " G : " << static_cast<int>(color_g) << " B : " << static_cast<int>(color_b) << std::endl;
// 		for (int i = 0; i < number_of_lines ; i++)
// 		{
// 			tmp1 = sin(pi * k / number_of_lines) * cos(2.0 * pi * i / number_of_lines);
// 			tmp2 = sin(pi * k / number_of_lines) * sin(2.0 * pi * i / number_of_lines);
// 			tmp3 = cos(pi * k / number_of_lines);
// 			this->vertices_array[index] = {static_cast<GLfloat>(tmp1),
// 										static_cast<GLfloat>(tmp2),
// 										static_cast<GLfloat>(tmp3),
// 										color_r, color_g, color_b, 0};
// 			// std::cout << vertices_array[i].x << "," << vertices_array[i].y << "," << vertices_array[i].z << std::endl;
// 			index++;
// 		}
// 	}
// 	for (int j = 0; j < faces_num_elem; j += 6)
// 	{
// 		this->faces_array[j] = index2;
// 		this->faces_array[j + 1] = index2 + 1;
// 		this->faces_array[j + 2] = index2 + number_of_lines;
// 		this->faces_array[j + 3] = index2 + 1;
// 		this->faces_array[j + 4] = index2 + number_of_lines;
// 		this->faces_array[j + 5] = index2 + number_of_lines + 1;
// 		index2++;
// 	}
// 	// printArray(faces_array, faces_num_elem);
// 	// printPointArray(this->vertices_array, this->vertices_num_elem);
// }
