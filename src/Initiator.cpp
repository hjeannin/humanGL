#include <SFML/OpenGL.hpp>
#include "Initiator.hpp"

Initiator::Initiator(void) : _status(0)
{
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

int
Initiator::getStatus(void) const
{
	return this->_status;
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
