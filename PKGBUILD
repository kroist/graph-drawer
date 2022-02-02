pkgname=graph-drawer
pkgver=1.0
pkgrel=1
epoch=
pkgdesc=""
arch=("x86_64")
url=""
license=('MIT')
groups=()
depends=('cmake')
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("$pkgname-$pkgver.tar.gz::https://github.com/kroist/graph-drawer/tarball/main")
noextract=("$pkgname-$pkgver.tar.gz")
md5sums=('SKIP')
validpgpkeys=()

prepare() {
    mkdir $pkgname-$pkgver
    tar -xf $pkgname-$pkgver.tar.gz -C $pkgname-$pkgver --strip-components 1
}

build() {
	cd "$pkgname-$pkgver"
    cmake -B build
    cmake --build build
}

package() {
	cd "$pkgname-$pkgver"
    cp build/drawer "$pkgdir/"
}
