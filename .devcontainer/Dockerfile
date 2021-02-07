FROM debian:testing

USER root

RUN apt update -y && apt install -y git zsh build-essential neovim ranger curl wget locales nodejs npm apt-utils

RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen

COPY dotfiles /root/dotfiles
RUN /root/dotfiles/setup.sh

ENTRYPOINT []
CMD ["/usr/bin/zsh"]
ENV SHELL "/usr/bin/zsh"
WORKDIR "/root"
ENV LANG en_US.utf8