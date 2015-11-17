##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Tue Nov 17 19:14:05 2015 Florent BEAURAIN
##

include			source.mk

NAME			=	binServer

OBJS			=	$(SRC:.cpp=.o)

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS		+=	-Iserver/inc

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded
else
CXXFLAGS		+=	-W -Wall -Wextra
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CXX) -o $(NAME) $(OBJS)
clean:
			@rm -vf $(OBJS)

fclean:			clean
			@rm -vf $(NAME)

re:			fclean all

.PHONY:			clean fclean re
