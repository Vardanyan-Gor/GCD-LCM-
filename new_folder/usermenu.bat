@echo off
:menu
cls
echo ***********************************
echo        System Utility Menu
echo ***********************************
echo 1. Display Network Configuration
echo 2. Run Traceroute
echo 3. Lookup DNS
echo 4. Encrypt String
echo 5. Decrypt String
echo 6. Encrypt File
echo 7. Decrypt File
echo 8. Compress File (LZ77)
echo 9. Decompress File
echo 10. Generate Hash
echo 0. Exit Program
echo ***********************************
set /p option="Choose an action: "

if "%option%"=="1" goto show_network
if "%option%"=="2" goto run_traceroute
if "%option%"=="3" goto dns_lookup
if "%option%"=="4" goto encrypt_string
if "%option%"=="5" goto decrypt_string
if "%option%"=="6" goto encrypt_file
if "%option%"=="7" goto decrypt_file
if "%option%"=="8" goto file_compress
if "%option%"=="9" goto file_decompress
if "%option%"=="10" goto hash_generator
if "%option%"=="0" goto end
goto menu

:show_network
ipconfig /all
pause
goto menu

:run_traceroute
set /p hostname="Enter target hostname or IP: "
tracert %hostname%
pause
goto menu

:dns_lookup
set /p domain="Enter domain name: "
nslookup %domain%
pause
goto menu

:encrypt_string
set /p plaintext="Enter text to encrypt: "
set /p shift="Enter Caesar shift value: "
encrypt.exe string encrypt %shift% "%plaintext%"
pause
goto menu

:decrypt_string
set /p ciphertext="Enter text to decrypt: "
set /p shift="Enter Caesar shift value: "
encrypt.exe string decrypt %shift% "%ciphertext%"
pause
goto menu

:encrypt_file
set /p infile="Input file path: "
set /p outfile="Output file path: "
set /p shift="Enter Caesar shift value: "
encrypt.exe file encrypt %shift% "%infile%" "%outfile%"
pause
goto menu

:decrypt_file
set /p infile="Input file path: "
set /p outfile="Output file path: "
set /p shift="Enter Caesar shift value: "
encrypt.exe file decrypt %shift% "%infile%" "%outfile%"
pause
goto menu

:file_compress
set /p infile="File to compress: "
set /p outfile="Compressed file output: "
lz77_tool compress "%infile%" "%outfile%"
pause
goto menu

:file_decompress
set /p infile="File to decompress: "
set /p outfile="Decompressed file output: "
lz77_tool decompress "%infile%" "%outfile%"
pause
goto menu

:hash_generator
set /p target="Enter file or text to hash: "
echo Generating hash values...
certutil -hashfile "%target%" MD5 > hash_md5.txt
certutil -hashfile "%target%" SHA256 > hash_sha256.txt
echo Hash values saved to hash_md5.txt and hash_sha256.txt
pause
goto menu

:end
echo Program Terminated. Goodbye!
exit
