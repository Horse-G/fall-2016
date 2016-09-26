#!/bin/bash
if [[ $# == 0 || "$0" == "/home/anh2130/mybin/mystate.sh" ]]; then
	echo "meh"
else
	if [[ $# > 1 ]]; then
		echo "error: invalid arg num"
	elif [[ "$0" == "/home/anh2130/mybin/exclaim" ]]; then
		echo "I am ${1}, yay! :-)"
	elif [[ "$0" == "/home/anh2130/mybin/complain" ]]; then
		echo "I'm ${1}. :-|"
	else
		echo "error: invalid executable name"
	fi
fi
