# Contributor: Ezekiel Bethel <zek@9net.org>

pkgname=('switch-mupdf')
pkgver=1.16.1
pkgrel=1
pkgdesc="A lightweight PDF, XPS, and E-book viewer."
arch=('any')
license=('AGPL')
url="https://mupdf.com/"
options=(!strip libtool staticlibs)
source=(https://mupdf.com/downloads/archive/mupdf-$pkgver-source.tar.xz)
noextract=(mupdf-$pkgver-source.tar.xz)
sha256sums=('skip')
makedepends=('switch-pkg-config' 'devkitpro-pkgbuild-helpers')
depends=('switch-freetype' 'switch-libjpeg-turbo' 'switch-zlib')
groups=('switch-portlibs')

build() {
  source /opt/devkitpro/switchvars.sh

  # XCFLAGS here is intentional
  # "Do not specify CFLAGS or LIBS on the make invocation line - specify
  # XCFLAGS or XLIBS instead. Make ignores any lines in the makefile that
  # set a variable that was set on the command line" - mupdf makefile

  make -C "$srcdir/mupdf" \
  CC=${TOOL_PREFIX}gcc \
  CXX=${TOOL_PREFIX}g++ \
  LD=${TOOL_PREFIX}ld \
  AR=${TOOL_PREFIX}ar \
  RANLIB=${TOOL_PREFIX}ranlib \
  XCFLAGS="${CPPFLAGS} ${CFLAGS} -DTOFU_NOTO -DTOFU_CJK" \
  USE_SYSTEM_FREETYPE=yes \
  USE_SYSTEM_HARFBUZZ=no \
  USE_SYSTEM_JBIG2DEC=no \
  USE_SYSTEM_JPEGXR=no \
  USE_SYSTEM_LCMS2=no \
  USE_SYSTEM_LIBJPEG=yes \
  USE_SYSTEM_MUJS=no \
  USE_SYSTEM_OPENJPEG=no \
  USE_SYSTEM_ZLIB=no \
  libs
}

package() {
  source /opt/devkitpro/switchvars.sh

  export DESTDIR=..

  install -d $DESTDIR/include/mupdf
  install -d $DESTDIR/include/mupdf/fitz
  install -d $DESTDIR/include/mupdf/pdf
  install $srcdir/mupdf/include/mupdf/*.h $DESTDIR/include/mupdf
  install $srcdir/mupdf/include/mupdf/fitz/*.h $DESTDIR/include/mupdf/fitz
  install $srcdir/mupdf/include/mupdf/pdf/*.h $DESTDIR/include/mupdf/pdf
  install -d $DESTDIR/lib
  install $srcdir/mupdf/build/release/libmupdf.a $DESTDIR/lib
  install $srcdir/mupdf/build/release/libmupdf-third.a $DESTDIR/lib
}
