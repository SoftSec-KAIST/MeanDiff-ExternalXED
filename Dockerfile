FROM build_base
MAINTAINER Soomin Kim <soomink@kaist.ac.kr>

RUN apt install python -y

RUN mkdir /compile

WORKDIR /compile
RUN git clone https://github.com/intelxed/xed.git xed
RUN git clone https://github.com/intelxed/mbuild.git mbuild
RUN mkdir build
RUN cd build && ../xed/mfile.py install
RUN cp ./build/kits/xed-install-base-`date +%Y-%m-%d`-lin-x86-64/lib . -r
RUN cp ./build/kits/xed-install-base-`date +%Y-%m-%d`-lin-x86-64/include . -r
