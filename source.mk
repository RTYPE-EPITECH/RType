##
## source.mk for source.mk
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:32 2015 Florent Beaurain
## Last update Thu Dec  3 16:43:33 2015 Probola
##

## Server sources

DIR_SERVER		=	server/Sources/

SERVER			+=	$(DIR_SERVER)main.cpp
SERVER			+=	$(DIR_SERVER)Client.cpp
SERVER			+=	$(DIR_SERVER)Network.cpp
SERVER			+=	$(DIR_SERVER)Game.cpp
SERVER			+=	$(DIR_SERVER)HandleThread.cpp
SERVER			+=	$(DIR_SERVER)Monster.cpp
SERVER			+=	$(DIR_SERVER)Player.cpp
SERVER			+=	$(DIR_SERVER)Obstacle.cpp
SERVER			+=	$(DIR_SERVER)AObject.cpp
SERVER			+=	$(DIR_SERVER)Missile.cpp

## Common sources

DIR_COMMON		=	common/Sources/

COMMON			+=	$(DIR_COMMON)USocket.cpp
COMMON			+=	$(DIR_COMMON)UTimer.cpp
COMMON			+=	$(DIR_COMMON)UThread.cpp
COMMON			+=	$(DIR_COMMON)UMutex.cpp
COMMON			+=	$(DIR_COMMON)Tools.cpp
COMMON			+=	$(DIR_COMMON)UConditionVariable.cpp
COMMON			+=	$(DIR_COMMON)Protocole.cpp

## Client sources

DIR_CLIENT		=	client/Sources/

#CLIENT			+=	$(DIR_CLIENT)Game.cpp
CLIENT                  +=	$(DIR_CLIENT)main.cpp
#CLIENT 	                +=	$(DIR_CLIENT)Network.cpp
CLIENT                  +=	$(DIR_CLIENT)SFML.cpp
CLIENT                  +=	$(DIR_CLIENT)Sound.cpp
CLIENT                  +=	$(DIR_CLIENT)SoundFactory.cpp
CLIENT                  +=	$(DIR_CLIENT)RSprite.cpp
CLIENT                  +=	$(DIR_CLIENT)TextureFactory.cpp
CLIENT			+=	$(DIR_CLIENT)RTexture.cpp
CLIENT			+=	$(DIR_CLIENT)SpriteFactory.cpp
CLIENT			+=	$(DIR_CLIENT)TextureFactory.cpp
