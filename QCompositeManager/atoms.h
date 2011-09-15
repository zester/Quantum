#ifndef __ATOMS_H
#define __ATOMS_H

#include <X11/Xlib.h>

struct InternalAtoms;
extern InternalAtoms *atomList;

struct InternalAtoms
{
	enum X11Atom
	{
        _NET_WM_WINDOW_OPACITY,
        _NET_CURRENT_DESKTOP,

        _XROOTPMAP_ID,
        _XSETROOT_ID,

        ESETROOT_PMAP_ID,

		NAtoms
	};

	Atom atoms[NAtoms];
};

void createAtomList();

#define ATOM(x) atomList->atoms[InternalAtoms::x]

#endif
