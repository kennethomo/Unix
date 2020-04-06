
/*
Name: Kenneth Omo, James Steckler
Serial Number: 23, 30
CS 4350--251-Unix Systems Programming
Assignment Number: 4
Due Date: 4/6/2020
*/

/**
 This program will accomplish the following tasks, while demonstrating system commands:
    1. Creates a new input file ( zp4in.txt )
    2. Ask the user to input number of lines of input to be inserted in the new file.
    3. From the command line, Accept the lines from the keyboard and save them in created file (
      zp4in.txt)
    4. Reopen the file again.
    5. Display the content of the new created input file.
    6. Count then display the number of Words in the input file.
    7. Count then display the number of Small letters in input file
    8. Count then display the number of Capital letters in the input file
    9. Count then display the number of Digits in the input file
    10. Count then display the number of Spaces in the input file
    11. Count then display the number of Special Symbols letters in the input file.
    12. Copy the content of the input file without any spaces , changing all small letters to capital letters
       and vice versa to a new file ( zp4out1.txt ).
    13. Reads the input file one line at a time, and writes these lines to a second file (zp4out2.txt). Add a
       line number for each line in the new file.
    14. Display the content of the zp4out1.txt , zp4out2.txt .
    15. Remove zp4in.txt , zp4out1.txt , and zp4out2.txt files from your current Directory.
 */


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
  getchar(); // clear buffer
  fprintf(fileptr, "%s", data);
  fclose(fileptr);

  displayFile(fileptr, fileInPath);
  fileAnalysis(fileptr);
    
  rmSpaceConvLetter(fileptr, numLines, fpOut1);

  lineNumber(fileptr, fpOut2, numLines);
  // Display results
  displayFile(fpOut1, fileOut1Path);
  displayFile(fpOut2, fileOut2Path);

  system("rm *txt");//use system command to remove all txt files


  return 0;
}
/**
 numLinesCmd - this int function takes user input to determine the integer # of lines to put in a file
 @return temp - user provided integer
 */
int numLinesCmd(){
  int temp;
  printf("Enter the number of lines: ");
  scanf("%d", &temp);
  return temp;
}

/**
 displayFIle - this void function takes takes path and pointer and displays the contents of the file
 @param *fileptr - pointer to file
 @param *filepath - path to file
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

/**
 countWords - this int function counts the number of words in the provided file ptr
 @param *fileptr - pointer to file to be opened
 @return wordCount - number of words counted
 */
int countWords(FILE *fileptr){

  char temp;
  int wordCount = 1;
  fileptr = fopen("zp4in.txt", "a+");
  while((temp = fgetc(fileptr)) != EOF){
    if(temp == ' ' || temp == '\n'){
      wordCount++;
    }
  }
  return wordCount;
  fclose(fileptr);

}
/**
 countSmall - this int function counts the number of lowercase letters in a file
 @param *fileptr - pointer to file to be opened
 @return smallCount - number of lowercase letters
 */
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
/**
 countCapital - this int function counts the number of lowercase letters in a file
 @param  *fileptr - pointer to file to be opened
 @return capitalCount - number of capital letters
 */
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
  return capitalCount;
  fclose(fileptr);
}
/**
 countDigits - int function that counts # of digits in provided file paramter
 @param *fileptr - pointer to file to be opened
 @return digitsCount - int number of digits in file
 */
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
  return digitsCount;
  fclose(fileptr);
}
/**
 countSpaces - int function that counts # of spaces in provided file paramter
 @param *fileptr - pointer to file to be opened
 @return spaceCount -  int # of spaces in file
 */
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
/**
 countSymbol - int function that counts # of symbols in provided file paramter
 @param *fileptr - pointer to file to be opened
 @return symbolCount - int # of symbols in file
 */
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
  return symbolCount;
  fclose(fileptr);
}
/**
 fileAnalysis - void function that prints statistics and data (# of various letters/digits/symbols,etc)
  @param *fileptr - pointer to file to be opened
 */
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

/**
 rmSpaceConvLetter - this void function takes several parameters that it uses to edit various parts of a file per
                 assignment syllabus
 @param *fileptr - pointer to file to be opened
 @param numlines - # of lines
 @param #fpOut1 - output file of manipulated data
 */
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
/**
 lineNumber - this void function outputs syllabus required data over files
 @param *fileptr -  FILE pointer to file to be opened
 @param *fpOut2 - FILE pointer to secondary file data
 @param numLines - int number of lines for file manipulation
 */
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

/**
 For any questions, please contact Kenneth Omo or James Steckler
 */
