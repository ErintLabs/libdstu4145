#!/bin/sh

# Add the repository
echo deb http://ftp.debian.org/debian jessie-backports main >> /etc/apt/sources.list
echo deb http://ftp.debian.org/debian jessie main >> /etc/apt/sources.list

# Setup the environment for cases when Travis automatically can't
apt-get update
apt-get -y install cmake cmake-data check
