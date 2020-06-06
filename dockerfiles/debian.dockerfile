ARG DEBIAN_VERSION
FROM debian:${DEBIAN_VERSION}

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

RUN \
  gem install cairo && \
  gem install \
    packnga \
    poppler \
    test-unit

USER rcairo
WORKDIR /home/rcairo
