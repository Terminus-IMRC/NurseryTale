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

ifeq '$(shell for f in $(NONEED_DEP_TARGETS); do if echo $(strip $(MAKECMDGOALS)) | tr -s " " "\n" | grep -q "^$$f$$"; then echo $$f; break; fi; done)' ''
 sinclude $(DEPS)
else
 ifneq '$(shell echo $(strip $(MAKECMDGOALS)) | tr -s " " "\n" | wc -l)' '1'
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
COMPILE.dep=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(DEPFLAGS) $(ADDCFLAGS) $(CFLAGS) -MM -MP -MT $<.o -MF $@
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
