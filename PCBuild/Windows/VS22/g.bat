set current=%~dp0
set base=%current%..\..\..\
set build=%base%build\Windows\VS22

cmake -S %base% -B %build% -G "Visual Studio 17 2022"