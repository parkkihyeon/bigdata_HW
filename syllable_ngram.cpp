#include "syllable_ngram.h"

void Syllable_ngram() {
	system("del /q word.txt") ;
	FILE * fp_input = fopen(INPUTTXT, "r");
	FILE * fp_output = fopen(OUTPUTTXT, "w");

	int c1, c2 , ngram, ncount = 0, max_filepointersize ;
	long file_pointersize = 0 ;
	bool first_texthangul = true ;

	fflush(stdin) ;
	while(1){
		printf("\t음절의 수를 쓰시오\n") ;
		ngram = Keyboard_Safeinput() ;
		if(ngram >= MIN_NGRAM && ngram <= MAX_NGRAM) 
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
	Wordcount_excute() ;
}

void Syllable_search(){
	printf("************************* 주 의 사 항 ! ! ! *******************\n") ;
	printf("\t Search를 하기전에 word.txt를 생성하세요.(분류를 먼저 해야합니다)\n") ;
	printf("***************************************************************\n") ;
	printf("\t1 : unigram, 2 : ngram , 3: 나가기\n") ;
	printf("***************************************************************\n") ;
	printf("\t< 음절 > \n") ;
	int num = Keyboard_Safeinput() ;
	switch(num){
	case 1:
		Syllable_onesearch() ;
		break ;
	case 2:
		{
			FILE * fp_input = fopen("word.txt", "r");
			char search[BUFSIZ], temp[BUFSIZ] ;
			int size ;
			bool success = false ;

			printf("\t검색 : ") ;
			scanf("%s", &search) ;
			while(!feof(fp_input)){
				fscanf(fp_input, "%d %s", &size, temp) ;
				if(!strcmp(temp,search)){
					printf("\t[%s] : %d\n", search, size);
					success= true ;
					break ;
				}
			}	
			if(!success) {
				printf("\t 검색 실패 \n") ;
				printf("*********** Search는 전처리 되어야 합니다. ************\n") ;
			}
			fclose(fp_input) ;
			break ;
		}
	default :
		break ;
	}


}

//음절
void Syllable_Process(){
	system("cls") ;
	int num ;
	while(1){
		Question_gram() ;
		printf("\t< 음절 > \n") ;
		num = Keyboard_Safeinput() ;
		switch(num){
		case 1:
			Frequency_research() ;
			Syllable_unigram() ;
			break ;
		case 2:
			Syllable_ngram() ;
			break ;
		case 3:
			Syllable_search() ;
			break ;
		default :
			return ;
		}
	}
}

