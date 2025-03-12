FROM alpine

RUN \
  apk update && apk upgrade && \
  apk add \
    bash \
    build-base \
    gcc \
    git \
    make \
    ruby-dev \
    openssl-dev \
    zlib-dev \
    sudo \
    which

RUN \
  gem install --no-user-install \
    bundler \
    rake

RUN \
  adduser rcairo -G wheel -D -h /home/rcairo

RUN \
  echo "rcairo ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/rcairo

USER rcairo
WORKDIR /home/rcairo
