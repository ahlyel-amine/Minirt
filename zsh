# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"
alias usg='df -h . | grep --color=always -E "Size|Used|Avail|Capacity|[0-9]*\.*[0-9]*Mi|[0-9]*\.*[0-9]*Gi|[0-9]+\.*[0-9]+% |$"'
alias myusg="du -hs * | sort -r -h"
alias bigusg="du -mh 2>/dev/null | sort -hr | head -30"
alias py="python3.9"
alias pip="pip3.9"
alias gofr="cd ~/goinfre"
alias code="/Applications/Visual\ Studio\ Code.app/Contents/Resources/app/bin/code"
alias clean=" ~/.Cleaner_42.sh"
#alias /bin/bash="~/Desktop/.minishell"
#alias ./bash="~/Desktop/.minishell"
#alias bash="~/Desktop/.minishell"
alias val="~/homebrew/Cellar/valgrind/HEAD-bdcb3b9/bin/valgrind --leak-check=full"
# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh
export PATH=$HOME/.brew/bin:$PATH
--------
# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='vim'
# else
#   export EDITOR='mvim'
# fi

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#
# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"
alias usg='df -h . | grep --color=always -E "Size|Used|Avail|Capacity|[0-9]*\.*[0-9]*Mi|[0-9]*\.*[0-9]*Gi|[0-9]+\.*[0-9]+% |$"'
alias myusg="du -hs * | sort -r -h"
alias bigusg="du -mh 2>/dev/null | sort -hr | head -30"
alias py="python3.9"
alias pip="pip3.9"
alias gofr="cd ~/goinfre"
alias code="/Applications/Visual\ Studio\ Code.app/Contents/Resources/app/bin/code"
alias clean=" ~/.Cleaner_42.sh"
alias /bin/bash="~/Desktop/.minishell"
alias ./bash="~/Desktop/.minishell"
alias bash="~/Desktop/.minishell"
alias val="~/homebrew/Cellar/valgrind/HEAD-bdcb3b9/bin/valgrind --leak-check=full"
# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh