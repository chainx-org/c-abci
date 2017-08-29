include ../../make.cfg

COLOR_OBJ     = $(COLOR_CYAN)
COLOR_TAG     = $(COLOR_YELLOW)
COLOR_TXT     = $(COLOR_GREEN)
############################################################################


CC:=@${CC}
AR=@ar -cr
RM=@rm -rf
INCDIR += -I../include
CFLAG +=-g
SRCDIR=./
BINDIR=./bin
OBJDIR=./obj
TARGET_BIN=$(BINDIR)/test
TARGET=$(TARGET_BIN)
SRCLIST=$(wildcard *.c)
OBJLIST=$(SRCLIST:%.c=$(OBJDIR)/%.o)
LIBS += -L$(ABCIROOTDIR)/lib/ -ldlist
############################################################################


ifeq ($(BIN_ROOT_DIR),)
	CP=
else
	CP=@cp -f $(TARGET_BIN) $(BIN_ROOT_DIR)
endif
############################################################################


all: prepare $(TARGET)

prepare:
	@-if [ ! -d $(OBJDIR) ];then mkdir $(OBJDIR); fi
	@-if [ ! -d $(BINDIR) ];then mkdir $(BINDIR); fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(ECHO) $(COLOR_TXT)"\t- COMPILE\t===>\t"$(COLOR_OBJ)"$(notdir $@)"$(COLOR_NONE)
	$(CC) $(INCDIR) $(CFLAG) -o $@ $<

$(TARGET_BIN): $(OBJLIST)
	@echo $(LIBS)
	$(ECHO) $(COLOR_TXT)"\n\t- DYNAMIC\t===>\t"$(COLOR_TAG)"$(notdir $(TARGET_BIN))"$(COLOR_NONE)
	$(LINK) -o $@ $^ $(LIBS) 
	$(ECHO) $(COLOR_TXT)"\t- DYNAMIC\t>>>>\t"$(COLOR_RED)"$(notdir $@)"$(COLOR_TXT)"\t<<<  COMPLETE"$(COLOR_NONE)
	-$(CP)

clean:
	-$(RM) $(OBJDIR)

distclean:
	-$(RM) $(BIN_ROOT_DIR)/$(notdir $(TARGET_BIN))
	-$(RM) $(OBJDIR)
	-$(RM) $(BINDIR)

rebuild: distclean  all

.PHONY: all prepare clean distclean rebuild
