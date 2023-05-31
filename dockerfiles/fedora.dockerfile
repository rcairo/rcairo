ARG FEDORA_VERSION
FROM fedora:${FEDORA_VERSION}

RUN \
  dnf install -y \
    gcc \
    gcc-c++ \
    make \
    redhat-rpm-config \
    ruby-devel \
    sudo \
    which

RUN \
  gem install \
    bundler \
    rake

RUN \
  useradd --user-group --create-home rcairo

RUN \
  echo "rcairo ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/rcairo

USER rcairo
WORKDIR /home/rcairo
