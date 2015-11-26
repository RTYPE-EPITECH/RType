##
## source.mk for source.mk
## 
## Made by Florent Beaurain
## Login   <beauraF@epitech.net>
## 
## Started on  Sat Jul 25 17:11:32 2015 Florent Beaurain
## Last update Thu Nov 26 15:46:12 2015 Florent BEAURAIN
##

## Server sources

DIR_SERVER		=	server/Sources/

SERVER			+=	$(DIR_SERVER)main.cpp
SERVER			+=	$(DIR_SERVER)USocket.cpp



## Common sources

DIR_COMMON		=	common/Sources/

COMMON			+=	$(DIR_COMMON)USocket.cpp
