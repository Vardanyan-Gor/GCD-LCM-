@echo off
:menu
cls
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Get IP Address
echo 2. Make Traceroute
echo 3. Resolve DNS Name
echo 4. Encrypt Text (Blowfish/Caesar)
echo 5. Decrypt Text
echo 6. Encrypt File (Blowfish/Caesar)
echo 7. Decrypt File
echo 8. Compress File (LZ77)
echo 9. Decompress File
echo 10. Calculate Hash Value (Text/File)
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="0" goto exit
goto menu

:get_ip
ipconfig | findstr "IPv4" 
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
set /p target="Enter the hostname or IP address: "
tracert %target%
pause
goto menu

:resolve_dns
set /p dns_name="Enter the DNS name: "
nslookup %dns_name%
pause
goto menu

:encrypt_text
set /p text="Enter text to encrypt: "
set /p key="Enter the shift key (number): "
encrypt.exe text encrypt %key% "%text%"
pause
goto menu

:decrypt_text
set /p text="Enter text to decrypt: "
set /p key="Enter the shift key (number): "
encrypt.exe text decrypt %key% "%text%"
pause
goto menu

:encrypt_file
set /p input="Enter the input file path: "
set /p output="Enter the output file path: "
set /p key="Enter the shift key (number): "
encrypt.exe file encrypt %key% "%input%" "%output%"
pause
goto menu

:decrypt_file
set /p input="Enter the input file path: "
set /p output="Enter the output file path: "
set /p key="Enter the shift key (number): "
encrypt.exe file decrypt %key% "%input%" "%output%"
pause
goto menu

:compress_file
set /p input="Enter the file path to compress: "
set /p output="Enter the output file path (compressed): "
lz77.exe compress "%input%" "%output%"
pause
goto menu

:decompress_file
set /p input="Enter the file path to decompress: "
set /p output="Enter the output file path (decompressed): "
lz77.exe decompress "%input%" "%output%"
pause
goto menu
:hash_value
set /p input="!!!!! Enter text or file path: "
::echo Use PowerShell or external tools for hashing.
::echo Example: PowerShell command 'Get-FileHash' for file hashing.
echo Default Hashing. Result in def-hash-%input% file
certutil -hashfile %input% > def-hash-%input% 
echo Calculate Hash Value with MD5. Result in MD5-%input% file 
certutil -hashfile %input% MD5 > MD5%input%
echo Calculate Hash Value with SHA256. Result in SHA256-%input% file 
certutil -hashfile %input% SHA256 > SHA256-%input%
pause
goto menu

:exit
echo Exiting... Goodbye!

::exit
