#include "Protocole.hpp"

Protocole::Protocole(unsigned int id) {
	this->_posInArray = 0;
	this->_id = id;
	_generateData[0] = &Protocole::_setResponseStruct;
	_generateData[1] = NULL;
	_generateData[2] = &Protocole::_setParametersStruct;
	_generateData[3] = &Protocole::_setActionStruct;
	_generateData[4] = &Protocole::_setPositionStruct;
	_generateData[5] = NULL;
	_generateData[6] = NULL;
	_generateData[7] = NULL;
	_generateData[8] = &Protocole::_setScrollingPacket;
	_generateData[9] = &Protocole::_setIdentifiantPacket;
	_generateData[10] = &Protocole::_setDeadEntityPacket;
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
	this->_header.id = this->_id;
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
	this->_header.id = this->_id;
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
	this->_header.id = this->_id;
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
	this->_header.id = this->_id;
	this->_header.size = sizeof(actionPacket);
	this->_action.action = (uint8_t)act;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_action), sizeof(actionPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_addPositionPacket(unsigned int posX, unsigned int posY, unsigned int sizeX, unsigned int sizeY, unsigned int sprite, const char * path, const char * type) {
	this->_arrayPositionPacket.lenght = static_cast<uint8_t>((this->_posInArray + 1) * sizeof(positionPacket));
	this->_arrayPositionPacket.data[this->_posInArray].pos_x = (uint16_t)posX;
	this->_arrayPositionPacket.data[this->_posInArray].pos_y = (uint16_t)posY;
	this->_arrayPositionPacket.data[this->_posInArray].size_x = (uint16_t)sizeX;
	this->_arrayPositionPacket.data[this->_posInArray].size_y = (uint16_t)sizeY;
	memcpy(&(this->_arrayPositionPacket.data[this->_posInArray].path.data), path, strlen(path));
	this->_arrayPositionPacket.data[this->_posInArray].path.lenght = (uint8_t)(strlen(path));
	memcpy(&(this->_arrayPositionPacket.data[this->_posInArray].sprite.data), type, strlen(type));
	this->_arrayPositionPacket.data[this->_posInArray].sprite.lenght = (uint8_t)(strlen(type));
	this->_arrayPositionPacket.data[this->_posInArray].type = sprite;
	this->_posInArray = this->_posInArray + 1;
}

void		Protocole::_putPositionPacketOnList(void) {
	char *result = new char[sizeof(headerPacket) + sizeof(arrayPositionPacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(arrayPositionPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 4;
	this->_header.id = this->_id;
	this->_header.size = sizeof(arrayPositionPacket);
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_arrayPositionPacket), sizeof(arrayPositionPacket));
	this->_posInArray = 0;
	this->_listPacket.push_back(result);
}

void		Protocole::_createPingPacket(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 5;
	this->_header.id = this->_id;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole:: _createPongPacket(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 6;
	this->_header.id = this->_id;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createDisconnectPacket(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 7;
	this->_header.id = this->_id;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createScrollingPacket(int scroll) {
	char	*result = new char[sizeof(headerPacket) + sizeof(scrollingPacket)];
	memset(result, 0, sizeof(headerPacket) + sizeof(scrollingPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_scroll), 0, sizeof(scrollingPacket));
	this->_header.opcode = 8;
	this->_header.id = this->_id;
	this->_header.size = sizeof(scrollingPacket);
	this->_action.action = (uint8_t)scroll;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_scroll), sizeof(scrollingPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createQuitPacket(void) {
	char *result = new char[sizeof(headerPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	this->_header.opcode = 9;
	this->_header.id = this->_id;
	this->_header.size = 0;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createIdentifiantPacket(unsigned int idPlayer, unsigned int nbGame) {
	char *result = new char[sizeof(headerPacket) + sizeof(identifantPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_identifiant), 0, sizeof(identifantPacket));
	this->_header.opcode = 10;
	this->_header.id = this->_id;
	this->_header.size = sizeof(identifantPacket);
	this->_identifiant.idPlayer = idPlayer;
	this->_identifiant.nbGame = nbGame;
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_identifiant), sizeof(identifantPacket));
	this->_listPacket.push_back(result);
}

void		Protocole::_createDeadEntityPacket(const std::string &type, const std::string &name) {
	char *result = new char[sizeof(headerPacket) + sizeof(deadEntityPacket)];
	memset(result, 0, sizeof(headerPacket));
	memset(&(this->_header), 0, sizeof(headerPacket));
	memset(&(this->_deadEntity), 0, sizeof(deadEntityPacket));
	this->_header.opcode = 11;
	this->_header.id = this->_id;
	this->_header.size = sizeof(deadEntityPacket);
	this->_deadEntity.name.lenght = static_cast<uint8_t>(name.size());
	memcpy(&(this->_deadEntity.name.data), name.data(), name.size());
	this->_deadEntity.type.lenght = static_cast<uint8_t>(type.size());
	memcpy(&(this->_deadEntity.type.data), type.data(), type.size());
	memcpy(result, &(this->_header), sizeof(headerPacket));
	memcpy(result + sizeof(headerPacket), &(this->_identifiant), sizeof(identifantPacket));
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

void		Protocole::_setScrollingPacket(const char *packet) {
	memcpy(&(this->_scroll), packet, sizeof(scrollingPacket));
}

void		Protocole::_setIdentifiantPacket(const char *packet) {
	memcpy(&(this->_identifiant), packet, sizeof(identifantPacket));
}

void		Protocole::_setDeadEntityPacket(const char *packet) {
	memcpy(&(this->_deadEntity), packet, sizeof(deadEntityPacket));
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

uint8_t			Protocole::_getHeaderId(void) const {
	return this->_header.id;
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

uint8_t			Protocole::_getPositionPathLength(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].path.lenght;
}

uint8_t			*Protocole::_getPositionPathData(size_t pos) const {
	return (uint8_t *)this->_arrayPositionPacket.data[pos].path.data;
}

uint8_t			Protocole::_getPositionType(size_t pos) const {
	return this->_arrayPositionPacket.data[pos].type;
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

uint8_t			Protocole::_getScrolling(void) const {
	return this->_scroll.scroll;
}

uint8_t			Protocole::_getIdentifiantIdPlayer(void) const {
	return this->_identifiant.idPlayer;
}

uint8_t			Protocole::_getIdentifiantNbGame(void) const {
	return this->_identifiant.nbGame;
}

uint8_t			*Protocole::_getDeadEntityNameData(void) const {
	return (uint8_t *)this->_deadEntity.name.data;
}

uint8_t			Protocole::_getDeadEntityNameLenght(void) const {
	return this->_deadEntity.name.lenght;
}

uint8_t			*Protocole::_getDeadEntityTypeData(void) const {
	return (uint8_t *)this->_deadEntity.type.data;
}

uint8_t			Protocole::_getDeadEntityTypeLenght(void) const {
	return this->_deadEntity.type.lenght;
}

unsigned int	Protocole::_getSizePacket(const char *packet) const {
	headerPacket	tmp;
	memset(&tmp, 0, sizeof(headerPacket));
	memcpy(&tmp, packet, sizeof(headerPacket));
	return (unsigned int)(sizeof(headerPacket) + tmp.size);
}

unsigned int	Protocole::_getSizePacketHeader(void) const {
	return sizeof(headerPacket);
}

/*
** Setter
*/

void			Protocole::_setId(unsigned int id) {
	this->_id = id;
}