#ifndef MISSILE_HPP
#define	MISSILE_HPP

#include "AObject.hpp"
#include "EMissile.hpp"

class Missile : public AObject {
protected:
	size_t _damage;
	EMissile _type;
public:
	Missile(void);
	~Missile();

	// get / set
	size_t	getDamage();
	void	setDamage(size_t);

	void setTypeMissile(EMissile);
	EMissile getTypeMissile();

	static Missile * newInstance(EMissile, size_t, size_t);
};

#endif /* MISSILE_HPP */