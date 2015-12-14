#pragma once
#ifndef PROTOCOLE_HPP_
# define PROTOCOLE_HPP_

#include			<cstring>
#include			<cstdint>
#include			<vector>
#include			<map>

class AObject;

typedef struct {
	uint8_t			lenght;
	uint8_t			data[255];
}					string;

typedef struct {
	uint8_t			opcode;
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
	uint16_t		pos_x;
	uint16_t		pos_y;
	uint16_t		size_x;
	uint16_t		size_y;
	string			sprite;
}					positionPacket;

typedef struct {
	uint8_t			lenght;
	positionPacket	data[50];
}					arrayPositionPacket;

typedef				enum {
					NONE = 0,
					UNKNOW = 1
}					ERROR_PROTO;

typedef				enum {
					LEFT = 0,
					RIGHT = 1,
					UP = 2,
					DOWN = 3,
					SHOOT = 4
}					ACTION;

class				Protocole {
private:
	std::map<char, void(Protocole::*)(const char *)>	_generateData;
	headerPacket			_header;
	responsePacket			_response;
	actionPacket			_action;
	arrayPositionPacket		_arrayPositionPacket;
	parametersPacket		_params;
	int						_posInArray;
	std::vector<char *>		_listPacket;

	/*
	** Functions Private to set Packets
	*/

	void					_setResponseStruct(const char *);
	void					_setParametersStruct(const char *);
	void					_setActionStruct(const char *);
	void					_setPositionStruct(const char *);

public:
	Protocole(void);
	~Protocole(void);

	/* 
	** Functions to create Packets 
	*/

	void					_createResponsePacket(ERROR_PROTO err);
	void					_createConnectPacket(void);
	void					_createActionPacket(ACTION act);
	void					_createParametersPacket(int, int);
	void					_addPositionPacket(AObject *);
	void					_addPositionPacket(int, int, int, int, const char *);
	void					_putPositionPacketOnList(void);
	void					_createPingCommand(void);
	void					_createPongCommand(void);
	void					_createDisconnectCommand(void);

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
	uint16_t				_getHeaderSize(void) const;
	uint8_t					_getArrayPositionLenght(void) const;
	uint16_t				_getPositionPosX(size_t) const;
	uint16_t				_getPositionPosY(size_t) const;
	uint16_t				_getPositionSizeX(size_t) const;
	uint16_t				_getPositionSizeY(size_t) const;
	uint8_t					_getPositionSpriteLenght(size_t) const;
	uint8_t					*_getPositionSpriteData(size_t) const;
	uint8_t					_getResponseOpcode(void) const;
	uint8_t					_getParametersDifficulty(void) const;
	uint8_t					_getParametersNbGame(void) const;
	uint8_t					_getActionOpcode(void) const;
	unsigned int			_getSizePacketHeader(void) const;
};

#endif // !PROTOCOLE_HPP_