# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific aliases and functions
alias cunix="ssh cunix.cc.columbia.edu"

function scpcu
{
	/usr/bin/scp ${1} anh2130@cunix.cc.columbia.edu:
}
