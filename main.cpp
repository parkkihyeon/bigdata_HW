#include"unigram.h"

void Frequency_research();
void Word_unigram() ;
void Syllable_Process() ;
void Word_Process() ;
void Ngram_menu() ;

int main()
{
	int num ;
	while(1){
		printf("*******************************************************\n") ;
		printf("\t1.����\t\t2.����\t\t3.������\n") ;
		printf("*******************************************************\n\t") ;
		printf("�Է� : " ) ;
		scanf("%d", &num) ;
		switch(num){
		case 1:
			Syllable_Process() ;
			break ;
		case 2:
			Word_Process() ;
			break ;
		default :
			exit(1) ;
		}
	}
}



void Word_Process(){
	int num ;
	while(1){
		Question_gram() ;
		scanf("%d", &num) ;
		switch(num){
		case 1:
			//	Frequency_research() ;
			//	All_Search() ;
			break ;
		case 2:
			//	Ngram_menu() ;
			break ;
		default :
			return ;
		}
	}
}

