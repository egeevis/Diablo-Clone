@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo [LEAD PROGRAMMER] TANI VE DERLEME MODU BASLATILIYOR...
echo ========================================================
echo.

:: 1. KONTROL: Raylib Yolu
set RAYLIB_HOME=third_party\raylib
if exist "%RAYLIB_HOME%\include\raylib.h" (
    echo [OK] Raylib header bulundu: %RAYLIB_HOME%\include\raylib.h
) else (
    echo [HATA] Raylib header BULUNAMADI!
    echo Beklenen yer: %CD%\%RAYLIB_HOME%\include\raylib.h
    pause
    exit /b
)

if exist "%RAYLIB_HOME%\lib\libraylib.a" (
    echo [OK] Raylib static lib bulundu: %RAYLIB_HOME%\lib\libraylib.a
) else (
    echo [UYARI] 'lib' klasorunde libraylib.a yok.
    echo Eger 'src' icindeyse sorun yok, derleyici deneyecek.
)

echo.
echo ========================================================
echo DERLEME ISLEMI BASLIYOR
echo ========================================================

:: Derleme Ayarlari
set APP_NAME=IsoRPG
set COMPILER=g++
set INCLUDE_FLAGS=-I./src -I%RAYLIB_HOME%\include
:: Static flag ekledim: Bu, exe'nin baska DLL'lere ihtiyac duymamasini saglar (Raylib haric)
set FLAGS=-static -std=c++17 -Wall -Wno-missing-braces -g
set LIBS=-L%RAYLIB_HOME%\lib -lraylib -lopengl32 -lgdi32 -lwinmm

set SRC_FILES=src\main.cpp ^
              src\entities\map.cpp ^
              src\entities\player.cpp ^
              src\rendering\highlight.cpp

echo Komut calistiriliyor...
echo %COMPILER% %SRC_FILES% -o %APP_NAME% ...

:: Derleme komutunu çalıştır
%COMPILER% %SRC_FILES% -o %APP_NAME% %INCLUDE_FLAGS% %LIBS% %FLAGS%

:: Hata Kontrolü
if %errorlevel% neq 0 (
    echo.
    echo [KRITIK HATA] Derleme SIRASINDA hata olustu! (Hata Kodu: %errorlevel%)
    echo Yukaridaki kirmizi yazilari oku.
    echo.
    pause
    exit /b
)

echo.
echo [BASARI] Derleme tamamlandi! Exe olusturuldu.
echo.
echo ========================================================
echo OYUN BASLATILIYOR (Konsolu kapatma...)
echo ========================================================
echo.

:: 2. KONTROL: Raylib DLL
if not exist "raylib.dll" (
    echo [UYARI] Ana klasorde 'raylib.dll' bulunamadi.
    echo Eger statik linkleme yapilmadiysa oyun acilmayabilir.
    echo Oyun acilmazsa: third_party\raylib\lib (veya bin) icindeki raylib.dll'i buraya kopyala.
    echo.
)

:: Oyunu başlat ve bekle
%APP_NAME%

echo.
echo ========================================================
echo OYUN KAPANDI. (Cikis Kodu: %errorlevel%)
echo ========================================================
pause