Build the containers
in server folder:
```
docker build -t my_ipc_server .  
```

in client folder:
```
docker build -t my_ipc_client .  
```
Creating the docker network
```
docker network create my_socket_ipc_network

```

Run containers
```
docker run --rm --network=my_socket_ipc_network --name ipc_server_dns_name my_ipc_server

docker run --rm --network=my_socket_ipc_network my_ipc_client

```


Source: https://medium.com/techanic/docker-containers-ipc-using-sockets-part-1-2ee90885602c