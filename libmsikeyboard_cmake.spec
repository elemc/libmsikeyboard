Name:           libmsikeyboard
Version:        0.2.1
Release:        1%{?dist}
Summary:        Library for change LED color, intensity and mode on MSI keyboards

License:        GPLv3
URL:            http://elemc.name
Source0:        http://repo.elemc.name/sources/%{name}-%{version}.tar.xz

BuildRequires:  hidapi-devel
BuildRequires:  cmake

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
%cmake -DCMAKE_BUILD_TYPE=Release .
%make_build


%install
rm -rf $RPM_BUILD_ROOT
%make_install
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%check
LD_LIBRARY_PATH=. ctest -V %{?_smp_mflags}

%files
%license LICENSE
%doc README.md
%{_libdir}/*.so.*

%files devel
%doc README.md
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/pkgconfig/msikeyboard.pc


%changelog
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
