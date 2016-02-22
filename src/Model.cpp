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

void
Model::changePartColorSwagg(int index, GLuint color)
{
	GLubyte		a = (color >> 0) & 0xFF;
	GLubyte		b = (color >> 8) & 0xFF;
	GLubyte		g = (color >> 16) & 0xFF;
	GLubyte		r = (color >> 24) & 0xFF;
	GLubyte		pouet = 0;

	for (GLuint j = 0; j < part[index].v_num_elem; j++)
	{
		pouet += 4;
		if (r != 0)
		{
			part[index].v_array[j].r = r + pouet;
		}
		else
		{
			part[index].v_array[j].r = r;
		}
		if (g != 0)
		{
			part[index].v_array[j].g = g + pouet;
		}
		else
		{
			part[index].v_array[j].g = g;
		}
		if (b != 0)
		{
			part[index].v_array[j].b = b + pouet;
		}
		else
		{
			part[index].v_array[j].b = b;
		}
		if (a != 0)
		{
			part[index].v_array[j].a = a + pouet;
		}
		else
		{
			part[index].v_array[j].a = a;
		}
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

void
Model::allocateHuman(void)
{
	setNeededPart(29);
	genCubes();	
}

void
Model::buildHuman(void)
{
	/////////////////////////////////////////////////////////////////////////////////
	//							BACK VIEW
	//
	//									  [HEAD]
	//LEFT									|								RIGHT
	//	  [LW]--[LFA]--[LE]--[LRA]--[LS]--[BODY]--[RS]--[RRA]--[RE]--[RFA]--[RW]
	//		|								||								  |
	//	  [LH]							   /	\							[RH]
	//									[LB]	[RB]
	//									  |		  |
	//									[LRL]	[RRL]			[LAZER]
	//									  |		  |
	//									[LK]	[RK]
	//									  |		  |
	//									[LFL]	[RFL]
	//									  |		  |
	//									[LA]	[RA]
	//									  |		  |
	//									[LF]	[RF]
	////////////////////////////////////////////////////////////////////////////////

	Anim		*body = new Anim(findMatrix(BODY), NULL);
	Anim		*head = new Anim(findMatrix(HEAD), body);

//	right arm
	Anim		*rs = new Anim(findMatrix(RS), body);
	Anim		*rra = new Anim(findMatrix(RRA), rs);
	Anim		*re = new Anim(findMatrix(RE), rra);
	Anim		*rfa = new Anim(findMatrix(RFA), re);
	Anim		*rw = new Anim(findMatrix(RW), rfa);
	Anim		*rh = new Anim(findMatrix(RH), rw);


//	left arm
	Anim		*ls = new Anim(findMatrix(LS), body);
	Anim		*lra = new Anim(findMatrix(LRA), ls);
	Anim		*le = new Anim(findMatrix(LE), lra);
	Anim		*lfa = new Anim(findMatrix(LFA), le);
	Anim		*lw = new Anim(findMatrix(LW), lfa);
	Anim		*lh = new Anim(findMatrix(LH), lw);


//	right leg
	Anim		*rb = new Anim(findMatrix(RB), body);
	Anim		*rrl = new Anim(findMatrix(RRL), rb);
	Anim		*rk = new Anim(findMatrix(RK), rrl);
	Anim		*rfl = new Anim(findMatrix(RFL), rk);
	Anim		*ra = new Anim(findMatrix(RA), rfl);
	Anim		*rf = new Anim(findMatrix(RF), ra);


//	left leg
	Anim		*lb = new Anim(findMatrix(LB), body);
	Anim		*lrl = new Anim(findMatrix(LRL), lb);
	Anim		*lk = new Anim(findMatrix(LK), lrl);
	Anim		*lfl = new Anim(findMatrix(LFL), lk);
	Anim		*la = new Anim(findMatrix(LA), lfl);
	Anim		*lf = new Anim(findMatrix(LF), la);

//	floor grass
	Anim		*ground = new Anim(findMatrix(GROUND), NULL);
	Anim		*handle = new Anim(findMatrix(HANDLE), rh);
	Anim		*lazer = new Anim(findMatrix(LAZER), handle);

	anim_vector = {	body, head,
					rs, rra, re, rfa, rw, rh,
					ls, lra, le, lfa, lw, lh,
					rb, rrl, rk, rfl, ra, rf,
					lb, lrl, lk, lfl, la, lf,
					ground, handle, lazer};

	changePartColor(GROUND, 0x54545400);
	changePartColor(HANDLE, 0x42424200);
	changePartColorSwagg(LAZER, 0xd0000000);
	anim_vector[GROUND]->setScale(500.0f, 1.0f, 500.f);
	anim_vector[GROUND]->addTranslation(SETUP, 0.0f, -9.0f, 0.0f);
	anim_vector[HANDLE]->setScale(0.5f, 0.5f, 1.6f);
	anim_vector[LAZER]->setScale(0.4f, 0.4f, 6.0f);
	anim_vector[LAZER]->addTranslation(SETUP, 0.0f, 0.0f, -3.4f);
// HIDE
	anim_vector[HANDLE]->addTranslation(SETUP, 0.0f, 0.0f, -10000.0f);

	changePartColor(HEAD, 0xB9886500);
	changePartColor(RE, 0xB9886500);
	changePartColor(RFA, 0xB9886500);
	changePartColor(LE, 0xB9886500);
	changePartColor(LFA, 0xB9886500);

	changePartColor(RH, 0xB9886500);
	changePartColor(LH, 0xB9886500);

	changePartColor(BODY, 0xffffff00);
	changePartColor(RS, 0xffffff00);
	changePartColor(LS, 0xffffff00);
	changePartColor(RRA, 0xffffff00);
	changePartColor(LRA, 0xffffff00);

	changePartColor(RW, 0xffd70000);
	changePartColor(LW, 0xffd70000);

	changePartColorSwagg(RB, 0x00225000);
	changePartColorSwagg(LB, 0x00225000);
	changePartColorSwagg(RRL, 0x00225000);
	changePartColorSwagg(LRL, 0x00225000);
	changePartColorSwagg(RK, 0x00225000);
	changePartColorSwagg(LK, 0x00225000);
	changePartColorSwagg(RFL, 0x00225000);
	changePartColorSwagg(LFL, 0x00225000);
	changePartColorSwagg(RA, 0xffffff00);
	changePartColorSwagg(LA, 0xffffff00);

	changePartColorSwagg(RF, 0xFFFFFF00);
	changePartColorSwagg(LF, 0xFFFFFF00);

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
	anim_vector[RE]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RE]->addRotation(SETUP, Z_AXIS, 8.0f);
	anim_vector[RE]->addRotation(SETUP, X_AXIS, -16.0f);
	anim_vector[RFA]->setScale(0.8f, 1.0f, 0.8f);
	anim_vector[RFA]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RW]->setScale(1.0f, 0.4f, 1.0f);
	anim_vector[RW]->addTranslation(SETUP, 0.0f, -0.6f, 0.0f);
	anim_vector[RH]->setScale(0.6f, 1.2f, 0.8f);
	anim_vector[RH]->addTranslation(SETUP, 0.0f, -0.8f, 0.0f);


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
	anim_vector[LW]->setScale(1.0f, 0.4f, 1.0f);
	anim_vector[LW]->addTranslation(SETUP, 0.0f, -0.6f, 0.0f);
	anim_vector[LH]->setScale(0.6f, 1.2f, 0.8f);
	anim_vector[LH]->addTranslation(SETUP, 0.0f, -0.8f, 0.0f);


// right leg
	anim_vector[RB]->setScale(1.5f, 1.0f, 1.0f);
	anim_vector[RB]->addTranslation(SETUP, 0.8f, -2.5f, 0.0f);
	anim_vector[RRL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[RRL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[RK]->setScale(1.2f, 1.2f, 1.2f);
	anim_vector[RK]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[RFL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[RFL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[RA]->setScale(1.0f, 0.4f, 1.0f);
	anim_vector[RA]->addTranslation(SETUP, 0.0f, -1.2f, 0.0f);
	anim_vector[RF]->setScale(1.0f, 0.6f, 2.0f);
	anim_vector[RF]->addTranslation(SETUP, 0.0f, -0.5f, -0.5f);


//	left leg
	anim_vector[LB]->setScale(1.5f, 1.0f, 1.0f);
	anim_vector[LB]->addTranslation(SETUP, -0.8f, -2.5f, 0.0f);
	anim_vector[LRL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[LRL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[LK]->setScale(1.2f, 1.2f, 1.2f);
	anim_vector[LK]->addTranslation(SETUP, 0.0f, -1.0f, 0.0f);
	anim_vector[LFL]->setScale(1.0f, 2.0f, 1.0f);
	anim_vector[LFL]->addTranslation(SETUP, 0.0f, -1.5f, 0.0f);
	anim_vector[LA]->setScale(1.0f, 0.4f, 1.0f);
	anim_vector[LA]->addTranslation(SETUP, 0.0f, -1.2f, 0.0f);
	anim_vector[LF]->setScale(1.0f, 0.6f, 2.0f);
	anim_vector[LF]->addTranslation(SETUP, 0.0f, -0.5f, -0.5f);
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

	anim_vector[RA]->addRotation(ANIM, X_AXIS, -20.0f, sf, mf);
	anim_vector[RA]->addRotation(ANIM, X_AXIS, 20.0f, mf, ef);

//	left leg backward
	anim_vector[LB]->addRotation(SETUP, X_AXIS, 20.0f);
	anim_vector[LK]->addRotation(SETUP, X_AXIS, 20.0f);
	anim_vector[LA]->addRotation(SETUP, X_AXIS, -20.0f);

	anim_vector[LB]->addRotation(ANIM, X_AXIS, -50.0f, sf, mf);
	anim_vector[LB]->addRotation(ANIM, X_AXIS, 50.0f, mf, ef);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, -20.0f, sf, mf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, 20.0f, mf, ef);

	anim_vector[LA]->addRotation(ANIM, X_AXIS, 20.0f, sf, mf);
	anim_vector[LA]->addRotation(ANIM, X_AXIS, -20.0f, mf, ef);

//	moving forward	
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
	anim_vector[RA]->addRotation(ANIM, X_AXIS, -60.0f, sf, nsf);
	anim_vector[RA]->addRotation(ANIM, X_AXIS, 120.0f, nsf, mf);
	anim_vector[RA]->addRotation(ANIM, X_AXIS, -60.0f, mf, nef);
	
//	left leg
	anim_vector[LB]->addRotation(ANIM, X_AXIS, -80.0f, sf, nsf);
	anim_vector[LB]->addRotation(ANIM, X_AXIS, 80.0f, nsf, mf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, 160.0f, sf, nsf);
	anim_vector[LK]->addRotation(ANIM, X_AXIS, -160.0f, nsf, mf);
	anim_vector[LA]->addRotation(ANIM, X_AXIS, -60.0f, sf, nsf);
	anim_vector[LA]->addRotation(ANIM, X_AXIS, 120.0f, nsf, mf);
	anim_vector[LA]->addRotation(ANIM, X_AXIS, -60.0f, mf, nef);

// body
	anim_vector[BODY]->addRotation(ANIM, X_AXIS, -360.0f, mf, 90);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, -2.0f, 0.0f, sf, nsf);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, 3.0f, 0.0f, nsf, mf);
	anim_vector[BODY]->addTranslation(ANIM, 0.0f, -1.0f, 0.0f, mf, ef);
}

void
Model::humanHello(void)
{
	GLuint		sf = 0;
	GLuint		nsf = 40;
	GLuint		mf = 50;
	GLuint		nef = 70;
	GLuint		ef = 80;
	GLuint		lf = 140;
	GLuint		lef = 180;

	(void)sf;
	(void)nsf;
	(void)mf;
	(void)nef;
	(void)ef;
	max_frame = lef;

	anim_vector[RS]->addRotation(ANIM, X_AXIS, -50.0f, sf, nsf);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, -90.0f, sf, nsf);
	anim_vector[RW]->addRotation(ANIM, Y_AXIS, -90.0f, sf, nsf);
	anim_vector[RW]->addRotation(ANIM, Z_AXIS, -30.0f, sf, nsf);

	anim_vector[RE]->addRotation(ANIM, Z_AXIS, -10.0f, nsf, mf);
	anim_vector[RE]->addRotation(ANIM, Z_AXIS, 20.0f, mf, nef);
	anim_vector[RE]->addRotation(ANIM, Z_AXIS, -10.0f, nef, ef);

	anim_vector[RW]->addRotation(ANIM, X_AXIS, 30.0f, nsf, mf);
	anim_vector[RW]->addRotation(ANIM, X_AXIS, -60.0f, mf, nef);
	anim_vector[RW]->addRotation(ANIM, X_AXIS, 30.0f, nef, ef);

	anim_vector[RW]->addRotation(ANIM, Z_AXIS, 30.0f, ef, lf);
	anim_vector[RW]->addRotation(ANIM, Y_AXIS, 90.0f, ef, lf);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, 90.0f, ef, lf);
	anim_vector[RS]->addRotation(ANIM, X_AXIS, 50.0f, ef, lf);
}

void
Model::humanVader(void)
{
	GLuint		sf = 0;
	GLuint		nsf = 40;
	GLuint		mf = 60;
	GLuint		nef = 70;
	GLuint		ef = 80;

	(void)sf;
	(void)nsf;
	(void)mf;
	(void)nef;
	(void)ef;
	max_frame = ef;

// place saber
	anim_vector[HANDLE]->addTranslation(SETUP, 0.0f, 0.0f, 10000.0f);
	anim_vector[HANDLE]->addTranslation(SETUP, 0.0f, -5.0f, -100.0f);

// move hand
	anim_vector[RS]->addRotation(ANIM, X_AXIS, -30.0f, sf, nsf);
	anim_vector[RE]->addRotation(ANIM, X_AXIS, -90.0f, sf, nsf);
	anim_vector[RW]->addRotation(ANIM, Y_AXIS, -90.0f, sf, nsf);
	anim_vector[RW]->addRotation(ANIM, Z_AXIS, -30.0f, sf, nsf);

// force saber
	anim_vector[HANDLE]->addTranslation(ANIM, 0.0f, 5.0f, 100.0f, nsf, mf);
}

void
Model::clearAnimationAndSetup(void)
{
	for (GLuint k = 0; k < anim_vector.size(); k++)
	{
		if (anim_vector[k]->scale != NULL)
		{
			delete anim_vector[k]->scale;
		}
		for (GLuint i = 0; i < anim_vector[k]->animation_transform.size(); i++)
		{
			delete anim_vector[k]->animation_transform[i];
		}
		for (GLuint j = 0; j < anim_vector[k]->setup_transform.size(); j++)
		{
			delete anim_vector[k]->setup_transform[j];
		}
	}
}

void
Model::switchAnimation(int	animation)
{
	clearAnimationAndSetup();
	buildHuman();
	frame = 0;
	global_frame = 0;
	if (animation == 1)
		humanWalk();
	if (animation == 2)
		humanBackFlip();
	if (animation == 3)
		humanHello();
	if (animation == 4)
		humanVader();
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
