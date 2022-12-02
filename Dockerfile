FROM fuzzers/afl:2.52 as builder

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake  automake autotools-dev autoconf libtool pkg-config m4 zlib1g zlib1g-dev gettext libgtest-dev libjpeg-dev 
ADD . /lib3mf
WORKDIR /lib3mf
RUN git submodule update --init
RUN cmake -DCMAKE_C_COMPILER=afl-clang -DCMAKE_CXX_COMPILER=afl-clang++ .
RUN make
RUN make install
ADD ./fuzzers/fuzz_3mfReader.cpp /lib3mf/
RUN afl-clang++  -L/usr/local/lib -I/usr/local/include/Bindings/CppDynamic fuzz.cpp -o fuzz_3mf_reader -l3mf -lstdc++ -ldl
RUN mkdir ./corpus
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cube_gears.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cylinder.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/cylinder.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/raw/master/examples/core/multiple_cylinders.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/blob/master/examples/core/sphere.3mf
RUN wget https://github.com/3MFConsortium/3mf-samples/blob/master/examples/core/torus.3mf
RUN mv *.3mf ./corpus

FROM fuzzers/afl:2.52
COPY --from=builder /lib3mf/fuzz_3mf /
COPY --from=builder /lib3mf/corpus/* /testsuite/
COPY --from=builder /usr/local/lib/lib3mf* /usr/local/lib/
ENV LD_LIBRARY_PATH=/usr/local/lib

ENTRYPOINT ["afl-fuzz", "-i", "/testsuite", "-o", "/3mfOut"]
CMD ["/fuzz_3mf_reader", "@@"]
