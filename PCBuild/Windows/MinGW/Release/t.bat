set current=%~dp0
set base=%current%..\..\..\..\
set build=%base%build\Windows\MinGW\Release\

cd %build%
NTTLib_test.exe
cd %current%
