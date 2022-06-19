FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends --no-install-suggests \
    python3 python3-pip gcc libc6-dev make cmake zip unzip universal-ctags libncurses5 libncurses5-dev pkg-config cppcheck check tzdata \
    && pip3 install --no-cache-dir setuptools \
    && pip3 install --no-cache-dir lorem pyyaml \
    && rm -rf /var/lib/apt/lists/* \
    && rm /etc/timezone && rm /etc/localtime \
    && echo "Europe/Bratislava" > /etc/timezone \
    && dpkg-reconfigure --frontend noninteractive tzdata

# set environment variables
ENV CC=/usr/bin/gcc
ENV CFLAGS="-std=c11 -Wall -Werror -g"
ENV LDLIBS="-lm -lcurses"

CMD []
