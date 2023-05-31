ARG VERSION
FROM almalinux:${VERSION}

RUN \
  dnf install -y \
    epel-release && \
  dnf install -y \
    gcc \
    gcc-c++ \
    libffi-devel \
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
