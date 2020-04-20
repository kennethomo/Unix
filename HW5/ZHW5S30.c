/*
Name: Kenneth Omo, James Steckler
Serial Number: 23, 30
CS 4350--251-Unix Systems Programming
Assignment Number: 5
Due Date: 4/20/2020
 */

/**
 This Program carefully and strictly follows the provided rubric and accomplishes 33 steps.  Overall, this
 program demonstrates the usage of system commands in C, as well as a how-to-use various provided libraries
 to access system, process, file, permisison, user and other potentially valuable information.  Almost all
 provided code was in part derived from provided slides, with reasonable applicaitons of pre-existing or self
 learned knowledge applied throughout to simplify and or streamline program flow.

 Six functions were used in the support of the mostly procedural program flow and have short descriptions
 where applicable to describe any potentially confusing code bits.  However it is fairly straightforward, and
 should any questions arise do not hesitate to email jes270@txstate.edu or kjo15@txstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>


void getSysName();
void getProcessId();
void getFileInfo();
void renameFile();
void removeFile();
void chmodFile();

int main() {

  FILE *fileptr; // file pointer for file manipulation
  int date; // variable for date
  time_t currTime; // time struct
  // Step 1 SYSTEM COMMAND
  printf("System / File Manipulation Program\n\n");
  printf("1. File is created.\n");
  system("touch zp5in-1.txt");

  struct stat fileStat;  // Struct to access file info
  char filename[]="zp5in-1.txt"; // filename variable
  if(stat(filename,&fileStat)==-1){
    printf("Something went wrong!!\n");
  }
  // Step 2
  printf("2. Text is appended to the file.\n");
  fileptr = fopen("zp5in-1.txt", "a+");
  fprintf(fileptr, "Texas State University, Spring 2020, Unix Programming");
  // Step 3
  printf("3. File is closed.\n");
  fclose(fileptr);
  // Step 4
  time(&currTime);
  printf("4. Current date is : %s",ctime(&currTime));
  // Step 5
  printf("5. Time of last file access  : %s", ctime(&fileStat.st_atime));
  // Step 6
  system("echo 6. The content of the file is  : $(cat zp5in-1.txt)");
  // Step 7
  chmodFile();
  // Step 8 SYSTEM COMMAND
  system("echo 8. File information is : $(ls -l zp5in-1.txt)");
  // Step 9 - 11
  getSysName();
  // Step 12 - 14
  getProcessId();
  // Step 15 - 25
  getFileInfo();
  // Step 26
  fileptr = fopen("zp5in-1.txt", "a+");
  fprintf(fileptr, "\nFinal step");
  printf("26.  New text is appended  zp5in-1.txt  file.\n");
  fclose(fileptr);
  // Step 27 SYSTEM COMMAND
  system("echo 27. '' Redisplaying the content of zp5in-1.txt  file. $(cat zp5in-1.txt)");
  // Step 28
  printf("28.  The time of last access to be zp5in-1.txt file  : %s", ctime(&fileStat.st_atime));
  // Step 29
  renameFile();
  // Step 30 SYSTEM COMMAND
  system("echo 30. '' The content of the new zp5in-2.txt file : $(cat zp5in-2.txt)");
  // Step 31
  printf("31.  The current date and time : %s",ctime(&currTime));
  // Step 32
  removeFile();
  // Step 33 SYSTEM COMMAND
  system("echo 33. '' Displaying the content of zp5in-2.txt  file :\n $(cat zp5in-2.txt)");

  printf("\n\n");

  printf("Implemented by Kenneth Omo and James Steckler\n");
  return 0;
}
/**
 getSysName - This function utilizes code provided in the notes to fulfill 9 - 11 of the rubric by displaying
 the Host, local Host, and System names.  *NOTE* it is likely that host and local host will be the same depending
 on running environment.  Also, could have displayed the IP, but that is technically not the Host. It's the IP.
 */
