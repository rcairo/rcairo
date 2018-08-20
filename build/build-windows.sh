#!/bin/sh

export LANG=C
export DEBIAN_FRONTEND=noninteractive

ruby_versions="2.1.10 2.2.4 2.3.0 2.4.0 2.5.0"
export RUBY_CC_VERSION="2.1.10:2.2.4:2.3.0:2.4.0:2.5.0"

N_CPUS=$(grep '^processor' /proc/cpuinfo | wc -l)
export MAKE_N_JOBS=${N_CPUS}

export RUBYLIB="$(pwd)/pkg-config/lib:$(pwd)/native-package-installer/lib"

run()
{
  "$@"
  if [ $? -ne 0 ]; then
    echo "Failed $@"
    exit 1
  fi
}

if [ ! -f ~/setup.timestamp ]; then
  run sudo systemctl stop apt-daily.service apt-daily.timer

  run sudo sed \
      -i'' \
      -e 's,archive.ubuntu.com/ubuntu,ftp.iij.ad.jp/pub/linux/ubuntu/archive/,g' \
      /etc/apt/sources.list
  run sudo dpkg --add-architecture i386
  run sudo apt update

  sudo rm -rf /etc/udev/rules.d/70-persistent-net.rules

  echo ttf-mscorefonts-installer \
       msttcorefonts/accepted-mscorefonts-eula \
       select true | \
    run sudo debconf-set-selections

  run \
    sudo apt install -y -V \
    git \
    gperf \
    ruby \
    ruby-dev \
    build-essential \
    pkg-config \
    autoconf \
    libtool \
    gettext \
    intltool \
    gtk-doc-tools \
    libffi-dev \
    libglib2.0-dev \
    gobject-introspection \
    flex \
    bison \
    python-dev \
    wine-stable \
    wine-binfmt \
    mingw-w64 \
    libmount-dev \
    python3-pip

  # run sudo update-alternatives --set \
  #     ${BUILD_HOST}-gcc /usr/bin/${BUILD_HOST}-gcc-posix
  # run sudo update-alternatives --set \
  #     ${BUILD_HOST}-g++ /usr/bin/${BUILD_HOST}-g++-posix

  run sudo pip3 install jsmin meson ninja

  run git clone file:///pkg-config/.git
  run git clone file:///native-package-installer/.git
  run git clone file:///rcairo/.git rcairo
  run git clone file:///ruby-gnome2/.git ruby-gnome2

  run sudo gem install --no-document \
      rake \
      bundler \
      pkg-config \
      native-package-installer \
      rake-compiler \
      mechanize \
      packnga

  if [ ! -d ~/.wine/ ]; then
    run wineboot
    until [ -f ~/.wine/system.reg ]; do
      sleep 1
    done
    sleep 10
    wine_home="z:/home/vagrant"
    wine_rcairo="${wine_home}/rcairo"
    wine_ruby_gnome2="${wine_home}/ruby-gnome2"
    bin_dir="vendor/local/bin"
    path=$(
      (
        echo -n "${wine_rcairo}/${bin_dir};";
        echo -n "${wine_ruby_gnome2}/glib2/${bin_dir};";
      ) | \
        sed -e 's,/,\\\\\\\\,g')
    run sed -i'' -r \
        -e "s,^(\"PATH\"=str\\(2\\):\"),\\1${path},g" \
        ~/.wine/system.reg
  fi

  run touch ~/setup.timestamp
fi

if [ ! -f ~/rake-compiler.timestamp ]; then
  sudo chown -R "${USER}:${USER}" /var/lib/gems

  for ruby_version in ${ruby_versions}; do
    run rake-compiler cross-ruby HOST="${BUILD_HOST}" VERSION="${ruby_version}"
  done

  run touch ~/rake-compiler.timestamp
fi

if [ ! -f ~/native.timestamp ]; then
  run cd ~/rcairo
  run git pull --rebase
  run rake windows:gcc:dll:bundle windows:zlib:build

  run cd ~/ruby-gnome2
  run git pull --rebase

  run cd ~/ruby-gnome2/glib2
  run rake native:build windows:build

  run cd ~/ruby-gnome2/gobject-introspection
  run rake native:build

  run touch ~/native.timestamp
fi

run cd ~/rcairo
run git pull --rebase
run rake windows:build
run rake cross compile native gem

run mkdir -p /vagrant/pkg
run cp pkg/*.gem /vagrant/pkg/
