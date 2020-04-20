#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Name: James Steckler, Kenneth Omo          CS 4350 - Unix Systems Programming
 * Serial Number:
 * Group Number:
 * Assignment Number: 3
 * Due Date: 3 / 4 / 2020
 */
// I'm fighting scanf inputs for menu, trying to figure out how to
// clear input buffers and other stuff.
// should probably change some variable names too, this is like 3 programs
// smashed together, only 1 and half of which were mine.
// Basically scanf is shit and because of that, haven't been able to do much
// testing with it.

void newLine(int); // print new line
void menu(char *); // option menu
int strCompare(char *, char *); // string comparison
int getKey(); // get key (for cipher)
void getCipher(int); // determine cipher
void getMsg(char *); // get message
int msgUpper(char *); // upper char in message
int msgLower(char *); // lower char in message
int msgDigits(char *); // digit char in message
int msgSymbols(char *); // symbol char in message
int msgSpaces(char *); // space char in message
void convLetter(char *); // convert letter char
int msgAnalysis(char *); // message analysis
void cloneStr(char *, char []); // clone string
<<<<<<< HEAD
void concat(char*, char*, char [], int); // concatenate string
=======
void concat(char *, char [], char [], int); // concatenate string
>>>>>>> 7af8e47486d0c5ea02eafe159d0ba1304b8cabfb
void encryption(char *, int); // encrypt message
void decryption(char *, int); // decrypt message
// Hardcoded
char glyphs[2][94] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"};
// Makes comparing for counting easy
static char UPPER[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
            LOWER[] = {"abcdefghijklmnopqrstuvwxyz"},
            DIGITS[] = {"0123456789"},
            SYMBOLS[] = {"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{-}~"};
            //SPACES[] = {' '};
// Some fancy menu variables
static char *ENCRYPT = "encrypt\0", *DECRYPT = "decrypt\0", *EXIT = "exit\0";
// Max string length for decrypting
static int STR_LEN = 100;

// I used goto's because I'm a madman that lives on the edge, and found some
// weird help and this is the result

int main(void){
    printf("Welcome to cryptography.");
    newLine(2);

    char selection[STR_LEN], // array to store menu choice
         message[STR_LEN]; // array to store user message
    int encrypt, decrypt, exit, cipherKey;

menuSelection:
    menu(selection);
    goto DoWhileTest;

beginDW:
    if (encrypt == 1) goto nCrypt;
    if (decrypt == 1) goto dCrypt;
    if (encrypt != 1 && decrypt != 1) goto invalidMsg;

    nCrypt:
        newLine( 2 );

        getMsg(message);
        printf("You entered %s\n", message);
        // It basically fails taking input here, I did something once where
        // I got it to run, but I can't reproduce it
        cipherKey = getKey();
        printf("you enetered %d\n", cipherKey);

        if (cipherKey > 93 || cipherKey < 1) goto invalidKey;

        encryption(message, cipherKey);
        goto endDW;

    dCrypt:
        newLine( 2 );

        cipherKey = getKey();
        if (cipherKey > 93 || cipherKey < 1) goto invalidKey;
        // It also fucks up the same way here
        getchar();
        getMsg(message);

        decryption(message, cipherKey);
        goto endDW;

    invalidMsg:
        printf("Invalid message");
        newLine(3);

        goto endDW;

    invalidKey:
        newLine(2);
        printf( "Invalid Key Number" );
        newLine(3);

endDW: goto menuSelection;

DoWhileTest:
    exit = strCompare(selection, EXIT);
    encrypt = strCompare(selection, ENCRYPT);
    decrypt = strCompare(selection, DECRYPT);
    if(exit != 1) goto beginDW;

    newLine(2);
    printf("James Steckler and Kenneth Omo Security Systems \n"
            "3 - 4 - 2020 \n");

    return 0;
}

/***
 * Provides the user with all menu options
 * @param options - the character array that stores the user's menu option
 */
void menu(char  *option){
    printf("What would you like to do to a message? (encrypt, decrypt, exit) \n"
            "Enter your choice:   ");
    scanf("%s", option);
    getchar();

}

/***
 * Prints a new line to the console
 * @param n  - the number of lines to skip
 */
void newLine(int n){
    if (n > 0) {
        printf("\n");
        newLine(n - 1);
    }
}

/***
 * Determines if two strings are the same or not
 * @param input - string entered by the user
 * @param menu - option available to the user
 * @return 1 or 0 (true or false, respectively)
 */
int strCompare(char *str1, char *str2){
    while (*str1 == *str2){
        if (*str1 == '\0' || *str2 == '\0')
            break;
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0')
        return 1;
    else
        return 0;
}

/***
 * Asks user for the message to be encrypted/decrypted
 * @param message - text to be encrypted/decrypted
 */
void getMsg(char *message){
    //char temp;
    printf("Enter your message \n");
    //scanf("%c",&temp);
    scanf("%[^\n]", message);
    getchar();
}

/***
 * Receives an integer value between 1 and 93 (inclusive)
 * Integer is going to be used as a cipher key
 * @return cipherKey - the integer to be used the key
 */
int getKey(){
    int cipherKey;
    //char temp;
    printf("Enter the key number (1 - 93) \n"); // get cipher from user
    //scanf("%c",&temp);
    scanf("%d", &cipherKey);
    //getchar();
    return cipherKey;
}

/***
 *
 */
void getCipher(int key){
    for (int i = 0; i < 94; i++){
        glyphs[1][key] = glyphs[0][i];
        key++;

        if (key > 93)
            key = 0;
    }
    printf("Inside getCipher and leaving\n");
}

/***
 * Analyses message to determine the number of upper case characters
 * @param message - string that is being analysed
 * @return upper - the number of upper case alphabet letters
 */
int msgUpper(char *message){
    int upper = 0;

    while (*message != '\0'){
        for (int i = 0; i < 26; i++){
            if (*message == UPPER[i])
                upper++;
        }
        message++;
    }
    return upper;
}

/***
 * Analyses message to determine the number of lower case characters
 * @param message - string that is being analysed
 * @return lower - the number of lower case alphabet letters
 */
int msgLower(char *message){
    int lower = 0;

    while (*message != '\0'){
        for (int i = 0; i < 26; i++){
            if (*message == LOWER[i])
                lower++;
        }
        message++;
    }
    return lower;
}

/***
 * Analyses message to determine the number of digits
 * @param message - string that is being analysed
 * @return digits - the number of characters that are digits
 */
int msgDigits(char *message){
    int digits = 0;

    while (*message != '\0'){
        for (int i = 0; i < 10; i++){ // digits
            if (*message == DIGITS[i])
                digits++;
        }
        message++;
    }
    return digits;
}

/**
 * Analyses message to determine the number of symbols
 * @param message - string that is being analysed
 * @return symbols - the number of characters that are symbols
 */
int msgSymbols(char *message){
    int symbols = 0,
        i;

    while (*message != '\0'){
        for ( i = 0; i < 32; i++){
            if (*message == SYMBOLS[i])
                symbols++;
        }
        message++;
    }
    return symbols;
}
/***
* Analyses message to determine the number of whitespace
* @param message - string that is being analysed
* @return spaces- the number of characters that are spaces
*/
int msgSpaces(char *message){
    int spaces = 0,
        i;
    for ( i =0; message[i]!= '\0'; i++) {
    //while (*message != '\0'){
        //for (i = 0; i < 1; i++){
        if (message[i] == 32)
            spaces++;
    }
        //spaces++;
    
    return spaces;
}

/***
 * First copies original message into new character
 * Then converts characters in message to upper to lower, and vice-versa
 * @param message - the string that is going to be modified
 * @param conversion - the variable to store the new, modified string
 */
void convLetter(char *message){
    int i;
    while (*message != '\0'){
        for (i = 0; i < 26; i++){
            if (*message == UPPER[i])
                *message = LOWER[i];
            else if (*message == LOWER[i])
                *message = UPPER[i];
        }
        message++;
    }
}

/***
 * Analyses the message to be encrypted/decrypted
 * Performs the following operations:
 *   - Count the number of upper case letters
 *   - Count the number of lower case letters
 *   - Count the number of digit characters
 *   - Count the number of symbol characters
 * Then displays analysis to the console
 * @param message - the string to be analyzed
 * @return total - the total number of characters
 */
int msgAnalysis(char *message){
    int upper = msgUpper(message),
        lower = msgLower(message),
        digits = msgDigits(message),
        symbols = msgSymbols(message),
        spaces = msgSpaces(message),
        total = upper + lower + digits + symbols + spaces;
    printf("Number of Upper:  %d \n", upper);
    printf("number of Lower:  %d \n", lower);
    printf("Number of Digits:  %d \n", digits);
    printf("Number of Symbols:  %d \n", symbols);
    printf("Number of Spaces:  %d \n", spaces);
    printf("Number of Characters in the message:  %d \n", total);

    char newMsg[STR_LEN];
    cloneStr(message, newMsg);
    convLetter(newMsg);
    printf("Converting Letters:  %s \n", newMsg);

    newLine(1);
    return total;
}

/***
 * Clones a string into a new string variable
 * @param message - the original string that is going to be cloned
 * @param clone - the copy of the original string to be modified later
*/
void cloneStr(char *message, char clone[]){
    int index = 0;
    while (*message != '\0'){
        clone[index] = *message;
        message++;
        index++;
    }
    clone[index] = '\0';
}

<<<<<<< HEAD
void concat(char *str1, char *str2, char *newStr, int size){

    int index1 = 0, index2 = 0;
    while(index1 < size) {
        *newStr = *str1;
        index1++;
        str1++;
        newStr++;
    }
    printf("in between while loops, message is %s", str1);
    while(index2 < size) {
        *newStr = *str2;
=======
void concat(char *message, char str2[], char newStr[], int size){

    printf("inconat\n");
    int i, j =0;
    for(i=strlen(message);str2[j]!='\0';i++){
      message[i]=str2[j];
      j++;
    }
    message[i] = '\0';
    /*
    int index1, index2;

    index1 = 0;
    while(str1[index1] != '\0') {
        index1++;
    }
    index2 = 0;
    while(str2[index2] != '\0') {
        str1[index1] = str2[index2];
>>>>>>> 7af8e47486d0c5ea02eafe159d0ba1304b8cabfb
        index1++;
        index2++;
        str2++;
        newStr++;
    }
    str1[index1] = '\0';
    */
}

/***
 * Determines the encryption cipher and analyses the message
 * Encrypts the message
 * @param message - string to be encrypted
 * @param key - integer to generate encryption cipher
 */
void encryption(char *message, int key){
<<<<<<< HEAD
    getCipher(94-key);
=======
    printf("Here is the message   %s\n", message );
    getCipher(key);
>>>>>>> 7af8e47486d0c5ea02eafe159d0ba1304b8cabfb
    int totalChar = msgAnalysis(message);
    char encrypted[STR_LEN];
    char cloner [STR_LEN];
    int index = 0;
    
    cloneStr(message,cloner); // ensure a fresh copy to concat
    
    while (*message != '\0'){
        for (int i = 0; i < 94; i++){
            if (*message == glyphs[0][i])
                encrypted[index] = glyphs[1][i];
            if (*message == 32)
                encrypted[index] = 32;
        }
        index++;
        message++;
    }
    printf("Here is the message   %s\n", message );
    encrypted[index] = '\0';
    printf("The Encrypted text is: \n");
    printf("%s", encrypted);
    newLine(2);

<<<<<<< HEAD
    char concatenation[STR_LEN];
    concat(cloner, encrypted, concatenation, totalChar);
    concatenation[totalChar * 2] = '\0';
=======
    //char concatenation[totalChar * 2];
    concat(&message, encrypted, concatenation, totalChar);
    //concatenation[totalChar * 2] = '\0';


>>>>>>> 7af8e47486d0c5ea02eafe159d0ba1304b8cabfb

    printf("Concatenation of original and decrypted text:  %s", message);
    newLine(3);
}

/***
 * Determines the decryption cipher and analyses the message
 * Encrypts the message
 * @param message - string to be decrypted
 * @param key - integer to generate decryption cipher
 */
void decryption(char *message, int key){
    getCipher(key);
    int totalChar = msgAnalysis(message);
    char decrypted[STR_LEN];
    char cloner [STR_LEN];
    int index = 0,
        i;
    cloneStr(message,cloner);
    while (*message != '\0'){
        for (i = 0; i < 94; i++){
            if (*message == glyphs[0][i])
                decrypted[index] = glyphs[1][i];
            if (*message == ' ')
                decrypted[index] = ' ';
        }
        index++;
        message++;
    }
    decrypted[index] = '\0';
    printf("The Decrypted text is: \n");
    printf("%s", decrypted);
    newLine(2);

    char concatenation[STR_LEN];
    concat(cloner, decrypted, concatenation, totalChar);
    concatenation[totalChar * 2] = '\0';

    printf("Concatenation of original and encrypted text:  %s", concatenation);
    newLine(3);
}
