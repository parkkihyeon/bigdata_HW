#include"bigdata.h"

void Wordcount_excute(){
	system("cls") ;
	FILE * fp_print = fopen("word.txt", "r") ;

	printf("\n\t�� ī��Ʈ ���\n\n") ;
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
		printf("\t������ �Է��Ͻÿ�\n") ;
		fflush(stdin) ;
		printf("\t�Է� : " ) ;
	}while(	scanf("%d", &num) != 1) ;
	return num ;
}
