#include <QX11Info>
#include <QDebug>

#include "atoms.h"

extern Display *dpy;

static const char *atomNames = {
    "_NET_WM_WINDOW_OPACITY\0"
    "_NET_CURRENT_DESKTOP\0"
    
    "_XROOTPMAP_ID\0"
    "_XSETROOT_ID\0"
    
    "ESETROOT_PMAP_ID\0"
};

InternalAtoms *atomList = 0;

void createAtomList()
{
	atomList = new InternalAtoms;

	const char *names[InternalAtoms::NAtoms];
	const char *ptr = atomNames;

	int i = 0;
	while (*ptr)
	{
		names[i++] = ptr;
		while (*ptr)
			++ptr;
		++ptr;
	}

	Q_ASSERT(i == InternalAtoms::NAtoms);

	for (i = 0; i < InternalAtoms::NAtoms; ++i)
        atomList->atoms[i] = XInternAtom(dpy, names[i], False);
}
