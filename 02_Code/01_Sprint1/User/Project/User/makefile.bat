REM ----------------------------------------------------------------
echo 提取库文件,拷贝入原.c所在文件夹,格式如下，注意相对路径，e c h o是注释命令，
echo 添加你的命令式不要加上此关键字
echo copy ..\..\..\out\build\i2c.o        ..\..\src_user\i2c\i2c.o

REM --------------------------------------------------------------------
echo 删除打包的文件，格式如下，e c h o是注释命令，
echo 添加你的命令式不要加上此关键字

echo del  ..\..\src_user\i2c\i2c.c

REM --------------------------------------------------------------------
DEL ..\..\..\out\hex\McuAppUpdate.img


DEL ..\..\..\out\hex\app.hex
rename ..\..\..\out\hex\HQ10.hex app.hex 
..\..\lib\tool\McuAutoMakeUpdate.exe ..\..\lib\tool\boot.hex ..\..\..\out\hex\app.hex ..\..\..\out\hex

DEL ..\..\..\out\hex\Mcu_download.hex
rename ..\..\..\out\hex\McuBootApp.hex  Mcu_download.hex  


DEL ..\..\..\out\hex\McuBootApp.bin
DEL ..\..\..\out\hex\app.hex