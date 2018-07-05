# Citcuit-x

A simple circuit software.

## Enivorment

-this software running on unbuntu

-this software using ncurses, make sure your computer has support ncurses already.

## Run the software

```
make
```

to complie

```
./circuit
```

to run this software

## Introdution

-there are two source-output interface in the upper-left corner

-the negative source is in 0,0 , the positive source is in 0,1

-you have to connect the sources to set a data for ininterface

### Component

-AND size:3*3

-OR  size:3*3

-XOR size:3*3

-INVERSE size:1*3

-BITDISPLAY size:3*3

-BYTEDISPLAY size:10*3

### Command

```
NEW type position
```

to new a gate or display(e.g. NEW AND 10,10)

```
CONN position(out) position(in)
```

to connect outinterface and ininterface(e.g. CONN 0,0 10,10)

```
DISCONN position(out) position(in)
```

to disconnect outinterface and ininterface(e.g. DSICONN 0,0 10,10)

```
LIST
```

list all commands you have input(so that you can copy it to a file and save it)

```
RUN
```

run the circuit and then see the out put in dispay

```
QUIT
```

to quit!

# GOOD　LUCKY
