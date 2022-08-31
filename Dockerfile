FROM fuzzers/afl:2.52

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake  automake autotools-dev autoconf libtool pkg-config m4 zlib1g zlib1g-dev gettext libgtest-dev libjpeg-dev 
RUN git clone https://github.com/3MFConsortium/lib3mf.git
WORKDIR /lib3mf
RUN git submodule update --init
RUN cmake -DCMAKE_C_COMPILER=afl-clang -DCMAKE_CXX_COMPILER=afl-clang++ .
RUN make
RUN make install
COPY fuzzers/fuzz.cpp .
RUN afl-clang++ -I/usr/local/include/Bindings/CppDynamic fuzz.cpp -o /fuzz_3mf -l3mf -lstdc++ -ldl
RUN mkdir /3mfCorpus
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cube_gears.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cylinder.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cylinder.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/multiple_cylinders.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/blob/master/examples/core/sphere.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/blob/master/examples/core/torus.3mf
RUN mv *.3mf /3mfCorpus
ENV LD_LIBRARY_PATH=/usr/local/lib

ENTRYPOINT ["afl-fuzz", "-i", "/3mfCorpus", "-o", "/3mfOut"]
CMD ["/fuzz_3mf", "@@"]
