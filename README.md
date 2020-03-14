# LIPA
Linear programming Interior-Point Algorithm.

LIPA is a C++ package designed to solve linear optimization problems using interior-point method.
 
 
## Motivation

On it's current state, the project is implemented as a solution to the
 [GeomsScale GSoC 2020 test task](https://github.com/GeomScale/gsoc2020/wiki/Optimization-and-SOS#tests).   
 
## Installation

### 1. Download

Download repo with ```git clone --recursive https://github.com/AndreyBychkov/LIPA.git```

If any issues with submodules arise, try checking out [this](https://git-scm.com/book/en/v2/Git-Tools-Submodules) article.

### 2. Building

The project strongly depends on BLAS and LAPACK libraries, so make sure you have them in your system.
We suggest following [guide from Armadillo](https://gitlab.com/conradsnicta/armadillo-code#5-linux-and-macos-installation)
for general information about installing this dependencies.

#### Building OpenBLAS

We use OpenBLAS as realisation of BLAS + LAPACK bundle.
 Consider checking [it's building manual](https://github.com/xianyi/OpenBLAS#installation-from-source).   
 
Our steps for CMake + MinGW:
1. `cd OpenBLAS`
2. `mkdir build`
3. `cd build`
4. `cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release`
5. `cmake --build . -j --target all`

It will produce directory `lib` in `OpenBLAS/build` with `libopenblas.a` in it 
which we link in Cmake as follows:
```cmake
target_link_libraries(LIPA ${CMAKE_SOURCE_DIR}/OpenBLAS/build/lib/libopenblas.a)
```

Replace libraries in function with yours if needed.

## Usage

### Problem definition

Define linear optimization problem as follows:

<img src="https://latex.codecogs.com/png.latex?%5Clarge%20optimize%5C%20c%5ET%20%5C%5C%20subject%5C%20to%5C%20Ax%20%5Cle%20b%20%5C%5C"/>
<br/><br/>  
In our code it is defined as:

```c++
LinearOptimizationProblem problem = LinearOptimizationProblem(A, b, c);
```

### Optimization

* Maximization: 
```c++
LinearOptimizationResult result = problem.maximize(x_0, gamma, mir_err, method);
```
* Minimization:
For minimization replace vector `c` with negative `-c` and  consider it as maximization problem.
```c++
vec c_neg = -c;
LinearOptimizationProblem problem = LinearOptimizationProblem(A, b, c_neg);
LinearOptimizationResult result = problem.maximize(x_0, gamma, mir_err, method);
```

### Results

In `LinearOptimizationResult` class we store the solution itself as well as utility information like
intermediate solutions and the number of iterations.

```c++
result.result.print("Solution x:");
```
 
