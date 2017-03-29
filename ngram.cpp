#include "ngram.h"

void Ngram_menu() {
	FILE * fp_input = fopen("input.txt", "r");
	FILE * fp_output = fopen("output.txt", "w");

	int c1, c2 , ngram, ncount = 0, max_filepointersize ;
	long file_pointersize = 0 ;
	bool first_texthangul = true ;

	printf("\n\tn�� �Է� : " ) ;
	while(1){
		scanf("%d", &ngram) ;
		if(ngram >= 2 && ngram <= 5) 
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

	FILE * fp_print = fopen("word.txt", "r") ;

	printf("\n\t�� ī��Ʈ ���\n\n") ;
	printf("    �� %d����\n\n", ngram) ;
	while(true){
		char frequency[100] ;
		fgets(frequency, 100, fp_print) ;
		if(feof(fp_print)) break ;
		printf("%s\n", frequency) ;
	}

	fclose(fp_print) ;
	system("del \q word.txt") ;
}


//����
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