Name:           libmsikeyboard
Version:        0.3.4
Release:        1%{?dist}
Summary:        Library for change LED color, intensity and mode on MSI keyboards

License:        GPLv3
URL:            https://elemc.name
Source0:        https://elemc.name/sources/%{name}-%{version}.tar.xz

BuildRequires:  hidapi-devel
BuildRequires:  meson
BuildRequires:  gcc gcc-c++
BuildRequires:  python3-devel
BuildRequires:  boost-devel

%description
Library for change LED color, intensity and modes on MSI keyboards

%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%prep
%autosetup

%build
%meson
%meson_build

%install
rm -rf $RPM_BUILD_ROOT
%meson_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%check
%meson_test

%files
%license LICENSE
%doc README.md
%{_libdir}/*.so.*

%files devel
%license LICENSE
%doc README.md
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/msikeyboard.pc
%{_datadir}/cmake/Modules/Findlibmsikeyboard.cmake

%changelog
* Sun Dec 26 2021 Alexei Panov <me AT elemc DOT name> 0.3.4-1
-  changed URLs to https

* Tue May 12 2020 Alexei Panov <me AT elemc DOT name> 0.3.3-1
- changed cmake find module

* Mon May 11 2020 Alexei Panov <me AT elemc DOT name> 0.3.2-1
- added cmake find module

* Fri Aug 10 2018 Alexei Panov <me AT elemc DOT name> 0.2.3-1
- Changed include files directory name

* Wed Aug 16 2017 Alexei Panov <me AT elemc DOT name> 0.2.2-1
- New release

* Tue Dec 27 2016 Alexei Panov <me AT elemc DOT name> 0.2.1-1
- Fix missing size_t bug

* Fri Dec 23 2016 Alexei Panov <me AT elemc DOT name> 0.2.0-2
- Fix C99 bug for EL7

* Fri Dec 23 2016 Alexei Panov <me AT elemc DOT name> 0.2.0-1
- New release

* Thu Dec 01 2016 Alexei Panov <me AT elemc DOT name> 0.1.0-3
- Change name in pc file

* Wed Nov 30 2016 Alexei Panov <me AT elemc DOT name> 0.1.0-2
- Change pkgconfig file

* Wed Nov 30 2016 Alexei Panov <me AT elemc DOT name> 0.1.0-1
- Initial build
