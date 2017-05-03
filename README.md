GRU: generic reusable utilities
============

Build Status
----
Linux Build Status: [![Linux Build Status](https://travis-ci.org/orpiske/gru.svg?branch=master)](https://travis-ci.org/orpiske/gru)

Windows Build Status: [![Windows Build status](https://ci.appveyor.com/api/projects/status/18qfc92iatymg9aw?svg=true)](https://ci.appveyor.com/project/orpiske/gru)

Coverity Scan: [![Coverity Scan Build Status](https://scan.coverity.com/projects/10838/badge.svg)](https://scan.coverity.com/projects/orpiske-gru)

Packaging Status
----
Fedora (GRU Testing): [![Fedora COPR (Testing Repo) Status](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing/package/gru/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing/package/gru/) 

Fedora (GRU Stable): [![Fedora COPR (Stable Repo) Status](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-stable/package/gru/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-stable/package/gru/) 


Introduction:
----

This library contains portable and reusable C code for very simple applications.

Dependencies:
----

Runtime/Compilation:
* cmake
* gcc or clang
* Microsoft Compiler (ie.: Visual Studio 2015)
* [uriparser](http://uriparser.sourceforge.net/)

Building
----

- On Linux:
```
mkdir build && cmake ..
```

- On Windows
```
mkdir build && cmake -G "NMake Makefiles" ..
```


License
----

The code is licensed under Apache License v2
