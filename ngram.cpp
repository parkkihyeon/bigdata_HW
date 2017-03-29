#include "ngram.h"

void Ngram_menu() {
	FILE * fp_input = fopen("input.txt", "r");
	FILE * fp_output = fopen("output.txt", "w");

	int c1, c2 , ngram, ncount = 0, max_filepointersize ;
	long file_pointersize = 0 ;
	bool first_texthangul = true ;

	printf("\n\tn을 입력 : " ) ;
	while(1){
		scanf("%d", &ngram) ;
		if(ngram >= 2 && ngram <= 5) 
			break ;
		else 
			printf("\t재입력 : " ) ; 
	}

	while(1){
		ncount++ ;
		c1 = fgetc(fp_input) ;
		file_pointersize++ ;

		// 파일이 끝나면 루프를 빠져나온다
		if(feof(fp_input)){
			fprintf(fp_output, "%c", '_') ;
			break ;
		}

		// 한글이면
		if ( Ishangul(c1)) {
			c2 = fgetc(fp_input) ;	
			file_pointersize++ ;
			fprintf(fp_output,"%c%c", c1, c2) ;
		}
		// 개행이면
		else if(c1 == '\n') {
			// 첫번째 단어가 개행이면 바로 다음 단어로 넘어감
			if(ncount == 1 ) {
				first_texthangul = true ;
				file_pointersize = 0 ;
			}
			else {
				file_pointersize++ ;
			}
			ncount-- ;
		}
		// 나머지 문자면
		else {
			if(ncount == 1)
				first_texthangul = false ;
			if(c1 == ' ') c1 = '_' ;
			fprintf(fp_output,"%c", c1) ;
		}
		// 같으면 출력을 마무리 한 후에 포인터를 옮긴다.
		if(ncount == ngram){
			if(first_texthangul) {
				file_pointersize -= 2 ;
			}
			else 
				file_pointersize -= 1 ;
			fprintf(fp_output,"\n") ;
			fseek( fp_input, -file_pointersize, SEEK_CUR );    //현재 위치(6)에서 2번 앞으로 이동
			first_texthangul = true ;
			file_pointersize = 0 ;
			ncount = 0 ;
		}
	}
	fclose(fp_input) ;
	fclose(fp_output) ;

	system("\"wordcount.exe\" -new -6 output.txt word.txt") ;

	FILE * fp_print = fopen("word.txt", "r") ;

	printf("\n\t빈도 카운트 출력\n\n") ;
	printf("    빈도 %d음절\n\n", ngram) ;
	while(true){
		char frequency[100] ;
		fgets(frequency, 100, fp_print) ;
		if(feof(fp_print)) break ;
		printf("%s\n", frequency) ;
	}

	fclose(fp_print) ;
	system("del \q word.txt") ;
}


//음절
void Syllable_Process(){
	int num ;
	while(1){
		Question_gram() ;
		scanf("%d", &num) ;
		switch(num){
		case 1:
			Frequency_research() ;
			Word_unigram() ;
			break ;
		case 2:
			Ngram_menu() ;
			break ;
		default :
			return ;
		}
	}
}