#!/bin/bash

# 1
INSTALLDIR=~/bin
# 2
BUILDDIR=~/wmbuild
# 3
BUILDVER=whatmask-1.2
# 4
if [ -e "${INSTALLDIR}/whatmask" ]; then
	exit
fi
# 5
if [ ! -d "$INSTALLDIR" ]; then
	mkdir ${INSTALLDIR}
fi
# 6
if [ ! -d "$BUILDDIR" ]; then
	mkdir ${BUILDDIR}
fi
if [ ! -d "${BUILDDIR}/${BUILDVER}" ]; then
	mkdir ${BUILDDIR}/${BUILDVER}
fi
# 7
cd ${BUILDDIR}
# 8
if [ ! -f "whatmask-1.2.tar.gz" ]; then
	wget http://www.columbia.edu/~dm2474/3102/whatmask-1.2.tar.gz
fi
# 9
tar xvf whatmask-1.2.tar.gz
cd ${BUILDVER}
./configure || exit
make || exit
cp ${BUILDDIR}/${BUILDVER}/whatmask ${INSTALLDIR}/whatmask
${INSTALLDIR}/whatmask 127.0.0.1/24
if [ ! $? ]; then
	echo "failure"
fi
#10
rm -rf ${BUILDDIR}/${BUILDVER}
