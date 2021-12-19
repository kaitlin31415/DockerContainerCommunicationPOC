FROM gcc:latest
WORKDIR /home/kaitlin
COPY . .
RUN g++ -o testcplusplus client.cpp
ENV PATH /home/kaitlin:$PATH
ENTRYPOINT ["testcplusplus", "172.19.0.2", "1001"]
