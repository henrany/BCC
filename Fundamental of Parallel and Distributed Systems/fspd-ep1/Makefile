all: numcheckseq numcheckfuncpar numcheckdatapar

clean: 
	/bin/rm -f *.o numcheckseq numcheckfuncpar numcheckdatapar

# vcoê deve criar as regras para gerar os dois outros programas.

numcheckseq: conditions.o numchecks.o timediff.o numcheckseq.o
	gcc -Wall conditions.o numchecks.o timediff.o numcheckseq.o -o numcheckseq

numcheckfuncpar: conditions.o numchecks.o timediff.o numcheckfuncpar.o
	gcc -pthread -Wall conditions.o numchecks.o timediff.o numcheckfuncpar.o -o numcheckfuncpar

numcheckdatapar: conditions.o numchecks.o timediff.o numcheckdatapar.o
	gcc -pthread -Wall conditions.o numchecks.o timediff.o numcheckdatapar.o -o numcheckdatapar

numcheckseq.o: numcheckseq.c conditions.h numchecks.h timediff.h
	gcc -Wall -c numcheckseq.c

numcheckfuncpar.o: numcheckfuncpar.c conditions.h numchecks.h timediff.h
	gcc  -pthread -Wall -c  numcheckfuncpar.c 

numcheckdatapar.o: numcheckdatapar.c conditions.h numchecks.h timediff.h
	gcc  -pthread -Wall -c  numcheckdatapar.c 

conditions.o: conditions.c conditions.h
	gcc -Wall -c conditions.c

numchecks.o: numchecks.c numchecks.h
	gcc -Wall -c numchecks.c

timediff.o: timediff.c timediff.h
	gcc -Wall -c timediff.c
