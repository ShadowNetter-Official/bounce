#!/bin/bash

echo
echo "bounce"
echo "by ShadowNetter"
echo
echo "cloning into repo..."
git clone https://github.com/ShadowNetter-Official/bounce
cd bounce
echo "done"
echo "installing..."
cd src
gcc -o bounce main.c cs50.c -lcrypt -lm
sudo cp bounce /bin/
echo
echo "done"
echo
echo "to uninstall do: "
echo "sudo rm /bin/bounce"
echo
