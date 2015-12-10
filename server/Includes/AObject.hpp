#ifndef AOBJECT_HPP
#define AOBJECT_HPP

#include "Protocole.hpp"
#include "EObject.hpp"

class AObject
{
public:
	AObject(Protocole &);
	~AObject();

	// FAIRE LES GET/SET

	size_t	getX() const;
	size_t	getY() const;
	size_t	getWidth() const;
	size_t	getHeight() const;
	EObject	getType() const;
	
	void	setX(size_t);
	void	setY(size_t);
	void	setWidth(size_t);
	void	setHeight(size_t);
	void	setType(EObject);

	bool	move(ACTION, size_t);

protected:
	size_t x;
	size_t y;
	size_t width;
	size_t height;
	EObject type;
	Protocole & _proto;

private:
	void	moveRight(size_t &x, size_t &y, size_t s = 1) const;
	void	moveLeft(size_t &x, size_t &y, size_t s = 1) const;
	void	moveTop(size_t &x, size_t &y, size_t s = 1) const;
	void	moveBot(size_t &x, size_t &y, size_t s = 1) const;
};



#endif /* AOBJECT_HPP */