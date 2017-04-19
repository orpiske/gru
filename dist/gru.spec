%global _enable_debug_package 0
%global debug_package %{nil}

Summary:            Generic Reusable Utilities (GRU) library
Name:               gru
Version:            0.1.0
Release:            2%{?dist}
License:            Apache-2.0
Group:              Development/Tools
Source:             gru-%{version}.tar.gz
URL:                https://github.com/orpiske/gru
BuildRequires:      cmake
BuildRequires:      make
BuildRequires:      gcc
BuildRequires:      doxygen
BuildRequires:      uriparser-devel
Requires:           uriparser


%description
This library implements reusable C/C++ utilities, algorithms and features.


%package devel
Summary:            Generic Reusable Utilities (GRU) development kit
Requires:           gru
Requires:           uriparser-devel
Group:              Development/Libraries

%description devel
Development packages for the GRU library

%package devel-docs
Summary:            Generic Reusable Utilities (GRU) development kit documentation
Group:              Development/Libraries

%description devel-docs
Development documentation for the GRU library

%prep
%autosetup -n gru-%{version}

%build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DBUILD_WITH_DOCUMENTATION=ON -DCMAKE_INSTALL_PREFIX=%{buildroot}/usr ..
make all documentation

%install
cd build
make install

%files
%doc AUTHORS README.md LICENSE COPYING
%{_libdir}/*


%files devel
%{_includedir}/*

%files devel-docs
%{_datadir}/*


%changelog
* Tue Nov 04 2016 Otavio R. Piske <angusyoung@gmail.com> - 20161104
- Changed non-write interfaces of the list to use a const pointer

* Tue Sep 07 2016 Otavio R. Piske <angusyoung@gmail.com> - 20160907
- Initial release
