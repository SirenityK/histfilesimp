pkgname=histfilesimp
pkgver=1.0.0
arch=('x86_64')
pkgrel=1
depends=('glibc')
makedepends=('cmake' 'make' 'gcc')

build() {
	cmake -B build -S .. \
		-DCMAKE_BUILD_TYPE='None' \
		-DCMAKE_INSTALL_PREFIX='/usr' \
		-Wno-dev
	cmake --build build -v
}

package() {
	DESTDIR="$pkgdir" cmake --install build
}
