@echo off
setlocal

:: --- AYARLAR ---
set APP_NAME=IsoRPG
set COMPILER=g++

:: Raylib Yolu (Proje icindeki relative path)
:: Kullanicinin belirttigi yol: third_party\raylib\include\raylib.h
set RAYLIB_HOME=third_party\raylib

:: Include Yollari
:: Hem kendi src klasorumuz hem de raylib include klasoru
set INCLUDE_FLAGS=-I./src -I%RAYLIB_HOME%\include

:: Library Yollari
:: Genellikle .a veya .lib dosyalari 'lib' klasorunde olur. 
:: Eger derlemede hata alirsan 'lib' yerine 'src' yapmayi dene.
set LIB_FLAGS=-L%RAYLIB_HOME%\lib -lraylib -lopengl32 -lgdi32 -lwinmm

:: --- KAYNAK DOSYALAR ---
:: highlight.cpp ismini duzelttigini varsayiyorum
set SRC_FILES=src\main.cpp ^
              src\entities\map.cpp ^
              src\entities\player.cpp ^
              src\rendering\highlight.cpp

:: --- DERLEME ISLEMI ---
echo [LEAD PROGRAMMER] Derleme baslatiliyor...
echo Raylib Konumu: %RAYLIB_HOME%

%COMPILER% %SRC_FILES% -o %APP_NAME% %INCLUDE_FLAGS% %LIB_FLAGS% -std=c++17 -Wall -Wno-missing-braces

if %errorlevel% neq 0 (
    echo.
    echo [KRITIK HATA] Derleme basarisiz oldu!
    echo Olasiliklar:
    echo 1. 'third_party\raylib\lib' klasoru var mi? Icinde 'libraylib.a' var mi?
    echo 2. Eger yoksa, bat dosyasinda 'lib' yerine 'src' yapip dene.
    echo 3. g++ (MinGW) kurulu ve PATH'e ekli mi?
    pause
    exit /b %errorlevel%
)

echo.
echo [BASARI] Kodlar buyulendi ve exe hazir!
echo Baslatiliyor...
echo.

:: Oyunu başlat
%APP_NAME%

:: Program kapanırsa veya çökerse hemen kapanma, bekle:
echo.
echo [BILGI] Program sonlandi. Cikis kodu: %errorlevel%
pause