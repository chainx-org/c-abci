include ../make.cfg

COLOR_OBJ     = $(COLOR_CYAN)
COLOR_TAG     = $(COLOR_YELLOW)
COLOR_TXT     = $(COLOR_GREEN)
############################################################################


CC:=@${CC}
AR=@ar -cr
RM=@rm -rf
LIBS +=
INCDIR += -I./include
CFLAG +=-g
SRCDIR=./
LIBDIR=./lib
OBJDIR=./obj
TARGET_SO=$(LIBDIR)/libdlist.so
TARGET_AR=$(LIBDIR)/libsocket.a
TARGET=$(TARGET_SO) $(TARGET_AR)
SRCLIST=$(wildcard *.c)
OBJLIST=$(SRCLIST:%.c=$(OBJDIR)/%.o)
############################################################################


ifeq ($(LIB_ROOT_DIR),)
	CP=
else
	CP=@cp -f $(TARGET_SO) $(LIB_ROOT_DIR)
endif
############################################################################


all: prepare $(TARGET)

prepare:
	@-if [ ! -d $(OBJDIR) ];then mkdir $(OBJDIR); fi
	@-if [ ! -d $(LIBDIR) ];then mkdir $(LIBDIR); fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(ECHO) $(COLOR_TXT)"\t- COMPILE\t===>\t"$(COLOR_OBJ)"$(notdir $@)"$(COLOR_NONE)
	$(CC) $(INCDIR) $(CFLAG) -o $@ $<

$(TARGET_SO): $(OBJLIST)
	$(ECHO) $(COLOR_TXT)"\n\t- DYNAMIC\t===>\t"$(COLOR_TAG)"$(notdir $(TARGET_SO))"$(COLOR_NONE)
	$(LINK_SO) -o $@ $^ $(LIBS) 
	$(ECHO) $(COLOR_TXT)"\t- DYNAMIC\t>>>>\t"$(COLOR_RED)"$(notdir $@)"$(COLOR_TXT)"\t<<<  COMPLETE"$(COLOR_NONE)
	-$(CP)
	

$(TARGET_AR): $(OBJLIST)
	$(ECHO) $(COLOR_TXT)"\n\t- ARCHIVE\t===>\t"$(COLOR_TAG)"$(notdir $(TARGET_AR))"$(COLOR_NONE)
	$(AR) $@  $^ 
	$(ECHO) $(COLOR_TXT)"\t- ARCHIVE\t>>>>\t"$(COLOR_RED)"$(notdir $@)"$(COLOR_TXT)"\t<<<  COMPLETE"$(COLOR_NONE)

clean:
	-$(RM) $(OBJDIR)

distclean:
	-$(RM) $(LIB_ROOT_DIR)/$(notdir $(TARGET_SO))
	-$(RM) $(OBJDIR)
	-$(RM) $(LIBDIR)

rebuild: distclean  all

.PHONY: all prepare clean distclean rebuild
