##
## Makefile for Makefile
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:05 2015 Florent Beaurain
## Last update Mon Dec 14 15:52:50 2015 Pierre Noel
##

include			source.mk

NAME_S			=	binServer

NAME_C			=	binClient

CXX			?=	g++

DEBUG			?=	no

CXXFLAGS_S		=	-I$(DIR_SERVER_I)

CXXFLAGS_C		=	-I$(DIR_CLIENT_I) -I$(DIR_LIB)SFML-Unix/include -l$(DIR_LIB)SFML-Unix

CXXFLAGS_COMMON		=	-I$(DIR_COMMON_I)

ifeq ($(CXX), clang++)
CXXFLAGS		+=	-Weverything -Wno-padded -pthread -lpthread
else
CXXFLAGS		+=	-pthread -lpthread  -W -Wall -Wextra -std=c++11
endif

ifeq ($(DEBUG), yes)
CXXFLAGS		+=	-g
endif

OBJS_SERVER		=	$(SERVER:.cpp=.o)
OBJS_COMMON		=	$(COMMON:.cpp=.o)
OBJS_CLIENT		=	$(CLIENT:.cpp=.o)

$(OBJS_SERVER):		$(DIR_SERVER)%.o: $(DIR_SERVER)%.cpp
			$(CXX) -c $(CXXFLAGS) $(CXXFLAGS_S) $(CXXFLAGS_COMMON) -g $< -o $@

$(OBJS_COMMON):		$(DIR_COMMON)%.o: $(DIR_COMMON)%.cpp
			$(CXX) -c $(CXXFLAGS) $(CXXFLAGS_COMMON) -g $< -o $@

$(OBJS_CLIENT):		$(DIR_CLIENT)%.o: $(DIR_CLIENT)%.cpp
			$(CXX) -c $(CXXFLAGS) $(CXXFLAGS_C) $(CXXFLAGS_COMMON) -g $< -o $@

all:			$(NAME_S) $(NAME_C)

$(NAME_C):		$(OBJS_COMMON) $(OBJS_CLIENT)
			$(CXX) -o $(NAME_C) $(OBJS_COMMON) $(OBJS_CLIENT) $(CXXFLAGS) $(CXXFLAGS_C)

$(NAME_S):		$(OBJS_COMMON) $(OBJS_SERVER)
			$(CXX) -o $(NAME_S) $(OBJS_SERVER) $(OBJS_COMMON) $(CXXFLAGS) $(CXXFLAGS_S)
clean:
			@rm -vf $(OBJS_SERVER) $(OBJS_COMMON) $(OBJS_CLIENT)

fclean:			clean
			@rm -vf $(NAME_S) $(NAME_C)

re:			fclean all

.PHONY:			clean fclean re
