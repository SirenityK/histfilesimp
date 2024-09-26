pkgname=histfilesimp
pkgdesc='A script to reduce zsh history'
pkgver=1.0.0
pkgrel=1
arch=('x86_64')
license=('MIT')
depends=('glibc')
makedepends=('cmake' 'make' 'gcc')
source=(https://github.com/SirenityK/${pkgname}/archive/refs/tags/v${pkgver}.tar.gz)
sha256sums=(42d81cc17fdedab33b28ebf94de055ec2c5eb05e21da81c7cdc93002d9b6fed2)

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
