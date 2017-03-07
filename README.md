# AlexeyServer
ScoreServer for Alexey

# build
## Docker

```
docker-compose build up
```


## CMake

```
mkdir src/build && cd src/build
cmake ../
make
```

# dependencies

* [msgpack-c](https://github.com/msgpack/msgpack-c)
* [cpp_redis](https://github.com/Cylix/cpp_redis)
