PRESENT_DIR := ${PWD}
OSNAME := $(shell uname)

default: setup lib/$(OSNAME)/libreadline_cleo3.a lib/$(OSNAME)/libtcl8.2.so lib/$(OSNAME)/libtk8.2.so

setup::
	-test -d lib || mkdir -p lib
	-test -d lib/$(OSNAME) || mkdir -p lib/$(OSNAME)

lib/$(OSNAME)/libreadline_cleo3.a:
	-(cd readline; ./configure; gmake; cp libreadline.a ../lib/$(OSNAME)/libreadline_cleo3.a; cp libhistory.a ../lib/$(OSNAME)/libhistory_cleo3.a)

lib/$(OSNAME)/libtcl8.2.so:
	-(cd tcltk/tcl8.2.3/unix; ./configure --prefix=$(PRESENT_DIR)/tcltk; gmake; gmake install; cd $(PRESENT_DIR)/tcltk/lib; cp libtcl8.2.so $(PRESENT_DIR)/lib/$(OSNAME)/;)
lib/$(OSNAME)/libtk8.2.so:
	-(cd tcltk/tk8.2.3/unix; ./configure --with-tcl=$(PRESENT_DIR)/tcltk/tcl8.2.3/unix --prefix=$(PRESENT_DIR)/tcltk; gmake; gmake install; cd $(PRESENT_DIR)/tcltk/lib; cp libtk8.2.so $(PRESENT_DIR)/lib/$(OSNAME)/;)
