FROM gcc:latest

  #copy everything into usr/src folder
  COPY . /usr/src/cpp_test

  WORKDIR /usr/src/cpp_test

  RUN g++ -o HelloWorld simple.cpp

  CMD [ "./HelloWorld" ]
