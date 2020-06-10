NAME = calculadora
OBJ = $(NAME).o lexico.o

$(NAME) : $(OBJ)     #segunda fase de la traducción. Generación del código ejecutable 
	g++ -o$(NAME) $(OBJ)

$(NAME).o : $(NAME).c        #primera fase de la traducción del analizador sintáctico
	g++ -c -o$(NAME).o  $(NAME).c 
	
lexico.o : lex.yy.c		#primera fase de la traducción del analizador léxico
	g++ -c -olexico.o  lex.yy.c 	

$(NAME).c : $(NAME).y       #obtenemos el analizador sintáctico en C
	bison -d -v -o$(NAME).c $(NAME).y

lex.yy.c: lexico.l	#obtenemos el analizador léxico en C
	flex lexico.l

clean : 
	rm  -f *.o *.output $(NAME).c $(NAME).h $(NAME) *.cpp *.txt
