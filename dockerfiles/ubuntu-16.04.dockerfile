FROM ubuntu:16.04

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

COPY . /home/rcairo/rcairo
RUN chown -R rcairo:rcairo /home/rcairo/rcairo

USER rcairo
WORKDIR /home/rcairo/rcairo

RUN \
  gem build cairo.gemspec && \
  sudo -H gem install *.gem && \
  sudo -H gem install poppler && \
  bundle install

CMD bundle exec rake
