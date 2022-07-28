FROM archlinux

RUN \
  pacman --sync --noconfirm --refresh --sysupgrade && \
  pacman --sync --noconfirm \
    gcc \
    make \
    ruby \
    sudo \
    which

RUN \
  gem install --no-user-install \
    bundler \
    rake

RUN \
  useradd --user-group --create-home rcairo

RUN \
  echo "rcairo ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/rcairo

RUN \
  gem install --no-user-install cairo && \
  gem install --no-user-install \
    packnga \
    poppler \
    test-unit

USER rcairo
WORKDIR /home/rcairo
