#ifndef __WEAKMONSTER_HPP__
# define __WEAKMONSTER_HPP__

#include	"Monster.hpp"

class		WeakMonster : public Monster {
public:
	WeakMonster(void);
	~WeakMonster(void);
};

extern "C" {
	Monster 	*getInstance(void) {
		return new WeakMonster();
	}
}

#endif
