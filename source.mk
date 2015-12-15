##
## source.mk for source.mk
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:32 2015 Florent Beaurain
## Last update Mon Dec 14 17:07:27 2015 Pierre Noel
##

## Server sources

DIR_SERVER		=	RType/Server/
DIR_SERVER_S		=	RType/Server/Sources/
DIR_SERVER_I		=	RType/Server/Includes/

SERVER			+=	$(DIR_SERVER_S)main.cpp
SERVER			+=	$(DIR_SERVER_S)Client.cpp
SERVER			+=	$(DIR_SERVER_S)Network.cpp
SERVER			+=	$(DIR_SERVER_S)Game.cpp
SERVER			+=	$(DIR_SERVER_S)HandleThread.cpp
SERVER			+=	$(DIR_SERVER_S)Monster.cpp
SERVER			+=	$(DIR_SERVER_S)Player.cpp
SERVER			+=	$(DIR_SERVER_S)Obstacle.cpp
SERVER			+=	$(DIR_SERVER_S)AObject.cpp
SERVER			+=	$(DIR_SERVER_S)Missile.cpp

## Common sources

DIR_COMMON		=	RType/Common/
DIR_COMMON_S		=	RType/Common/Sources/
DIR_COMMON_I		=	RType/Common/Includes/

COMMON			+=	$(DIR_COMMON_S)USocket.cpp
COMMON			+=	$(DIR_COMMON_S)UTimer.cpp
COMMON			+=	$(DIR_COMMON_S)UThread.cpp
COMMON			+=	$(DIR_COMMON_S)UMutex.cpp
COMMON			+=	$(DIR_COMMON_S)Tools.cpp
COMMON			+=	$(DIR_COMMON_S)UConditionVariable.cpp
COMMON			+=	$(DIR_COMMON_S)Protocole.cpp

## Client sources

DIR_CLIENT		=	RType/Client/
DIR_CLIENT_S		=	RType/Client/Sources/
DIR_CLIENT_I		=	RType/Client/Includes/

#CLIENT			+=	$(DIR_CLIENT_S)Game.cpp
CLIENT                  +=	$(DIR_CLIENT_S)main.cpp
#CLIENT 	        +=	$(DIR_CLIENT_S)Network.cpp
CLIENT                  +=	$(DIR_CLIENT_S)SFML.cpp
CLIENT                  +=	$(DIR_CLIENT_S)Sound.cpp
CLIENT                  +=	$(DIR_CLIENT_S)SoundFactory.cpp
CLIENT                  +=	$(DIR_CLIENT_S)RSprite.cpp
CLIENT                  +=	$(DIR_CLIENT_S)TextureFactory.cpp
CLIENT			+=	$(DIR_CLIENT_S)RTexture.cpp
CLIENT			+=	$(DIR_CLIENT_S)SpriteFactory.cpp

DIR_LIB			=	RType/Common/Library/
