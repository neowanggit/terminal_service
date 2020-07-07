# terminal_service

Run a simple terminal service that listen on port 8537.

## Compile and run

```bash
$ make
```

### service startup
under your "terminal_service" directory, run "./terminal_service"


## Endpoints available:

- `GET http://localhost:8537/v1/terminals`: get attributes of current list of terminals
- `GET http://localhost:8537/v1/terminals/:id`: get arributes of terminal with specific id
- `POST http://localhost:8537/v1/terminals`: create a terminal with JSON attributes, returns the allocaed id.

Please check curl.txt for reachable test.

## Build Env
1. Ubuntu 20.04
2. sudo apt install build-essential
3. sudo apt install libulfius-dev  

## unit test
1. sudo apt install libcunit1 libcunit1-dev
2. under "unittest", run "make"
3. Execute with "./terminal_ut"

## acceptance test
1. sudo apt install python3-pip
2. pip3 install --upgrade RESTinstance
3. under "acceptancetest", run "python3 -m robot --outputdir results atest/"

