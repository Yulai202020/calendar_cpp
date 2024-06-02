pkgname="yulai_cal"
pkgver=4.4
pkgrel=1
pkgdesc="Simple calindare"
arch=("x86_64")
license=('GPL')
source=("")

build() {
    g++ yulai_cal.cpp -o yulai_cal
}

package() {
    install -m 744 yulai_cal $pkgdir
}