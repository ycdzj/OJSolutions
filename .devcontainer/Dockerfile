FROM debian:bullseye

USER root

RUN DEBIAN_FRONTEND=noninteractive apt-get update -y &&\
    # packages
    apt-get install -y apt-utils zsh git curl fzf ranger wget tree build-essential binutils clang clangd gcc g++ gdb ccls &&\
    # ohmyzsh
    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended &&\
    zsh -c 'git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions' &&\
    sed -i 's/plugins=(/plugins=(zsh-autosuggestions /g' ~/.zshrc &&\
    zsh -c 'git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting' &&\
    sed -i 's/plugins=(/plugins=(zsh-syntax-highlighting /g' ~/.zshrc &&\
    sed -i 's/ZSH_THEME=/ZSH_THEME="crcandy" # /g' ~/.zshrc &&\
    chsh -s $(which zsh) &&\
    # fzf
    echo 'source /usr/share/doc/fzf/examples/key-bindings.zsh' >> ~/.zshrc &&\
    echo 'source /usr/share/doc/fzf/examples/completion.zsh' >> ~/.zshrc &&\
    # persist command history
    echo 'export HISTFILE=/persisted/zsh_history' >> ~/.zshrc &&\
    echo "export PROMPT_COMMAND='history -a' && export HISTFILE=/persisted/bash_history" >> ~/.bashrc

ENTRYPOINT []
CMD ["zsh"]