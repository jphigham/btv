# btv

### Windows source setup:

Clone source, create build dir:

```
Open Qt 5.15.2 (MinGW 8.1.0 64-bit)
> mkdir <path_to_source_dir>
> cd <path_to_source_dir>
> git clone <btv_repo_url>
> mkdir <path_to_build_dir>
> cd <path_to_build_dir>

```

#### Windows CMake/MinGW build:

```
> C:\Qt\Tools\CMake_64\bin\cmake.exe -G "MinGW Makefiles" <path_to_source_dir>\btv -DCMAKE_BUILD_STRING=Debug
> mingw32-make
> btv.exe
```

#### Windows qmake build:

```
> qmake <path_to_source_dir>\btv\btv.pro
> mingw32-make [release|debug]
> [release|debug]\btv.exe
```

### Linux source setup:

Clone source, create build dir:

```
$ mkdir <path_to_source_dir>
$ cd <path_to_source_dir>
$ git clone <btv_repo_url>
$ mkdir <path_to_build_dir>
$ cd <path_to_build_dir>
```

#### Linux CMake/gcc build:

```
$ cmake -G "Unix Makefiles" <path_to_source_dir>/btv -DCMAKE_BUILD_TYPE=Debug
$ make
$ ./btv
```

#### Linux qmake build:

```
$ <path_to_qt>/<qt_version>/<arch>/bin/qmake <path_to_source_dir>/btv/btv.pro
$ make [release|debug]
$ ./btv
```