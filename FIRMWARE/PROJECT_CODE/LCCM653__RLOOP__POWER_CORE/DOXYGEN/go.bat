cd D:\SIL3\DESIGN\RLOOP\FIRMWARE\PROJECT_CODE\LCCM653__RLOOP__POWER_CORE\DOXYGEN\
D:\SIL3\DESIGN\LDL\COMMON_CODE\DOXYGEN\DOXY_1_8_11\bin\doxygen.exe LCCM653.doxygen > dox.txt
mkdir PDF
cd PDF
del *.pdf
cd..
cd OUTPUT
cd LATEX
rem start /wait make.bat
copy refman.pdf ..\..\PDF\
cd..
cd PDF
ren refman.pdf LCCM653__DOXYGEN.PDF
cd..
cd OUTPUT
cd html
del *.map
del *.dot
del *.md5
pause
