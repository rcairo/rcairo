FROM centos:8

RUN \
  dnf install -y \
    epel-release && \
  dnf install -y \
    adwaita-gtk2-theme \
    dbus-daemon \
    dejavu-sans-fonts \
    gcc \
    gcc-c++ \
    gstreamer1-plugins-good \
    make \
    redhat-rpm-config \
    ruby-devel \
    sudo \
    which \
    xorg-x11-server-Xvfb

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
RUN chown -R rcairo: /home/rcairo/rcairo

USER rcairo
WORKDIR /home/rcairo/rcairo

RUN \
  gem build cairo.gemspec && \
  sudo -H gem install *.gem && \
  sudo -H gem install poppler && \
  bundle install

CMD bundle exec rake
