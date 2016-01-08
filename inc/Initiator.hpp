#ifndef	INITIATOR_HPP
# define INITIATOR_HPP

# include <iostream>

class Initiator
{

private:
	int			_status;

public:

	Initiator(void);
	Initiator(int _status);
	Initiator(Initiator const &src);
	~Initiator(void);

	int			getStatus(void) const;

	Initiator	&operator=(Initiator const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Initiator const &i);

#endif
