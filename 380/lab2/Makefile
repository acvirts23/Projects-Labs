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

prelude : prelude.o
	$(LINK.o) $(LDFLAGS) $^ $(LDLIBS) -o $@

prelude.o : prelude.c

#############################################################

.PHONY : clean

clean :
	@$(RM) prelude a.out core
	@$(RM) *.o *~ *.d

#############################################################