%global srcname gru

Summary:            Generic Reusable Utilities (GRU) library
Name:               gru
Version:            0.2.2
Release:            1%{?dist}
License:            Apache-2.0
# Sources can be obtained by
# git clone https://github.com/orpiske/gru
# cd gru
# tito build --tgz
Source0:            %{name}-%{version}.tar.gz
URL:                https://github.com/orpiske/gru
BuildRequires:      cmake >= 3.0.0
BuildRequires:      make
BuildRequires:      gcc
BuildRequires:      gcc-c++
BuildRequires:      doxygen
BuildRequires:      uriparser-devel


%description
This library implements reusable C/C++ utilities, algorithms and features.


%package devel
Summary:            Generic Reusable Utilities (GRU) development kit
Requires:           %{name}%{?_isa} = %{version}-%{release}

%description devel
Development packages for the GRU library

%package devel-doc
Summary:            Generic Reusable Utilities (GRU) development kit documentation
BuildArch:          noarch

%description devel-doc
Development documentation for the GRU library

%prep
%autosetup -n gru-%{version}

%build
mkdir build
%cmake -DBUILD_WITH_DOCUMENTATION=ON -DCMAKE_USER_C_FLAGS="-fPIC" -S . -B build
cd build && %make_build all documentation

%install
cd build
%make_install

%files
%doc AUTHORS README.md
%license LICENSE COPYING
%{_libdir}/*.so.*

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files devel
%{_includedir}/*
%{_libdir}/*.so

%post devel -p /sbin/ldconfig

%postun devel -p /sbin/ldconfig

%files devel-doc
%license LICENSE COPYING
%{_datadir}/*


%changelog
* Sat Mar 05 2022 Otavio R. Piske <angusyoung@gmail.com> 0.2.2-1
- gru build requires CMake 3 or greater (angusyoung@gmail.com)
- Updated readme (angusyoung@gmail.com)

* Sat Mar 05 2022 Otavio R. Piske <angusyoung@gmail.com> 0.2.1-1
- new package built with tito

* Fri Sep 24 2021 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-8
- Increase minimum cmake version

* Fri Nov 03 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-7
- Missing const declaration on keypair functions

* Wed Oct 04 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-6
- Removes incorrect debug message

* Wed Oct 04 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-5
- IPv6 handling fixes

* Sat Aug 26 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-4
- Adjusted to match fedora packaging guidelines

* Fri Jul 28 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-3
- Updated to contain timed logger fixes

* Thu Jul 27 2017 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0-2
- Updated package to comply with Fedora packaging guidelines
- Enabled generation of debuginfo package

* Fri Nov 04 2016 Otavio R. Piske <angusyoung@gmail.com> - 0.2.0
- Changed non-write interfaces of the list to use a const pointer

* Tue Sep 06 2016 Otavio R. Piske <angusyoung@gmail.com> - 0.1.0
- Initial release
