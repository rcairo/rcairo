FROM archlinux/base

RUN \
  pacman --sync --noconfirm --refresh && \
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

COPY . /home/rcairo/rcairo
RUN chown -R rcairo: /home/rcairo/rcairo

USER rcairo
WORKDIR /home/rcairo/rcairo

RUN \
  gem build cairo.gemspec && \
  sudo -H gem install --no-user-install *.gem && \
  sudo -H gem install --no-user-install poppler && \
  bundle install

CMD bundle exec test/run-test.rb
