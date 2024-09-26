pkgname=histfilesimp
pkgdesc='A script to reduce zsh history'
pkgver=1.0.0
pkgrel=1
arch=('x86_64')
license=('MIT')
depends=('glibc')
makedepends=('cmake' 'make' 'gcc')
source=(https://github.com/SirenityK/${pkgname}/archive/refs/tags/v${pkgver}.tar.gz)
sha256sums=(3f43efaef100895c67f72b6da7da67476f2f86c2d5c194a0da33b3639b716fee)

prepare() {
	tar -xvf v${pkgver}.tar.gz
}

build() {
	cd ${pkgname}-${pkgver}
	cmake -S . -B build \
		-DCMAKE_BUILD_TYPE='None' \
		-DCMAKE_INSTALL_PREFIX=/usr \
		-Wno-dev
	cmake --build build -v
}

package() {
	cd ${pkgname}-${pkgver}
	install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
	DESTDIR="${pkgdir}" cmake --install build
}
