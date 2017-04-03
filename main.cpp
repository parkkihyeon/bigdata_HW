#include "bigdata.h"


int main()
{
	int num ;
	while(1){
		system("cls") ;
		printf("검색을 하기 위해선 ngram으로 실행하여 word.txt를 채우세요. \nngram으로 할 때 마다 결과값은 중첩되지 않습니다. 새로운 ngram 명령 후 자동으로 word.txt는 삭제됩니다.\n") ;
		printf("*******************************************************\n") ;
		printf("\t1.음절\t\t2.어절\t\t3.나가기\n") ;
		printf("*******************************************************\n\t") ;
		num = Keyboard_Safeinput() ;
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
