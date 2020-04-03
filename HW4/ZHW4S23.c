#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numLinesCmd();
void displayFile(FILE *, char *);
int countWords(FILE *);
int countSmall(FILE *);
int countCapital(FILE *);
int countDigits(FILE *);
int countSpaces(FILE *);
int countSymbol(FILE *);
void fileAnalysis(FILE *);
void rmSpaceConvLetter(FILE *, int, FILE*);
void lineNumber(FILE *, FILE *, int);

int main(){

  static int numLines;
  FILE *fileptr;
  FILE *fpOut1;
  FILE *fpOut2;
  char data[numLines];
  int status;
  char fileInPath[] = {"zp4in.txt"};
  char fileOut1Path[] = {"zp4out1.txt"};
  char fileOut2Path[] = {"zp4out2.txt"};


  numLines = numLinesCmd();



  fileptr = fopen(fileInPath, "a+");
  printf("Enter String: \n");
  scanf(" %[^\n]", data);
  getchar();
  //printf("%s", data);
  //fgets(data, numLines, stdin);
  fprintf(fileptr, "%s", data);
  fclose(fileptr);

  displayFile(fileptr, fileInPath);
  fileAnalysis(fileptr);


  rmSpaceConvLetter(fileptr, numLines, fpOut1);

  lineNumber(fileptr, fpOut2, numLines);

  displayFile(fpOut1, fileOut1Path);
  displayFile(fpOut2, fileOut2Path);

  system("rm *txt");//use system command to remove all txt files


  return 0;
}
/*
Doesnt work
*/
int numLinesCmd(){
  int temp;
  printf("Enter the number of lines: ");
  scanf("%d", &temp);
  return temp;
}

/*
Creates file and writes string to file then closes it.
*/
void displayFile(FILE *fileptr, char *filePath){
  char temp;
  fileptr = fopen(filePath, "a+");
  printf("Content of the %s: \n\n", filePath);
  while ((temp = fgetc(fileptr)) != EOF) {
    printf("%c", temp);
  }
  printf("\n\n");
  fclose(fileptr);
}

/*
Counts words you a little bitch
*/
int countWords(FILE *fileptr){

  char temp;
  int wordCount = 1;//has to be one i have no idea why
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    if(temp == ' ' || temp == '\n'){
      wordCount++;
    }
  }
  //printf("%d\n", wordCount);
  return wordCount;
  fclose(fileptr);

}

int countSmall(FILE *fileptr){

  static char LOWER[] = {"abcdefghijklmnopqrstuvwxyz"};

  char temp;
  int i;
  int smallCount = 0;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    for (i = 0; i < 26; i++){
        if (temp == LOWER[i])
            smallCount++;
    }
  }
  //printf("%d\n", wordCount);
  return smallCount;
  fclose(fileptr);

}

int countCapital(FILE *fileptr){

  static char UPPER[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

  char temp;
  int i;
  int capitalCount = 0;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    for (i = 0; i < 26; i++){
        if (temp == UPPER[i])
            capitalCount++;
    }
  }
  //printf("%d\n", wordCount);
  return capitalCount;
  fclose(fileptr);
}

int countDigits(FILE *fileptr){

  static char DIGITS[] = {"0123456789"};

  char temp;
  int i;
  int digitsCount = 0;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    for (i = 0; i < 26; i++){
        if (temp == DIGITS[i])
            digitsCount++;
    }
  }
  //printf("%d\n", digitsCount);
  return digitsCount;
  fclose(fileptr);
}

int countSpaces(FILE *fileptr){

  char temp;
  int spaceCount = 0;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    if(temp == ' '){
      spaceCount++;
    }
  }
  //printf("%d\n", spaceCount);
  return spaceCount;
  fclose(fileptr);

}

int countSymbol(FILE *fileptr){

  static char SYMBOLS[] = {"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{-}~"};

  char temp;
  int i;
  int symbolCount = 0;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    for (i = 0; i < 26; i++){
        if (temp == SYMBOLS[i])
            symbolCount++;
    }
  }
  //printf("%d\n", symbolCount);
  return symbolCount;
  fclose(fileptr);
}

void fileAnalysis(FILE *fileptr){

  int words = countWords(fileptr),
      cap =  countCapital(fileptr),
      sm = countSmall(fileptr),
      dig = countDigits(fileptr),
      sym = countSymbol(fileptr),
      sp = countSpaces(fileptr);
  printf("File Analysis: \n\n");
  printf("Number of Words:  %d \n", words);
  printf("number of Small:  %d \n", sm);
  printf("Number of Capital:  %d \n", cap);
  printf("Number of Digits:  %d \n", dig);
  printf("Number of Spaces:  %d \n", sp);
  printf("Number of Symbols:  %d \n", sym);
}

void rmSpaceConvLetter(FILE *fileptr, int numLines, FILE *fpOut1) {
  char tempData[numLines];
  char blank[numLines];
  char ch;
  int i = 0, j = 0, len;

  fileptr = fopen("zp4in.txt", "a+");
  fpOut1 = fopen("zp4out1.txt", "a+");

  fgets(tempData, numLines, fileptr);
  len = strlen(tempData);
  while (tempData[i] != '\0') {
    ch = tempData[i];
    if (ch >= 'A' && ch <= 'Z')
        tempData[i] = tempData[i] + 32;
    else if (ch >= 'a' && ch <= 'z')
        tempData[i] = tempData[i] - 32;

    if (tempData[i] != ' ') {
      blank[j++] = tempData[i];
    }
    i++;
  }
  blank[j]='\0';
  fprintf(fpOut1, "%s",blank);

  fclose(fpOut1);
  fclose(fileptr);
}

void lineNumber(FILE *fileptr, FILE *fpOut2, int numLines){

  char tempData[numLines];
  int i, len;
  char ch;

  fileptr = fopen("zp4in.txt", "a+");
  fpOut2 = fopen("zp4out2.txt", "a+");

  fgets(tempData, numLines, fileptr);
  len = strlen(tempData);

  for (i = 0; i < len; i++) {
    ch = tempData[i];
    fprintf(fpOut2, "%d: %c\n", i+1, ch);
  }

  fclose(fpOut2);
  fclose(fileptr);
}
