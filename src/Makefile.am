## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = projet

projet_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	Agent.c Agent.h \
	Client.c Client.h \
	parking.c parking.h \
	Reclamation.c Reclamation.h 

projet_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

