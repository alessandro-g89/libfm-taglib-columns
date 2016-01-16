MODULES = gtk-column-taglib-title \
	gtk-column-taglib-artist gtk-column-taglib-album gtk-column-taglib-genre \
	gtk-column-taglib-comment gtk-column-taglib-year gtk-column-taglib-track \
	gtk-column-taglib-bitrate gtk-column-taglib-samplingrate \
	gtk-column-taglib-channels gtk-column-taglib-length
LIBDIR = /usr/lib/x86_64-linux-gnu
CFLAGS = `pkg-config --cflags libfm gtk+-2.0 taglib`
AM_LDFLAGS = -rpath $(LIBDIR) -no-undefined -module -avoid-version -ltag_c

all:
	$(foreach MODULE,$(MODULES),libtool --mode=compile gcc $(CFLAGS) -c $(MODULE).c;)
	$(foreach MODULE,$(MODULES),libtool --mode=link gcc $(AM_LDFLAGS) $(MODULE).lo -o $(MODULE).la;)

install:
	$(foreach MODULE,$(MODULES),libtool --mode=install install -c $(MODULE).la $(LIBDIR)/libfm/modules/;)
	libtool --finish $(LIBDIR)/libfm/modules/
