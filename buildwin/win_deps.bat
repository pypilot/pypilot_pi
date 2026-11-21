::
:: Install build dependencies. Requires a working choco installation,
:: see https://docs.chocolatey.org/en-us/choco/setup.
::
:: Initial run will do choco installs requiring administrative
:: privileges.
::

:: Install the pathman tool: https://github.com/therootcompany/pathman
:: Fix PATH so it can be used in this script.
:: The regular installation using webi is broken since long, the root
:: cause (pun intended) is broken https setup at https://rootprojects.org.
::
set localbin="%HomeDrive%%HomePath%\.local\bin"
set pathman_path="buildwin\pathman.exe"
if not "%APPVEYOR_BUILD_FOLDER%" == "" (
    set pathman_path="%APPVEYOR_BUILD_FOLDER%\%pathman_path%"
)
if not exist "%HomeDrive%%HomePath%\.local\bin\pathman.exe" (
    if not exist %localbin% mkdir %localbin%
    copy %pathman_path%  %localbin%
)
pathman list > nul 2>&1
if errorlevel 1 set PATH=%PATH%;%HomeDrive%\%HomePath%\.local\bin
pathman add %HomeDrive%%HomePath%\.local\bin >nul

:: Install choco cmake and add it's persistent user path element
::
set CMAKE_HOME=C:\Program Files\CMake
if not exist "%CMAKE_HOME%\bin\cmake.exe" choco install --no-progress -y cmake
pathman add "%CMAKE_HOME%\bin" > nul

:: Install command-line gettext tools without the graphical Poedit installer.
::
set "GETTEXT_HOME=%ProgramFiles%\gettext-iconv"
if not exist "%GETTEXT_HOME%\bin\msgfmt.exe" (
    choco install --no-progress -y gettext
    if errorlevel 1 exit /b 1
)
pathman add "%GETTEXT_HOME%\bin" > nul
set "PATH=%GETTEXT_HOME%\bin;%PATH%"
msgfmt --version > nul 2>&1
if errorlevel 1 exit /b 1
msgmerge --version > nul 2>&1
if errorlevel 1 exit /b 1

:: Update required python stuff
::
if defined PYTHON set "PATH=%PYTHON%;%PYTHON%\Scripts;%PATH%"
python --version > nul 2>&1 && python -m ensurepip > nul 2>&1
if errorlevel 1 choco install --no-progress -y python
python --version
python -m ensurepip
python -m pip install --upgrade pip
python -m pip install -q setuptools wheel
python -m pip install -q cloudsmith-cli
if errorlevel 1 exit /b 1
python -m pip install -q cryptography
if errorlevel 1 exit /b 1

:: Install pre-compiled wxWidgets and other DLL; add required paths.
::
set SCRIPTDIR=%~dp0
set WXWIN=%SCRIPTDIR%..\cache\wxWidgets
set wxWidgets_ROOT_DIR=%WXWIN%
set wxWidgets_LIB_DIR=%WXWIN%\lib\vc_dll
if not exist "%WXWIN%" (
  wget --version > nul 2>&1 || choco install --no-progress -y wget
  wget -q https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxWidgets-3.2.6-headers.7z ^
      -O wxWidgetsHeaders.7z
  wget -q https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxMSW-3.2.6_vc14x_ReleaseDLL.7z ^
      -O wxWidgetsDLL.7z
  wget -q https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxMSW-3.2.6_vc14x_Dev.7z ^
      -O wxWidgetsDev.7z
  7z i > nul 2>&1 || choco install -y 7zip
  7z x -aoa wxWidgetsHeaders.7z -o%WXWIN%
  7z x -aoa wxWidgetsDLL.7z -o%WXWIN%
  7z x -aoa wxWidgetsDev.7z -o%WXWIN%
  ren "%WXWIN%\lib\vc14x_dll" vc_dll
)
pathman add "%WXWIN%" > nul
pathman add "%wxWidgets_LIB_DIR%" > nul

if not exist %SCRIPTDIR%\..\cache ( mkdir %SCRIPTDIR%\..\cache )
set "CONFIG_FILE=%SCRIPTDIR%\..\cache\wx-config.bat"
echo set "wxWidgets_ROOT_DIR=%wxWidgets_ROOT_DIR%" > %CONFIG_FILE%
echo set "wxWidgets_LIB_DIR=%wxWidgets_LIB_DIR%" >> %CONFIG_FILE%


call refreshenv
:: Preserve an explicitly selected host Python after refreshing the user PATH.
if defined PYTHON set "PATH=%PYTHON%;%PYTHON%\Scripts;%PATH%"
exit /b 0
