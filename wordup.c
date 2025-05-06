//Name: Hai Vu Vu
//Date: 05/06/2025
//Purpose: Worlde game
//Suffering for real to figure out how to stop the ^ if the letter is repeated (words like "Loose" eventhough i made it up but i can't figure out how. =(( sorry


#include<stdio.h>
#define ReadFile "mystery.txt"

void scan_correct(FILE* WORD,char answer[]);
void INPUT(int row, char GUESS[][100]);
void CORRECT(int column, int row, char GUESS[][100], char answer[],char OUTPUT[][100]);
void LINE(int row, char OUTPUT[][100], char answer[], char point[][100]);
void CONGRATS(int num, char answer[]);
void LOST(char answer[]);

int main(){
	FILE* WORD;
	WORD=fopen(ReadFile, "r");
	char answer[100];
	char GUESS[6][100];
	char OUTPUT[6][100];
	char point[6][100];
	int row=0;
	int num=1;
	int count=0;
	int prize;
	if(WORD==NULL){
		printf("ERROR in opening \"WORD\"");
		return 0;
	}
	else{
		printf("You've started a Wordle game, start by entering a 5 character word.\n");
		printf("You have 6 tries.\nCorrect words are capitalized. Words that are in the wrong position is point with \"^\" symbol");
		scan_correct(WORD, answer);
		do{
			if(num<6){
				printf("\nGUESS %d! Enter your guess:", num);
				INPUT(row, GUESS);
				for(int i=0;GUESS[row][i]!='\0';i++){
					if(GUESS[row][i]>='A' && GUESS[row][i]<='Z'){
						GUESS[row][i]=GUESS[row][i] + ('a'-'A');
					}
				}
				printf("============================================");
				while(GUESS[row][count]!='\0' && answer[count]!='\0'){
					if(GUESS[row][count]!=answer[count]){
						prize=0;
						break;
					}
					else{
						prize=1;
					}
					count++;
				}
				if(prize==1){
					CONGRATS(num, answer);
					break;
				}
				else{
				
					CORRECT(6, row, GUESS, answer, OUTPUT);
					LINE(row, OUTPUT, answer, point);
					for(int rowI=0; rowI<row+1;rowI++){
						printf("\n%s", OUTPUT[rowI]);
						printf("\n%s", point[rowI]);
					}
					row++;
					printf("\n");
					
				}
			}
			else if(num==6){
				printf("\nFinal GUESS: ");
				INPUT(row, GUESS);
				while(GUESS[row][count]!='\0' && answer[count]!='\0'){
					if(GUESS[row][count]!=answer[count]){
						prize=0;
						break;
					}
					else{
						prize=1;
					}
					count++;
				}
				if(prize==1){
					printf("============================================");
					CONGRATS(num, answer);
					break;
				}
				else{
					printf("============================================");
					LOST(answer);
				}
			}
		num++;
		}while(num<=6);
	}	
	fclose(WORD);
return 0;
}

void scan_correct(FILE* WORD,char answer[]){
		fscanf(WORD, "%s", answer);
}

void INPUT(int row, char GUESS[][100]){
	while(1){
		scanf("%s", GUESS[row]);
		int length=0;
		while(GUESS[row][length]!='\0'){
			length++;
		}
		if(length==5){
			break;
		}
		else{
			printf("\nYour guess must be 5 letters long.");
			printf("\nPlease try again: ");
		}
	}
}

void CORRECT(int column, int row, char GUESS[][100], char answer[], char OUTPUT[][100]){
	for(int i=0;GUESS[row][i]!='\0';i++){
		OUTPUT[row][i]=GUESS[row][i];
	}
	OUTPUT[row][5]='\0';
	for(int j=0;GUESS[row][j]!='\0'&& answer[j] !='\0' ;j++){
		if(GUESS[row][j]==answer[j]){
			OUTPUT[row][j]=answer[j] - 32;
		}
		else{
			OUTPUT[row][j]=GUESS[row][j];
		}
	}
}
	
void LINE(int row, char OUTPUT[][100], char answer[], char point[][100]){
	point[row][5]='\0';
	for(int i=0;OUTPUT[row][i]!='\0';i++){
		for(int j=0;answer[j]!='\0';j++){
			if(OUTPUT[row][i]-answer[j]==0){
				point[row][i]='^';
				break;
			}
			else if(OUTPUT[row][i]-answer[j]==32){
				point[row][i]=' ';
				break;
			}
			else{
				point[row][i]=' ';
			}
			
		}
	}
}



void CONGRATS(int num, char answer[]){
	printf("\n\t\t");
	printf("%s", answer);
	printf("\n\tYou won in %d guesses!", num);
	if(num==1){
		printf("\n\t\tGOATED!\n");
	}
	else if(num==2 ||num==3){
		printf("\n\t\tAMAZING!\n");
	}
	else if(num==4||num==5){
		printf("\n\t\tNice!\n");	
	}
	else if(num==6){
		printf("\n");
	}
}

void LOST(char answer[]){
	printf("\nThe word was %s!", answer);
	printf("\nYou've lost, better luck next time!\n");
}
