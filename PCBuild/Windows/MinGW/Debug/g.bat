set current=%~dp0
set base=%current%..\..\..\..\
set build=%base%build\Windows\MinGW\Debug\

cmake -S %base% -B %build% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DNTTLib_USE_TESTS=ON -DNTTLib_USE_EXAMPLES=ON