Summary:            Generic Reusable Utilities (GRU) library
Name:               gru
Version:            0.2.0
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
%cmake -DBUILD_WITH_DOCUMENTATION=ON -DCMAKE_USER_C_FLAGS="-fPIC" ..
make all documentation

%install
cd build
make install DESTDIR=%{buildroot}

%files
%doc AUTHORS README.md LICENSE COPYING
%{_libdir}/*


%files devel
%{_includedir}/*

%files devel-docs
%{_datadir}/*


%changelog
* Thu Jul 27 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-2
- Updated package to comply with Fedora packaging guidelines
- Enabled generation of debuginfo package

* Fri Nov 04 2016 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0
- Changed non-write interfaces of the list to use a const pointer

* Tue Sep 06 2016 Otavio R. Piske <angusyoung@gmail.com> - 0.1.0
- Initial release
