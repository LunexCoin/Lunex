
Debian
====================
This directory contains files used to package lunexd/lunex-qt
for Debian-based Linux systems. If you compile lunexd/lunex-qt yourself, there are some useful files here.

## lunex: URI support ##


lunex-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install lunex-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your lunex-qt binary to `/usr/bin`
and the `../../share/pixmaps/lunex128.png` to `/usr/share/pixmaps`

lunex-qt.protocol (KDE)

