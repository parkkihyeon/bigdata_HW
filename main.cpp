#include "bigdata.h"


int main()
{
	int num ;
	while(1){
		system("cls") ;
		printf("�˻��� �ϱ� ���ؼ� ngram���� �����Ͽ� word.txt�� ä�켼��. \nngram���� �� �� ���� ������� ��ø���� �ʽ��ϴ�. ���ο� ngram ��� �� �ڵ����� word.txt�� �����˴ϴ�.\n") ;
		printf("*******************************************************\n") ;
		printf("\t1.����\t\t2.����\t\t3.������\n") ;
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
