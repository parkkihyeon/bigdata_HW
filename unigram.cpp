#include"unigram.h"

int freq[ASCII_NUM] = { 0 };  // 아스키 문자 빈도조사
int hfreq[HANGUL_HEIGHT][HANGUL_WIDTH]; // 한글 빈도조사

void Ascii_frequency(int ch, int freq[])
{
	if(ch < 128 )
		freq[ch]++ ;
}

void Hangul_frequency(int c1, int c2, int hfreq[HANGUL_HEIGHT][HANGUL_WIDTH])
{
	if (c1 >= 0xB0 && c1 <= 0xC8 && c2 >= 0xA1 && c2 <= 0xFE) // 한글 빈도조사
		hfreq[c1-0xB0][c2-0xA1]++;
}

bool Ishangul(char c1){
	if(c1 & 0x80) 
		return true ;
	else return false ;
}

void Frequency_research(){
	int c1, c2;
	FILE * fp_input = fopen("input.txt", "r");

	while (!feof(fp_input)) {
		c1 = fgetc(fp_input) ;
		if (Ishangul(c1)) 
			c2 = fgetc(fp_input) ;
		Ascii_frequency(c1, freq) ;
		Hangul_frequency(c1,c2,hfreq) ;

	}
	fclose(fp_input) ;
}

void Word_unigram() {
	int i, j ;
	printf("\t빈도의 총계\n") ;

	for(int i = 0 ; i < 128 ; i++ ){
		if(freq[i]){
			if( i == char('\n')){
				printf("\tf[\\n] = %d\n", i, freq[i]) ;
			}
			else
				printf("\tf[%c] = %d\n", i, freq[i]) ;
		}
	}

	for (i=0xB0; i <= 0xC8; i++) { // 한글 빈도조사
		for (j=0xA1; j <= 0xFE; j++) {
			if (hfreq[i-0xB0][j-0xA1]){
				printf("\tf[%c%c] = %d\n", i, j, hfreq[i-0xB0][j-0xA1]);
			}
		}
	}
}


void Question_gram() {
	printf("*******************************************************\n") ;
	printf("\t1.unigram\t2.ngram \t3.나가기\n") ;
	printf("*******************************************************\n\t") ;
	printf("입력 : " ) ;
}