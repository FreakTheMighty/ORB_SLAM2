FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install -y \
 git\
 cmake\
 build-essential\
 libgl1-mesa-dev\
 libglew-dev\
 libblas-dev\
 liblapack-dev\
 libopencv-dev\
 python-opencv\
 libeigen3-dev


RUN cd /tmp && git clone https://github.com/stevenlovegrove/Pangolin.git && \
  cd Pangolin && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make -j

ADD . /usr/local/slam

WORKDIR /usr/local/slam

RUN chmod +x build.sh & ./build.sh
