##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Mon Dec 14 10:35:12 2015 Probola
##

include			source.mk

NAME			=	binServer

OBJS_SERVER		=	$(SERVER:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-Iserver/Includes -Icommon/Includes -Iclient/Includes

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-pthread -lpthread  -W -Wall -Wextra -std=c++11
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME)

$(NAME):		$(OBJS_COMMON) $(OBJS_SERVER)
			$(CXX) -o $(NAME) $(OBJS_SERVER) $(OBJS_COMMON)
clean:
			@rm -vf $(OBJS_SERVER) $(OBJS_COMMON)

fclean:			clean
			@rm -vf $(NAME)

re:			fclean all

.PHONY:			clean fclean re
