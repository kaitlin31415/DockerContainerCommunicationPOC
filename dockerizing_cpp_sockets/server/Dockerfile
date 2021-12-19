FROM gcc:latest
WORKDIR /home/kaitlin
COPY . .
EXPOSE 1001
RUN g++ server.cpp -o testcplusplus 
ENV PATH /home/kaitlin:$PATH
ENTRYPOINT ["testcplusplus", "1001"]