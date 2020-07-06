# simple_example

Run a simple terminal service that listen on port 8537.

## Compile and run

```bash
$ make
```


### https connection


## Endpoints available:

- `GET http://localhost:8537/v1/terminals`: get attributes of current list of terminals
- `GET http://localhost:8537/v1/terminals/:id`: get arributes of terminal with specific id
- `POST http://localhost:8537/v1/terminals`: create a terminal with JSON attributes, returns the allocaed id.

Please check curl.txt for acceptance test.

## Build Env
1. Ubuntu 20.04
2. sudo apt install build-essential
3. sudo apt install libulfius-dev  