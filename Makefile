
###############################################################################
# Path

DESTDIR		:= $(CURDIR)/out

PREFIX		:= /system
BINDIR		:= $(PREFIX)/sbin

###############################################################################
# Compile

CC	:= $(CROSS_COMPILE)gcc

CFLAGS	= $(EXTRA_CFLAGS)
LDFLAGS	= $(EXTRA_LDFLAGS)

###############################################################################
# Options

#AUTOSTART	:= y

###############################################################################
# Board Setting

BOARD	:= 
CFLAGS	+= -DBOARD_$(BOARD)

###############################################################################
# Target rules

CFLAGS	+=
LDFLAGS	+= -lmdsapi -llogd 

OBJS	:= src/update.o src/update_api.o src/main.o src/file_check.o 
OBJS	+= src/util.o src/ftp_list.o src/pack_list.o

APP	:= dlpkg3

all:		$(APP)

$(APP):		$(OBJS)
	$(Q)$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install:	install-binary

install-binary:	$(APP)
	$(Q)$(call check_install_dir, $(DESTDIR)$(BINDIR))
	$(Q)fakeroot cp -v $(APP) $(DESTDIR)$(BINDIR)/$(APP)

clean:
	$(Q)rm -vrf $(APP) $(OBJS) 

uninstall:
	$(Q)rm -vrf $(DESTDIR)$(BINDIR)/$(APP)


# Functions

define check_install_dir
	if [ ! -d "$1" ]; then mkdir -p $1; fi
endef

