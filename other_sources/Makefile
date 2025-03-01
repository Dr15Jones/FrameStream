PRESENT_DIR := ${PWD}
OSNAME := $(shell uname)

default: setup lib/$(OSNAME)/libreadline_cleo3.a lib/$(OSNAME)/libtcl8.6.so lib/$(OSNAME)/libtk8.6.so

setup::
	-test -d lib || mkdir -p lib
	-test -d lib/$(OSNAME) || mkdir -p lib/$(OSNAME)

lib/$(OSNAME)/libreadline_cleo3.a:
	-(cd readline; ./configure; gmake; cp libreadline.a ../lib/$(OSNAME)/libreadline_cleo3.a; cp libhistory.a ../lib/$(OSNAME)/libhistory_cleo3.a)

lib/$(OSNAME)/libtcl8.6.so:
	-(cd tcltk/tcl8.6.16/unix; ./configure --prefix=$(PRESENT_DIR)/tcltk; gmake; gmake install; cd $(PRESENT_DIR)/tcltk/lib; cp libtcl8.6.so $(PRESENT_DIR)/lib/$(OSNAME)/;)
lib/$(OSNAME)/libtk8.6.so:
	-(cd tcltk/tk8.6.16/unix; ./configure --with-tcl=$(PRESENT_DIR)/tcltk/tcl8.6.16/unix --prefix=$(PRESENT_DIR)/tcltk; gmake; gmake install; cd $(PRESENT_DIR)/tcltk/lib; cp libtk8.6.so $(PRESENT_DIR)/lib/$(OSNAME)/;)