void getSysName(){
  int uname(struct utsname *name);

  struct utsname uts;
  char hostBuf[256];
  struct hostent *host_entry;
  int hostname;

  hostname = gethostname(hostBuf, sizeof(hostBuf));

  if(hostname == -1){
    perror("gethostname");
  }

  host_entry = gethostbyname(hostBuf);

  if (host_entry == NULL){
      perror("gethostbyname");
  }

  uname(&uts);
  printf("9. System name : %s\n", uts.sysname);
  printf("10.  Local host name : %s\n", hostBuf);
  printf("11.  Host name : %s\n", host_entry->h_name );
  // if (host_entry)
  //     puts(host_entry->h_name);
}
/**
 getProcessId - This function fulfills 12,13,14 of the rubric and displays the process and parent ID, and the
 priority level of the process
 */
void getProcessId(){
  // use existing library to simplify
  pid_t process_id;
  pid_t p_process_id;
  int which = PRIO_PROCESS;
  id_t pid;
  int ret;

  process_id = getpid();
  p_process_id = getppid();
  pid = getpid();
  ret = getpriority(which, pid);
  // display results of the gets()
  printf("12.  The process id : %d\n", process_id);
  printf("13.  Parent process id : %d\n", p_process_id);
  printf("14.  Priority level of the process : %d\n", ret);

}
/**
 getFileInfo - This function fulfills 15-25 of the rubric and displays the filename, device, inode, permissions
 # of hardlinks, Owner ID, Group ID, effective ID, size of blocks, number of blocks.  For the displaying
 of file permissions I used the direct access to each part of the file permission block from fileState struct
 and used the ? wildcard to display which value was true for each position.
 */
void getFileInfo(){

  struct stat fileStat;
  char filename[]="zp5in-1.txt";
  char *str;
  if(stat(filename,&fileStat)==-1){
    printf("Something went wrong!!\n");
  }
    (str = getenv("HOME"));
  printf("15.  The file Name is : %s\n", filename);
  printf("16.  The device is : %s\n", str);
  printf("17.  The inode is  : %llu\n", fileStat.st_ino);
  printf("18.  The file permission : ");
  // The below manually checks each perm slot and displays which is true
  printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n19.  Number of hard links  : %hu\n", fileStat.st_nlink);
  printf("20.  Owner's user ID  : %d\n", fileStat.st_uid);
  printf("21.  Owner's group ID  : %d\n", fileStat.st_gid);
  printf("22.  Owner's effective user ID  : %d\n", (int)geteuid());
  printf("23.  Size of  zp5in-1.txt   file  : %lld\n", fileStat.st_size);
  printf("24.  Block size of zp5in-1.txt   file  : %d\n", fileStat.st_blksize);
  printf("25.  Number of blocks allocated to zp5in-1.txt  file  : %lld\n", fileStat.st_blocks);
}
/**
 renameFile - This function fulfills step 29 of the rubric and changes the name of the file with an error check.
 */
void renameFile(){
  int ret;
  char oldName[] = "zp5in-1.txt";
  char newName[] = "zp5in-2.txt";

  ret = rename(oldName, newName);
  if(ret == 0){
    printf("29.  Renamed the file to be zp5in-2.txt\n");
  }
  else{
    printf("Something went wrong!!!\n");
  }
}
/**
 removeFile - This function deletes the file from the directory, and checks to make sure it's there
 */
void removeFile(){

  int stat;
  char file[] = "zp5in-2.txt";

  stat = remove(file);

  if (stat == 0){
    printf("32.  Removed zp5in-2.txt  files from current Directory.\n");
  }
  else{
    printf("Something  Went Wrong!!!\n");
    perror("ERROR");
  }
}
/**
 chmodFIle - This function fulfills the file perfmission changing requirement of step 7 by using the chmod
 method to correctly change it's modes
 */
void chmodFile(){

  struct stat fileStat;
  char filename[]="zp5in-1.txt";
  if(stat(filename,&fileStat)==-1){
    printf("Something went wrong!!\n");
  }
  chmod(filename, S_IRWXU | S_IRWXG);
  printf("7. File mode is changed\n");

}
