#ifndef MISSILE_HPP
#define	MISSILE_HPP

#include "AObject.hpp"
#include "EMissile.hpp"

class Missile : public AObject {
protected:
	size_t _damage;
	EMissile _type;
public:
	Missile(Protocole &);
	~Missile();

	// get / set
	size_t	getDamage();
	void	setDamage(size_t);

	void setType(EMissile);
	EMissile getType();

	static Missile * newInstance(Protocole &, EMissile, size_t, size_t);
};

#endif /* MISSILE_HPP */