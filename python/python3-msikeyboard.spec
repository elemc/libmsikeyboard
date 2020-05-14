%global         srcname msikeyboard
Name:           python3-%{srcname}
Version:        0.3.3
Release:        1%{?dist}
Summary:        Python library for change LED color, intensity and mode on MSI keyboards

License:        GPLv3
URL:            http://elemc.name
Source0:        http://repo.elemc.name/sources/%{name}-%{version}.tar.xz

BuildRequires:  hidapi-devel
BuildRequires:  gcc gcc-c++
BuildRequires:  python3-devel
BuildRequires:  boost-devel
BuildRequires:  libmsikeyboard-devel

%description
Python library for change LED color, intensity and modes on MSI keyboards

%prep
%autosetup

%build
%py3_build


%install
rm -rf $RPM_BUILD_ROOT
%py3_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%license LICENSE
%doc README.md
%{python3_sitearch}/%{srcname}-*.egg-info/
%{python3_sitearch}/%{srcname}*
%{python3_sitearch}/MSIKeyboard

%changelog
* Tue May 12 2020 Alexei Panov <me AT elemc DOT name> 0.3.3-1
- initial package build

