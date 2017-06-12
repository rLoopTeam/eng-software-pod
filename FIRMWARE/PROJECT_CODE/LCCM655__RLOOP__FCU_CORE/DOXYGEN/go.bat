cd D:\SIL3\DESIGN\RLOOP\FIRMWARE\PROJECT_CODE\LCCM655__RLOOP__FCU_CORE\DOXYGEN\
D:\SIL3\DESIGN\LDL\COMMON_CODE\DOXYGEN\DOXY_1_8_11\bin\doxygen.exe LCCM655.doxygen > dox.txt
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
ren refman.pdf LCCM655__DOXYGEN.PDF
cd..
cd OUTPUT
cd html
del *.map
del *.dot
del *.md5
pause
