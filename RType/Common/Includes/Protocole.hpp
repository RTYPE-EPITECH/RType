#pragma once
#ifndef PROTOCOLE_HPP_
# define PROTOCOLE_HPP_

#include			<cstring>
#include			<cstdint>
#include			<vector>
#include			<map>
#include			"EObject.hpp"

class AObject;

typedef struct {
	uint8_t			lenght;
	uint8_t			data[255];
}					string;

typedef struct {
	uint8_t			opcode;
	uint8_t			id;
	uint16_t		size;
}					headerPacket;

typedef struct {
	uint8_t			opcode;
}					responsePacket;

typedef struct {
	uint8_t			difficulty;
	uint8_t			nbGame;
}					parametersPacket;

typedef struct {
	uint8_t			action;
}					actionPacket;

typedef struct {
	uint8_t			scroll;
}					scrollingPacket;

typedef struct {
	uint8_t			idPlayer;
	uint8_t			nbGame;
}					identifantPacket;

typedef struct {
	string			type;
	string			name;
}					deadEntityPacket;

typedef struct {
	uint16_t		pos_x;
	uint16_t		pos_y;
	uint16_t		size_x;
	uint16_t		size_y;
	uint8_t			type;
	string			sprite;
	string			path;
}					positionPacket;

typedef struct {
	uint8_t			lenght;
	positionPacket	data[50];
}					arrayPositionPacket;

typedef				enum {
					NONE = 0,
					UNKNOW = 1,
					SHOOT_FAIL = 2,
					MOOVE_FAIL = 3,
					INVALID_ACTION = 4
}					ERROR_PROTO;

typedef				enum {
					LEFT = 0,
					RIGHT = 1,
					UP = 2,
					DOWN = 3,
					SHOOT = 4,
					UNKNOW_ACTION = 5
}					ACTION;

class				Protocole {
private:
	std::map<char, void(Protocole::*)(const char *)>	_generateData;
	headerPacket			_header;
	responsePacket			_response;
	actionPacket			_action;
	arrayPositionPacket		_arrayPositionPacket;
	parametersPacket		_params;
	scrollingPacket			_scroll;
	identifantPacket		_identifiant;
	deadEntityPacket		_deadEntity;
	int						_posInArray;
	std::vector<char *>		_listPacket;
	unsigned int			_id;

	/*
	** Functions Private to set Packets
	*/

	void					_setResponseStruct(const char *);
	void					_setParametersStruct(const char *);
	void					_setActionStruct(const char *);
	void					_setPositionStruct(const char *);
	void					_setScrollingPacket(const char *);
	void					_setIdentifiantPacket(const char *);
	void					_setDeadEntityPacket(const char *);

public:
	Protocole(unsigned int id = 0);
	~Protocole(void);

	/* 
	** Functions to create Packets 
	*/

	void					_createResponsePacket(ERROR_PROTO err);
	void					_createConnectPacket(void);
	void					_createActionPacket(ACTION act);
	void					_createParametersPacket(int, int);
	void					_addPositionPacket(unsigned int, unsigned int, unsigned int, unsigned int, EObject, const char *, const char *);
	void					_putPositionPacketOnList(void);
	void					_createPingPacket(void);
	void					_createPongPacket(void);
	void					_createDisconnectPacket(void);
	void					_createScrollingPacket(int);
	void					_createQuitPacket(void);
	void					_createIdentifiantPacket(unsigned int, unsigned int);
	void					_createDeadEntityPacket(const std::string &, const std::string &);
	/*
	** Functions to handle new Packets
	*/

	const char 				*_linkPacketHeaderBody(const char *, const char *) const;
	void					_setNewPacketHeader(const char *);
	void					_setNewPacket(const char *);

	/*
	** Getters
	*/
	
	char					*_getLastPacket(void) const;
	std::vector<char *>		_getListPacket(void) const;
	uint8_t					_getHeaderOpcode(void) const;
	uint8_t					_getHeaderId(void) const;
	uint16_t				_getHeaderSize(void) const;
	uint8_t					_getArrayPositionLenght(void) const;
	uint16_t				_getPositionPosX(size_t) const;
	uint16_t				_getPositionPosY(size_t) const;
	uint16_t				_getPositionSizeX(size_t) const;
	uint16_t				_getPositionSizeY(size_t) const;
	uint8_t					_getPositionSpriteLenght(size_t) const;
	uint8_t					*_getPositionSpriteData(size_t) const;
	uint8_t					_getPositionPathLength(size_t) const;
	uint8_t					*_getPositionPathData(size_t) const;
	EObject					_getType(size_t) const;
	uint8_t					_getResponseOpcode(void) const;
	uint8_t					_getParametersDifficulty(void) const;
	uint8_t					_getParametersNbGame(void) const;
	uint8_t					_getActionOpcode(void) const;
	uint8_t					_getScrolling(void) const;
	uint8_t					_getIdentifiantIdPlayer(void) const;
	uint8_t					_getIdentifiantNbGame(void) const;
	uint8_t					_getDeadEntityNameLenght(void) const;
	uint8_t					*_getDeadEntityNameData(void) const;
	uint8_t					_getDeadEntityTypeLenght(void) const;
	uint8_t					*_getDeadEntityTypeData(void) const;
	unsigned int			_getSizePacket(const char *) const;
	unsigned int			_getSizePacketHeader(void) const;

	/*
	** Setter
	*/

	void					_setId(unsigned int id);
};

#endif // !PROTOCOLE_HPP_
