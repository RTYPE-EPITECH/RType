#include "Protocole.hpp"
#include "AObject.hpp"

Protocole::Protocole(void) {
	this->_posInArray = 0;
	_generateData[0] = &Protocole::_setResponseStruct;
	_generateData[1] = NULL;
	_generateData[2] = &Protocole::_setParametersStruct;
	_generateData[3] = &Protocole::_setActionStruct;
	_generateData[4] = &Protocole::_setPositionStruct;
	_generateData[5] = NULL;
	_generateData[6] = NULL;
	_generateData[7] = NULL;
}

Protocole::~Protocole(void) {}

/*
** Functions to create Packets
*/

void		Protocole::_createResponsePacket(ERROR_PROTO err) {
	char	*result = new char[sizeof(headerPacket) + sizeof(responsePacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(responsePacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_response), 0, sizeof(responsePacket));
	this->_header.opcode = 0;
	this->_header.size = sizeof(responsePacket);
	this->_response.opcode = (uint8_t)err;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_response), sizeof(responsePacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createConnectPacket(void) {
	char	*result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 1;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createParametersPacket(int difficulty, int nbGame) {
	char	*result = new char[sizeof(headerPacket) + sizeof(parametersPacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(parametersPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_params), 0, sizeof(parametersPacket));
	this->_header.opcode = 2;
	this->_header.size = sizeof(parametersPacket);
	this->_params.difficulty = (uint8_t)difficulty;
	this->_params.nbGame = (uint8_t)nbGame;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_params), sizeof(parametersPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createActionPacket(ACTION act) {
	char	*result = new char[sizeof(headerPacket) + sizeof(actionPacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(actionPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_action), 0, sizeof(actionPacket));
	this->_header.opcode = 3;
	this->_header.size = sizeof(actionPacket);
	this->_action.action = (uint8_t)act;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_action), sizeof(actionPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_addPositionPacket(AObject * obj)
{
	_addPositionPacket(obj->getX(),
		obj->getY(),
		obj->getWidth(),
		obj->getHeight(),
		"Type");
	//obj->getType()
}

void		Protocole::_addPositionPacket(int posX, int posY, int sizeX, int sizeY, const char *sprite) {
	this->_arrayPositionPacket.lenght = (this->_posInArray + 1) * sizeof(positionPacket);
	this->_arrayPositionPacket.data[this->_posInArray].pos_x = (uint16_t)posX;
	this->_arrayPositionPacket.data[this->_posInArray].pos_y = (uint16_t)posY;
	this->_arrayPositionPacket.data[this->_posInArray].size_x = (uint16_t)sizeX;
	this->_arrayPositionPacket.data[this->_posInArray].size_y = (uint16_t)sizeY;
	memcpy(&(this->_arrayPositionPacket.data[this->_posInArray].sprite.data), sprite, strlen(sprite));
	this->_arrayPositionPacket.data[this->_posInArray].sprite.lenght = (uint8_t)(strlen(sprite));
	this->_posInArray = this->_posInArray + 1;
}

void		Protocole::_putPositionPacketOnList(void) {
	char *result = new char[sizeof(headerPacket) + sizeof(arrayPositionPacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(arrayPositionPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 4;
	this->_header.size = sizeof(arrayPositionPacket);
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_arrayPositionPacket), sizeof(arrayPositionPacket));
	this->_posInArray = 0;
	this->_listPacket.push_back(result);
}

void		Protocole::_createPingCommand(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 5;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole:: _createPongCommand(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 6;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createDisconnectCommand(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 7;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

/*
** Functions to handle new Packets
*/

const char		*Protocole::_linkPacketHeaderBody(const char *header, const char *body) const {
	headerPacket tmp;
	memset(&tmp, 0, sizeof(headerPacket));
	memcpy(&tmp, header, sizeof(headerPacket));
	char *result = new char[sizeof(headerPacket) + tmp.size];
	memset(result, 0, sizeof(headerPacket) + tmp.size);
	memcpy(result, header, sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), body, tmp.size);
	return result;
}

void		Protocole::_setNewPacketHeader(const char *packet) {
	memcpy(&(this->_header), packet, sizeof(headerPacket));
}

void		Protocole::_setNewPacket(const char *packet) {
	_setNewPacketHeader(packet);
	if (this->_header.size != 0)
		(this->*_generateData[this->_header.opcode])(packet);
}
void		Protocole::_setResponseStruct(const char *packet) {
	memcpy(&(this->_response), packet, sizeof(responsePacket));
}

void		Protocole::_setParametersStruct(const char *packet) {
	memcpy(&(this->_params), packet, sizeof(parametersPacket));
}

void		Protocole::_setActionStruct(const char *packet) {
	memcpy(&(this->_action), packet, sizeof(actionPacket));
}

void		Protocole::_setPositionStruct(const char *packet) {
	memcpy(&(this->_arrayPositionPacket), packet, sizeof(arrayPositionPacket));
}

/*
** Getters
*/

char		*Protocole::_getLastPacket(void) const {
	return _listPacket.back();
}

std::vector<char *>		Protocole::_getListPacket(void) const {
	return _listPacket;
}

uint8_t			Protocole::_getHeaderOpcode(void) const {
	return this->_header.opcode;
}

uint16_t		Protocole::_getHeaderSize(void) const {
	return this->_header.size;
}

uint8_t			Protocole::_getArrayPositionLenght(void) const {
	return this->_arrayPositionPacket.lenght;
}

uint16_t		Protocole::_getPositionPosX(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].pos_x;
}

uint16_t		Protocole::_getPositionPosY(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].pos_y;
}

uint16_t		Protocole::_getPositionSizeX(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].size_x;
}

uint16_t		Protocole::_getPositionSizeY(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].size_y;
}

uint8_t			Protocole::_getPositionSpriteLenght(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].sprite.lenght;
}

uint8_t			*Protocole::_getPositionSpriteData(size_t pos) const {
	return (uint8_t *)this->_arrayPositionPacket.data[pos].sprite.data;
}

uint8_t			Protocole::_getResponseOpcode(void) const {
	return this->_response.opcode;
}

uint8_t			Protocole::_getParametersDifficulty(void) const {
	return this->_params.difficulty;
}

uint8_t			Protocole::_getParametersNbGame(void) const {
	return this->_params.nbGame;
}

uint8_t			Protocole::_getActionOpcode(void) const {
	return this->_action.action;
}

unsigned int	Protocole::_getSizePacketHeader(void) const {
	return sizeof(headerPacket);
}