#!/bin/bash -e

linux() {
	if [ ! -d lib/mlx_linux ]
	then
		git clone https://github.com/42Paris/minilibx-linux.git lib/mlx_linux
	fi 
	if [ ! -e lib/mlx_linux/libmlx.a ]
	then
		sudo apt-get install -yqq clang
		sudo apt-get install -yqq libbsd-dev
		sudo apt-get install -yqq libx11-dev
		sudo apt-get install -yqq libxext-dev
		cd lib/mlx_linux && ./configure 
		rm -rf .git && rm -rf .gitignore && rm -rf .github && cd ..
	fi
}

mac() {
	if [ ! -d lib/mlx_mac ]
	then
		echo "Missing mlx_mac folder, download it from the intra and save it to lib/mlx_mac"
		exit
	fi
	if [ ! -e lib/mlx_mac/libmlx.a ]
	then
		make -s -C lib/mlx_mac
	fi
}

case "$OSTYPE" in
	linux*) linux ;;
	darwin*) mac ;;
esac
