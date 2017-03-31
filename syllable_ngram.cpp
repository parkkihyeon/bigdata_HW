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
		printf("\t������ ���� ���ÿ�\n") ;
		ngram = Keyboard_Safeinput() ;
		if(ngram >= MIN_NGRAM && ngram <= MAX_NGRAM) 
			break ;
		else 
			printf("\t���Է� : " ) ; 
	}

	while(1){
		ncount++ ;
		c1 = fgetc(fp_input) ;
		file_pointersize++ ;

		// ������ ������ ������ �������´�
		if(feof(fp_input)){
			fprintf(fp_output, "%c", '_') ;
			break ;
		}

		// �ѱ��̸�
		if ( Ishangul(c1)) {
			c2 = fgetc(fp_input) ;	
			file_pointersize++ ;
			fprintf(fp_output,"%c%c", c1, c2) ;
		}
		// �����̸�
		else if(c1 == '\n') {
			// ù��° �ܾ �����̸� �ٷ� ���� �ܾ�� �Ѿ
			if(ncount == 1 ) {
				first_texthangul = true ;
				file_pointersize = 0 ;
			}
			else {
				file_pointersize++ ;
			}
			ncount-- ;
		}
		// ������ ���ڸ�
		else {
			if(ncount == 1)
				first_texthangul = false ;
			if(c1 == ' ') c1 = '_' ;
			fprintf(fp_output,"%c", c1) ;
		}
		// ������ ����� ������ �� �Ŀ� �����͸� �ű��.
		if(ncount == ngram){
			if(first_texthangul) {
				file_pointersize -= 2 ;
			}
			else 
				file_pointersize -= 1 ;
			fprintf(fp_output,"\n") ;
			fseek( fp_input, -file_pointersize, SEEK_CUR );    //���� ��ġ(6)���� 2�� ������ �̵�
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
	printf("************************* �� �� �� �� ! ! ! *******************\n") ;
	printf("\t Search�� �ϱ����� word.txt�� �����ϼ���.(�з��� ���� �ؾ��մϴ�)\n") ;
	printf("***************************************************************\n") ;
	printf("\t1 : unigram, 2 : ngram , 3: ������\n") ;
	printf("***************************************************************\n") ;
	printf("\t< ���� > \n") ;
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

			printf("\t�˻� : ") ;
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
				printf("\t �˻� ���� \n") ;
				printf("*********** Search�� ��ó�� �Ǿ�� �մϴ�. ************\n") ;
			}
			fclose(fp_input) ;
			break ;
		}
	default :
		break ;
	}


}

//����
void Syllable_Process(){
	system("cls") ;
	int num ;
	while(1){
		Question_gram() ;
		printf("\t< ���� > \n") ;
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

