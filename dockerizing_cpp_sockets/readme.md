Step 1: Create the network 
```
docker network create user_def_nw      
```
Step 2: Find the netowork subset range:
```

```

You should get a result like this
```
[
    {
        "Name": "user_def_nw",
        "Id": "574d003247cd0e63027e0c91d874585bd5c0df664ba8964ee83ddd4c57c405b9",
        "Created": "2021-12-19T18:31:57.8599449Z",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "172.19.0.0/16",
                    "Gateway": "172.19.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {},
        "Options": {},
        "Labels": {}
    }
]
```

Look for Subset:
```
"Subnet": "172.19.0.0/16",
"Gateway": "172.19.0.1"
```
Let your address be 1+ the gateway.

Step 3: in server.cpp to be the ip address:
```
serv_addr.sin_addr.s_addr = inet_addr("172.19.0.2");
```

Step 4: in client/Dockerfile change the ip address to the SAME ip address 
```
ENTRYPOINT ["testcplusplus", "172.19.0.2", "1001"]
```


Step 5: Build the containers
```
docker build -t cpp_server:1 . 
docker build -t cpp_clent:1 . 
```

Step 6: Run the containers (server first)
```
docker run --rm --net=user_def_nw -ti -P --name server1 cpp_server:1   
docker run --rm --net=user_def_nw -ti --name cli1 cpp_client:1
```

Source: https://forums.docker.com/t/client-server-program-each-running-as-a-container-not-able-to-communicate-with-each-other-using-posix-socket-api/14293