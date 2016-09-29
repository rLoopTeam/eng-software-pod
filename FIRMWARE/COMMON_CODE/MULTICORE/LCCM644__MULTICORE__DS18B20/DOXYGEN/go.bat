doxygen LCCM644.doxygen > dox.txt
mkdir PDF
cd PDF
del *.pdf
cd..
cd OUTPUT
cd LATEX
rem start /wait make.bat
copy refman.pdf ..\..\PDF\
cd..
cd..
cd PDF
ren refman.pdf LCCM644__DOXYGEN.PDF
pause
