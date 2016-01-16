libfm taglib modules
====================

Modules for pcmanfm/libfm to show informations about music files (obtained
with taglib) in additional columns.

Requires libfm-gtk-dev and libtagc0-dev for building, e.g. on Debian-based
distros use:

	$ sudo apt-get install libfm-gtk-dev libtagc0-dev

To build and install, use:

	$ make
	$ sudo make install

Modules are installed under /usr/lib/x86_64-linux-gnu, which is correct
for multiarch 64-bit installations. For 32-bit installation change LIBDIR
to /usr/lib/i386-linux-gnu in the Makefile. For other architectures
change as appropriate.
