#include "word_gram.h"

void Word_unigram(){
	system("del /q word.txt") ;
	FILE * fp_input = fopen(INPUTTXT, "r");
	FILE * fp_output = fopen(OUTPUTTXT, "w");
	char word[BUFSIZ] ;

	while(!feof(fp_input)){
		fscanf(fp_input, "%s\n", word);
		fprintf(fp_output, "%s\n", word) ;
	}

	fclose(fp_input) ;
	fclose(fp_output) ;
	system("\"wordcount.exe\" -new -l -6 output.txt word.txt") ;
	Wordcount_excute() ;
}

void Word_ngram(){
	system("del /q word.txt") ;
	FILE * fp_input = fopen(INPUTTXT, "r");
	FILE * fp_output = fopen(OUTPUTTXT, "w");
	long filepointer = 0 ;
	int ncount = 0 ;
	int first_wordlen = 0 , ngram, c1, c2 , file_pointersize = 0 ;
	boolean first_word = true, isword = false ;
	char word[BUFSIZ] ;

	printf("\t어절의 수\n") ;
	while(1){
		ngram = Keyboard_Safeinput() ;
		if(ngram >= MIN_NGRAM && ngram <= MAX_NGRAM) 
			break ;
		else 
			printf("\t재입력 : " ) ; 
	}

	//아아 aaaaa bbb    시발련아 ㅋ
	while(1){
		c1 = fgetc(fp_input) ;
		if ( Ishangul(c1)) {
			c2 = fgetc(fp_input) ;	
			file_pointersize+= 2 ;
			if(c1 >= 0xB0 && c1 <= 0xC8 ){
				fprintf(fp_output,"%c%c", c1, c2) ;
				isword = true ;
			}
		}
		else if ( c1 <= 127 && c1 != ' ' && c1 != '\n'){
			fprintf(fp_output, "%c", c1) ;
			isword = true ;
			file_pointersize++ ;
		}
		else {
			if(c1 == ' ' || c1 == '\n'){
				if(c1 == '\n')
					file_pointersize += 2 ;
				else if(c1 == ' ')
					file_pointersize ++ ;
				else
					file_pointersize += 2;

				while(1){
					c1 = fgetc(fp_input) ;
					if(c1 == ' ' )
						file_pointersize++ ;
					else if(c1 == '\n')
						file_pointersize += 2 ;
					else if(c1 == 0xa1){
						fgetc(fp_input) ;
						file_pointersize += 2 ;
					}
					else {
						if(isword){
							ncount++ ;
							fprintf(fp_output, " ") ;
							if(feof(fp_input))break ;
							fseek(fp_input, -1, SEEK_CUR) ;
						}
						break ;
					}
				}
			}
			if(first_word){
				first_wordlen += file_pointersize ;
				first_word = false ;
			}
		}

		if(feof(fp_input))break ;

		if(ncount == ngram){
			fprintf(fp_output, "\n") ;
			fseek(fp_input, -(file_pointersize-first_wordlen), SEEK_CUR) ;
			file_pointersize = 0 ;
			first_wordlen = 0 ;
			ncount = 0 ;
			first_word = isword = true ;
		}


	}

	fclose(fp_input) ;
	fclose(fp_output) ;
	system("\"wordcount.exe\" -new -l -6 output.txt word.txt") ;
	Wordcount_excute() ;
}

void Word_Search(){
	printf("\t어절을 입력하시오\n") ;
	printf("\tngram으로 원하는 n어절을 입력 후, 해당 하는 어절을 입력하세요.\n") ;
	FILE * fp_input = fopen("word.txt", "r");
	char search[BUFSIZ], temp[BUFSIZ] ;
	int size ;
	boolean success = false ;

	printf("\t검색 : ") ;
	fflush(stdin) ;
	gets(search) ;
	fflush(stdin) ;
	printf("\n") ;

	while(!feof(fp_input)){
		fscanf(fp_input, "%d", &size) ;
		fgets(temp,BUFSIZ, fp_input) ;
		if(strstr(temp, search) != NULL){
			printf("\t%s \t\t 총 갯수 : %d\n", temp, size);
			success= true ;
		}
	}	
	if(!success) {
		printf("\t 검색 실패 \n") ;
		printf("*********** Search는 전처리 되어야 합니다. ************\n") ;
	}
	fclose(fp_input) ;

}


void Word_Process(){
	system("cls") ;
	int num ;
	while(1){
		Question_gram() ;
		printf("\t< 어절 > \n") ;
		num = Keyboard_Safeinput() ;
		switch(num){
		case 1:
			Word_unigram() ;
			break ;
		case 2:
			Word_ngram() ;
			break ;
		case 3:
			Word_Search() ;
			break ;
		default :
			return ;
		}
	}
}