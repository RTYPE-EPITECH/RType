##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Thu Nov 26 13:10:46 2015 Pierre Noel
##

include			source.mk

NAME			=	binServer

OBJS_SERVER		=	$(SERVER:.cpp=.o)
OBJS_COMMON		=	$(COMMON:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-Iserver/Includes -Icommon/Includes

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-W -Wall -Wextra
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME)

$(NAME):		$(OBJS_SERVER) $(OBJS_COMMON)
			$(CXX) -o $(NAME) $(OBJS_SERVER) $(OBJS_COMMON)
clean:
			@rm -vf $(OBJS_SERVER) $(OBJS_COMMON)

fclean:			clean
			@rm -vf $(NAME)

re:			fclean all

.PHONY:			clean fclean re
