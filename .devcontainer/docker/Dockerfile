FROM ubuntu:20.04

USER root

# timezone
RUN ln -snf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
RUN echo 'Asia/Shanghai' > /etc/timezone

# apt-utils
RUN apt update -y && apt install -y apt-utils

# locale
RUN apt update -y && apt install -y locales
RUN echo 'en_US.UTF-8 UTF-8' >> /etc/locale.gen && locale-gen
ENV LANG en_US.utf8

# ohmyzsh and plugins
RUN apt update -y && apt install -y zsh git curl
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
RUN apt update -y && apt install -y neovim curl nodejs npm
COPY neovim/init.vim /tmp/init.vim
RUN mkdir -p ~/.config/nvim && mv /tmp/init.vim ~/.config/nvim
# install vim-plug
RUN sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
# install nvim plugin
RUN nvim +PlugInstall +qall
RUN nvim +"CocInstall coc-clangd" +qall

# git
RUN apt update -y && apt install -y git
RUN git config --global core.autocrlf input
RUN git config --global core.editor nvim
RUN git config --global pull.rebase false

# cf-tool
RUN apt update -y && apt install -y golang
RUN go get -v github.com/xalanq/cf-tool
RUN cd $(go env GOPATH)/bin && ln -s cf-tool cf

# C++
RUN apt update -y && apt install -y build-essential clang clangd gcc g++ gdb

# tools
RUN apt update -y && apt install -y ranger htop wget

ENTRYPOINT []
CMD ["/usr/bin/zsh"]
WORKDIR "/root"