@echo off
echo ========================================================
echo          TOWER OF HANOI - SFML BUILD SCRIPT             
echo ========================================================
echo.

if exist "SFML\include" (
    echo [INFO] Found local SFML directory inside this folder.
    echo Compiling main.cpp with local SFML include and lib paths...
    g++ main.cpp -I SFML\include -L SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o hanoi.exe
    if exist "SFML\bin\*.dll" (
        echo Copying runtime SFML DLLs to current folder...
        copy /Y SFML\bin\*.dll . > nul
    )
) else if exist "C:\SFML\include" (
    echo [INFO] Found SFML in C:\SFML.
    echo Compiling main.cpp with C:\SFML paths...
    g++ main.cpp -I C:\SFML\include -L C:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o hanoi.exe
    if exist "C:\SFML\bin\*.dll" (
        echo Copying runtime SFML DLLs to current folder...
        copy /Y C:\SFML\bin\*.dll . > nul
    )
) else (
    echo [INFO] Trying standard system SFML compiler paths...
    g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o hanoi.exe
)

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] Build succeeded! Executable created: hanoi.exe
    echo Run .\hanoi.exe to launch the SFML graphics visualizer.
) else (
    echo.
    echo [ERROR] Build failed! Please ensure you paste your downloaded SFML folder into this directory.
)
echo.
pause
