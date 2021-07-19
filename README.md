# Synapse Multi-RTU Reader - v1.0

 Dependancies :

```# apt-get install sqlite3 libsqlite3-dev libmodbus5 libmodbus-dev```

Compile as below or use 'make all'

```gcc log.c -o log -lsqlite3 -lmodbus -m```

```
./rtu [-h|j|c] [-d]

Syntax :

-h = Human readable output (default)
-j = JSON readable output
-c = Comma delimited minimal output

-d = Debug output

Examples :
Read RTUs, output in JSON format :  ./rtu -j

Note : Config stored in local SQLite databses db_config.db and db_data.db

```
