FROM debian:testing

USER root

# packages
RUN apt update -y && apt install -y git zsh build-essential neovim ranger curl wget locales nodejs npm apt-utils golang clang clangd

# locale
RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen
ENV LANG en_US.utf8

# ohmyzsh and plugins
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended
# install zsh-autosuggestions
RUN zsh -c 'git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions'
RUN sed -i 's/plugins=(/plugins=(zsh-autosuggestions /g' ~/.zshrc
# install zsh-syntax-highlighting
RUN zsh -c 'git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting'
RUN sed -i 's/plugins=(/plugins=(zsh-syntax-highlighting /g' ~/.zshrc
# change default shell to zsh
RUN chsh -s $(which zsh)

# zshrc
COPY zsh/zshrc /tmp/zshrc
RUN cat /tmp/zshrc >> ~/.zshrc && rm /tmp/zshrc

# neovim and plugins
COPY neovim/init.vim /tmp/init.vim
RUN mkdir -p ~/.config/nvim && mv /tmp/init.vim ~/.config/nvim
# install vim-plug
RUN sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
# install nvim plugin
RUN nvim +PlugInstall +qall
RUN nvim +"CocInstall coc-clangd" +qall

# git
RUN git config --global core.autocrlf input
RUN git config --global pull.rebase false

# cf-tool
RUN go get -v github.com/xalanq/cf-tool
RUN cd $(go env GOPATH)/bin && ln -s cf-tool cf

ENTRYPOINT []
CMD ["/usr/bin/zsh"]
WORKDIR "/root"