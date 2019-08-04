#!/bin/sh

# Functions
build_binary()
{
	(
		cd ../"$1" || exit
		make clean && make release
		sha256sum "$1"
	)
}

# Script
build_binary "battery"
build_binary "vpn"
