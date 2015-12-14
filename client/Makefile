##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Mon Dec 14 10:44:16 2015 Probola
##


NAME			=	TestClient

SRC			=	Sources/main.cpp		\
				Sources/Game.cpp		\
				Sources/Network.cpp		\
				Sources/RSprite.cpp		\
				Sources/RTexture.cpp		\
				Sources/SFML.cpp		\
				Sources/Sound.cpp		\
				Sources/SoundFactory.cpp	\
				SpriteFactory.cpp		\
				TextureFactory.cpp		\
				../common/Sources/Protocole.cpp	\
				../common/Sources/Tools.cpp	\
				../common/UConditionVariable.cpp\
				../common/UMutex.cpp		\
				../common/USocket.cpp		\
				../common/UThread.cpp		\
				../common/UTimer.cpp		\
				../common/WConditionVariable.cpp\
				../common/WDynamicLibrary.cpp	\
				../WMutex.cpp			\
				../WSocket.cpp			\
				../WThread.cpp			\
				../WTimer.cpp

OBJS_COMMON		=	$(SRC:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-I./Includes -I../common/Includes -I../common/Library/SFML-Unix/include -l../common/Library/SFML-Unix

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-pthread -lpthread  -W -Wall -Wextra -std=c++11
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME)

$(NAME):		$(OBJS_COMMON)
			$(CXX) -o $(NAME) $(OBJS_COMMON)
clean:
			@rm -vf $(OBJS_COMMON)

fclean:			clean
			@rm -vf $(NAME)

re:			fclean all

.PHONY:			clean fclean re
