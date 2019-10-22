FROM ruby:2.6

RUN \
  apt update && \
  apt install -y \
    dbus \
    gnome-icon-theme \
    gnumeric \
    gstreamer1.0-plugins-good \
    sudo \
    xvfb

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
  gem install *.gem && \
  bundle install

CMD bundle exec rake
