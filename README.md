GRU: generic reusable utilities
============

Build Status
----
Linux Build Status: [![Linux Build Status](https://travis-ci.org/orpiske/gru.svg?branch=master)](https://travis-ci.org/orpiske/gru)

Windows Build Status: [![Windows Build status](https://ci.appveyor.com/api/projects/status/18qfc92iatymg9aw?svg=true)](https://ci.appveyor.com/project/orpiske/gru)

Coverity Scan: [![Coverity Scan Build Status](https://scan.coverity.com/projects/10838/badge.svg)](https://scan.coverity.com/projects/orpiske-gru)

Codacity Report: [![Codacy Badge](https://api.codacy.com/project/badge/Grade/0b78101608f744dba5e561423bd32748)](https://www.codacy.com/app/orpiske/gru?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=orpiske/gru&amp;utm_campaign=Badge_Grade)

Packaging Status
----
Fedora (GRU Testing): [![Fedora COPR (Testing Repo) Status](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing/package/gru/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing/package/gru/)

Fedora (GRU Testing Legacy): [![Fedora COPR (Testing Repo) Status](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing-legacy/package/gru/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-testing-legacy/package/gru/)

Fedora (GRU Stable): [![Fedora COPR (Stable Repo) Status](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-stable/package/gru/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/orpiske/orp-tools-stable/package/gru/)


Introduction:
----

This library contains portable and reusable C code for very simple applications.

Installation:
----

The code can be installed via Fedora COPR. Packages are available for CentOS 6, 7, Fedora 25 
or greater and RHEL 6 and 7. For CentOS 6 and RHEL 6, please use the legacy repos (check the notes below). 

**Testing**

1. Enable my testing COPR.

```dnf copr enable orpiske/orp-tools-testing```

2. Install the runtime only:
```dnf install -y gru```

3. (Alternative) Install the development packages: 
```dnf install -y gru gru-devel gru-devel-doc```

**Note**: the testing packages are the **recommended** packages for this project.

**Note**: for RHEL 6 or CentOS 6, use the orp-tools-testing-legacy repository.

**Stable**

1. Enable my testing COPR.

```dnf copr enable orpiske/orpiske/orp-tools-stable ```

2. Install the runtime only:
```dnf install -y gru```

3. (Alternative) Install the development packages: 
```dnf install -y gru gru-devel gru-devel-doc```


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
