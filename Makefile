##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Mon Dec 14 13:42:26 2015 Probola
##

include			source.mk

NAME			=	binServer

OBJS_SERVER		=	$(SERVER:.cpp=.o)
OBJS_COMMON		=	$(COMMON:.cpp=.o)
OBJS_CLIENT		=	$(CLIENT:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-IRType/Server/Includes -IRType/Common/Includes -IRType/Client/Includes -IRType/Common/Library/SFML-Unix/include -lRType/Common/Library/SFML-Unix

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-pthread -lpthread  -W -Wall -Wextra -std=c++11
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME)

$(NAME):		$(OBJS_COMMON) $(OBJS_SERVER) $(OBJS_CLIENT)
			$(CXX) -o $(NAME) $(OBJS_SERVER) $(OBJS_COMMON) $(OBJS_CLIENT)
clean:
			@rm -vf $(OBJS_SERVER) $(OBJS_COMMON) $(OBJS_CLIENT)

fclean:			clean
			@rm -vf $(NAME)

re:			fclean all

.PHONY:			clean fclean re
