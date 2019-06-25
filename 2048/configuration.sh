#!/bin/sh

#  configuration.sh
#  2048
#
#  Created by Chloé Yukino on 25/06/2019.
#  Copyright © 2019 Cyzu. All rights reserved.

echo "This script will install ncurses library..."

if [[ "$OSTYPE" == "linux-gnu" ]]; then
# Linux ...
    sudo apt-get update
    sudo apt-getupgrade
# Install gcc & ncurses library
    sudo apt-get install build-essential
    sudo apt-get install libncurses-dev ncurses-dev libncurses5-dev libncursesw5-dev


elif [[ "$OSTYPE" == "darwin"* ]]; then
# Mac OSX
    brew install ncurses

fi

echo "Installation finished !"
echo "Run command 'make' to continue."
