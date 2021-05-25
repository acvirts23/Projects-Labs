########################################################
# Dr. Zoppetti: Makefile example
########################################################

########################################################
# Variable definitions
########################################################
# C compiler
CC      = gcc

# C compiler flags
CFLAGS = -g -Wall -Wextra -Werror -pedantic
#CFLAGS = -O3 -Wall -Wextra -Werror -pedantic

# Linker flags
LDFLAGS  := 

# Libraries we're using, prefaced with "-l"
LDLIBS   := 

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

shellPrelude : shellPrelude.o
	$(LINK.o) $(LDFLAGS) $^ $(LDLIBS) -o $@

shellPrelude.o : shellPrelude.c

#############################################################

.PHONY : clean

clean :
	@$(RM) shellPrelude a.out core
	@$(RM) *.o *~ *.d

#############################################################