# dynamic-network-visualization-boost-graph-library

Generate dynamic networks visualizations using the [Boost Graph Library](https://www.boost.org/doc/libs/release/libs/graph/doc/index.html).

![doc/2010-11-01-2011-04-01.gif](doc/2010-11-01-2011-04-01.gif)

## Getting started

### 0. Requirements

* OpenGL 2
* libboost-date-time-dev
* libboost-graph-dev
* libboost-program-options-dev
* libglfw3
* libglfw3-dev

### 1. Data preparation

The [doc/vertices.csv](doc/vertices.csv) and [doc/edges.csv](doc/edges.csv) CSV files are given as an example of the expected file format.

Note that:

* These files have been generated from the [Bitcoin Alpha trust weighted signed network](http://snap.stanford.edu/data/soc-sign-bitcoin-alpha.html) distributed by the [Stanford Network Analysis Project](http://snap.stanford.edu/index.html)
* The file MUST start with an header
* Entries MUST be sorted by time, by chronological order

### 2. Build

```
$ make
```

### 3. Run

Using the example dataset and for the events happening between 2010-11-01 and 2011-04-01, month per month:

```
$ ./build/main --vertices_file_path doc/vertices.csv --edges_file_path doc/edges.csv --start_date 2010-11-01 --end_date 2011-04-01
```

## References

* J. Leskovec, A. Krevl. SNAP Datasets: Stanford Large Network Dataset Collection. http://snap.stanford.edu/data, 2014
* S. Kumar, F. Spezzano, V.S. Subrahmanian, C. Faloutsos. Edge Weight Prediction in Weighted Signed Networks. IEEE International Conference on Data Mining (ICDM), 2016
* S. Kumar, B. Hooi, D. Makhija, M. Kumar, V.S. Subrahmanian, C. Faloutsos. REV2: Fraudulent User Prediction in Rating Platforms. 11th ACM International Conference on Web Searchand Data Mining (WSDM), 2018
