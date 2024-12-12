FROM continuumio/miniconda3

RUN \
  echo "debconf debconf/frontend select Noninteractive" | \
    debconf-set-selections

COPY environment.yml /
RUN \
  conda env create && \
  echo "conda activate rcairo" >> ~/.bashrc
