#ifndef __WEAKMONSTER_HPP__
# define __WEAKMONSTER_HPP__

#include	"IMonster.hpp"

class		WeakMonster : public IMonster {
public:
	WeakMonster(void);
	~WeakMonster(void);

	virtual size_t getLife() const;
	virtual size_t getMaxLife() const;
	virtual size_t getMaxMissile() const;
	virtual EMissile getTypeMissile() const;
	virtual std::string getTypeMonster() const;
};

extern "C" {
	IMonster 	*getInstance(void) {
		return new WeakMonster();
	}
}

#endif
