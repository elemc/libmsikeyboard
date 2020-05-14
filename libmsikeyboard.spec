%global         srcname msikeyboard
Name:           libmsikeyboard
Version:        0.3.3
Release:        1%{?dist}
Summary:        Library for change LED color, intensity and mode on MSI keyboards

License:        GPLv3
URL:            http://elemc.name
Source0:        http://repo.elemc.name/sources/%{name}-%{version}.tar.xz

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

%package -n     python3-%{srcname}
Summary:        Python files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description -n python3-%{srcname}
The python3-%{srcname} package contains python library files for
developing applications that use %{name}

%prep
%autosetup

%build
%meson
%meson_build
pushd python
%py3_build
popd


%install
rm -rf $RPM_BUILD_ROOT
%meson_install
pushd python
%py3_install
popd


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%check
%meson_test

%files
%license LICENSE
%doc README.md
%{_libdir}/*.so.*

%files devel
%doc README.md
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/msikeyboard.pc
%{_datadir}/cmake/Modules/Findlibmsikeyboard.cmake

%files -n python3-%{srcname}
%{python3_sitearch}/%{srcname}-*.egg-info/
%{python3_sitearch}/%{srcname}*
%{python3_sitearch}/MSIKeyboard

%changelog
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
