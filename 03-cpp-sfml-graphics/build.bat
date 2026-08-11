@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo          TOWER OF HANOI - SFML BUILD SCRIPT             
echo ========================================================
echo.

if not exist bin (
    mkdir bin
)

if exist "SFML\include" (
    echo [INFO] Found local SFML directory inside 03-cpp-sfml-graphics.
    echo Compiling main.cpp with SFML libraries...
    g++ main.cpp -I SFML\include -L SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o bin\hanoi-sfml.exe
    
    if exist "SFML\bin\*.dll" (
        echo Copying SFML runtime DLLs to bin directory...
        copy /Y "SFML\bin\*.dll" "bin\" > nul
    )
    if exist "C:\MinGW\bin\libstdc++-6.dll" (
        echo Copying MinGW runtime DLLs to bin directory...
        copy /Y "C:\MinGW\bin\libstdc++-6.dll" "bin\" > nul
        copy /Y "C:\MinGW\bin\libgcc_s_seh-1.dll" "bin\" > nul
        copy /Y "C:\MinGW\bin\libwinpthread-1.dll" "bin\" > nul
    )
) else (
    echo [INFO] Trying system SFML compiler paths...
    g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o bin\hanoi-sfml.exe
)

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] Build succeeded! Executable created: bin\hanoi-sfml.exe
    echo Launching SFML visualizer window...
    cd bin
    start "" "hanoi-sfml.exe"
    cd ..
) else (
    echo.
    echo [ERROR] Build failed! Please check compiler error output above.
)
echo.
pause
