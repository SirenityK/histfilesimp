pkgname=histfilesimp
pkgdesc='A script to reduce zsh history'
pkgver=1.0.0
pkgrel=1
license=('MIT')
makedepends=('cargo')
arch=('i686' 'x86_64' 'armv6h' 'armv7h')

build() {
	export RUSTUP_TOOLCHAIN=stable
	export CARGO_TARGET_DIR=target
	cargo build --release --all-features
}

check() {
	export RUSTUP_TOOLCHAIN=stable
	cargo test --all-features
}

package() {
	install -Dm644 ../LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
	install -Dm0755 -t "$pkgdir/usr/bin/" "target/release/$pkgname"
}
