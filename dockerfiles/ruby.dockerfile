ARG RUBY_VERSION
FROM ruby:${RUBY_VERSION}

RUN \
  apt update && \
  apt install -y \
    sudo

RUN \
  useradd --user-group --create-home rcairo

RUN \
  echo "rcairo ALL=(ALL:ALL) NOPASSWD:ALL" | \
    EDITOR=tee visudo -f /etc/sudoers.d/rcairo

USER rcairo
WORKDIR /home/rcairo
