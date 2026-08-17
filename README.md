# DSP Lab

A small collection of standalone DSP experiments built around shared C modules.
Each lab has its own entry point and can be built and run independently.
Generated binaries and data files are kept in the `output/` directory.

## Build

Build one lab from the project root:

```
make <lab>
```

To see the available build targets:

```
make help
```

To build all labs:

```
make all
```

## Run

Run a built demo from the `output/` directory:

```
cd output
./<lab>_demo
```

Return to the project root before running a plotting script:

```
cd ..
gnuplot scripts/<lab>_demo.gp
```

## Clean

```
make clean
```

**NOTE:** see config.h to change parameters.
