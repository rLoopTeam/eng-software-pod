doxygen LFW513.doxygen > dox.txt
mkdir PDF
cd PDF
del *.pdf
cd..
cd OUTPUT
cd LATEX
start /wait make.bat
copy refman.pdf ..\..\PDF\
cd..
cd..
cd PDF
ren refman.pdf LFW513__DOXYGEN.PDF
pause