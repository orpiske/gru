%global _enable_debug_package 0
%global debug_package %{nil}

Summary:            Generic Reusable Utilities (GRU) library
Name:               gru
Version:            0.0.1
Release:            1%{?dist}
License:            Apache-2.0
Group:              Development/Tools
Source:             gru-%{version}.tar.gz
URL:                https://github.com/orpiske/gru
BuildRequires:      cmake
BuildRequires:      make
BuildRequires:      gcc


%description
This library implements reusable C/C++ utilities, algorithms and features.

%prep
%autosetup -n gru-%{version}

%build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=%{buildroot}/usr ..
make

%install
cd build
make install

%files
%doc AUTHORS README.md LICENSE COPYING
%{_libdir}/*
%{_includedir}/*


%changelog
* Tue Sep 07 2016 Otavio R. Piske <angusyoung@gmail.com> - 20160907
- Initial release
