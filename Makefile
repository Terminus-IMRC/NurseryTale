PROG=NurseryTale
SRCS=main.c mod_coordsAndSteps.c tale.c searched_index.c fd_utils.c will_and_die.c
HDRS=def.h
SRCS_XDEP=main.c mod_coordsAndSteps.c tale.c searched_index.c
NONEED_DEP_TARGETS+=clean line

OBJS=$(SRCS:%.c=%.c.o)
OBJS_XDEP=$(SRCS_XDEP:%.c=%.c.o)
DEPS=$(SRCS:%.c=%.c.d)
ALLDEP=$(MAKEFILE_LIST_SANS_DEPS)
TOCLEAN=index.db

all: $(PROG)

# check whether NONEED_DEP_TARGETS are in MAKECMDGOALS
ifeq '$(filter-out $(NONEED_DEP_TARGETS), $(MAKECMDGOALS))' '$(MAKECMDGOALS)'
 sinclude $(DEPS)
else
 # if so and there are more than 1 targets in MAKECMDGOALS, it would cause dependency files missing so say error
 ifneq '$(words $(MAKECMDGOALS))' '1'
  $(error Specify only one target if you want to make target that needs no dependency file)
 endif
endif

MAKEFILE_LIST_SANS_DEPS=$(filter-out %.d, $(MAKEFILE_LIST))

CC:=cc
HEADERFLAGS:=-I.
OPTFLAGS:=-pipe -O0 -g
WARNFLAGS:=-ansi -pedantic -Wall -Wextra -W -Wundef -Wshadow -Wcast-qual -Winline -Wno-long-long -fsigned-char
RM:=rm -r -f
WC:=wc -c -l

COMPILE.c=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(DEPFLAGS) $(ADDCFLAGS) $(CFLAGS) -c
COMPILE.dep=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(DEPFLAGS) $(ADDCFLAGS) $(CFLAGS) -M -MP -MT $<.o -MF $@
LINK.o=$(CC) $(OPTFLAGS) $(WARNFLAGS) $(LINKFLAGS) $(LDFLAGS)

X?=3
X_VALFLAGS=-DX=$(X)
XNUM=.x
$(shell ([ -f $(XNUM) ] && [ `cat $(XNUM)` -eq $(X) ]) || echo $(X) >$(XNUM))

$(OBJS_XDEP): $(XNUM)
$(OBJS_XDEP): DEPFLAGS+=$(X_VALFLAGS)


$(PROG): $(OBJS) $(ALLDEP)
	$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o: %.c $(ALLDEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.c.d: %.c $(ALLDEP)
	$(COMPILE.dep) $<

run: $(PROG)
	./$(PROG)

.PHONY: line
line:
	$(WC) $(SRCS) $(MAKEFILE_LIST_SANS_DEPS)

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(XNUM)
	$(RM) $(TOCLEAN)
