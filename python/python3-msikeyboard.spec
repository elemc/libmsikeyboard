%global         srcname msikeyboard
Name:           python3-%{srcname}
Version:        0.3.3
Release:        2%{?dist}
Summary:        Python library for change LED color, intensity and mode on MSI keyboards

License:        GPLv3
URL:            https://elemc.name
Source0:        https://elemc.name/sources/%{name}-%{version}.tar.xz

BuildRequires:  hidapi-devel
BuildRequires:  gcc gcc-c++
BuildRequires:  python3-devel
BuildRequires:  python3-setuptools
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
%{python3_sitearch}/%{srcname}-*.egg-info/
%{python3_sitearch}/%{srcname}*
%{python3_sitearch}/MSIKeyboard

%changelog
* Sun Dec 26 2021 Alexei Panov <me AT elemc DOT name> 0.3.3-2
- changed URLs 

* Tue May 12 2020 Alexei Panov <me AT elemc DOT name> 0.3.3-1
- initial package build

