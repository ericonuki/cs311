CC = icc
CXX = icpc
CFLAGS = -Wall -std=gnu99 -openmp -O2 -g -I.
CFLAGS_DEBUG = -Wall -std=gnu99 -openmp -O0 -g -I.
CXXFLAGS = -Wall -openmp -O3 -g
#overkill on the flags, but that doesn't hurt anything
#add current dir to libs for libjsmn.a
LDFLAGS = -lrt -lpthread -L. -ljsmn
#replace this if you want to change the output name
CTARGET = compute
TEXTARGET = writeup

# LaTeX related constants
HTML=main_html
SRC=mt.h

#any headers go here
INCLUDES = 

#any .c or .cpp files go here
SOURCE = compute.c

#default is to compile and pdf
default: compile pdf
both: pdf html

#depends on all of you source and header files
compile: ${SOURCE} ${INCLUDES}
#this assumes you actually are linking all of the source files together
	${CC} ${CFLAGS} ${SOURCE} -o ${CTARGET} ${LDFLAGS}

debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS_DEBUG} ${SOURCE} -o ${CTARGET} ${LDFLAGS} -DDEBUG

dvi: ${TEXTARGET}.tex
#	pygmentize the input source file -- THIS NAME SHOULD BE SAFE
	pygmentize -f latex -o __${SRC}.tex ${SRC}
#	run latex twice to get references correct
	latex ${TEXTARGET}.tex
#	you can also have a bibtex line here
#	bibtex $(TEXTARGET).tex
	latex $(TEXTARGET).tex
#	remove the pygmentized output to avoid cluttering up the directory
	rm __${SRC}.tex

ps: dvi
	dvips -R -Poutline -t letter ${TEXTARGET}.dvi -o ${TEXTARGET}.ps

pdf: ps
	ps2pdf ${TEXTARGET}.ps


html:
	cp ${TEXTARGET}.tex ${HTML}.tex
	latex ${HTML}.tex
	latex2html -split 0 -noshow_section_numbers -local_icons -no_navigation -noinfo -noaddress ${HTML}

	sed 's/<BR><HR>//g' < ${HTML}/index.html > ${HTML}/index2.html
	mv ${HTML}/index2.html ${TEXTARGET}.html
	rm ${HTML}.*
	rm -rf ${HTML}

clean:
	rm ${TEXTARGET}.dvi ${TEXTARGET}.log ${TEXTARGET}.out ${TEXTARGET}.ps ${TEXTARGET}.aux ${TEXTARGET}.pdf ${CTARGET}
