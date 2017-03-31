#include"bigdata.h"

void Wordcount_excute(){
	system("cls") ;
	FILE * fp_print = fopen("word.txt", "r") ;

	printf("\n\t빈도 카운트 출력\n\n") ;
	while(true){
		char frequency[BUFSIZ] ;
		fgets(frequency, BUFSIZ, fp_print) ;
		if(feof(fp_print)) break ;
		printf("%s\n", frequency) ;
	}

	fclose(fp_print) ;
}

int Keyboard_Safeinput(){
	int num ;
	do{
		printf("\t정수를 입력하시오\n") ;
		fflush(stdin) ;
		printf("\t입력 : " ) ;
	}while(	scanf("%d", &num) != 1) ;
	return num ;
}
