include make.cfg

COLOR_OBJ     = $(COLOR_CYAN)
COLOR_TAG     = $(COLOR_YELLOW)
COLOR_TXT     = $(COLOR_GREEN)
############################################################################


MAKE=make
RM=@rm -rf
BUILD_PWD=$(shell pwd)
DEMO_SRCDIR=$(BUILD_PWD)/demo
CORE_SRCDIR=$(BUILD_PWD)/core
ENCODING_SRCDIR=$(BUILD_PWD)/encoding
SOCKET_SRCDIR=$(BUILD_PWD)/socket
TYPE_SRCDIR=$(BUILD_PWD)/type
LOGGER_SRCDIR=$(BUILD_PWD)/logger
LIB_SRCDIR_LIST=$(CORE_SRCDIR) $(ENCODING_SRCDIR) $(SOCKET_SRCDIR) $(TYPE_SRCDIR) $(DEMO_SRCDIR) 
############################################################################


all: prepare
	@for DIR in $(LIB_SRCDIR_LIST); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

prepare:
	@echo $(BUILD_PWD)
	@-if [ ! -d $(LIB_ROOT_DIR) ];then mkdir $(LIB_ROOT_DIR); fi
	@-if [ ! -d $(BIN_ROOT_DIR) ];then mkdir $(BIN_ROOT_DIR); fi

cores: prepare
	@for DIR in $(CORE_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

encodings: prepare
	@for DIR in $(ENCODING_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

sockets: prepare
	@for DIR in $(SOCKET_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

types: prepare
	@for DIR in $(TYPE_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

loggers: prepare
	@for DIR in $(LOGGER_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

demo: prepare
	@for DIR in $(DEMO_SRCDIR); do \
        cd $$DIR; \
        $(MAKE) all || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

clean: prepare
	@for DIR in $(LIB_SRCDIR_LIST); do \
        cd $$DIR; \
        $(MAKE) clean || exit "$$?"; \
        cd $(BUILD_PWD); \
    done

distclean:
	@for DIR in $(LIB_SRCDIR_LIST); do \
        cd $$DIR; \
        $(MAKE) distclean || exit "$$?"; \
        cd $(BUILD_PWD); \
    done
	-$(RM) $(LIB_ROOT_DIR)
	-$(RM) $(BIN_ROOT_DIR)
