ARG UBUNTU_VERSION
FROM ubuntu:${UBUNTU_VERSION}

RUN \
  echo "debconf debconf/frontend select Noninteractive" | \
    debconf-set-selections

RUN \
  apt update && \
  apt install -y \
    g++ \
    gcc \
    make \
    ruby-dev \
    sudo

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
