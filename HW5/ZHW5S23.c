/*
Name: Kenneth Omo, James Steckler
Serial Number: 23, 30
CS 4350--251-Unix Systems Programming
Assignment Number: 5
Due Date: 4/20/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/stat.h>

void getSysName();
void getProcessId();
void getFileInfo();
void renameFile();
void removeFile();

int main() {

  FILE *fileptr;
  int date;
  time_t currTime;



  printf("System / File Manipulation Program\n\n");
  printf("1. File is created.\n");
  system("touch zp5in-1.txt");

  struct stat fileStat;
  char filename[]="zp5in-1.txt";
  if(stat(filename,&fileStat)==-1){
    printf("Something went wrong!!\n");
  }

  printf("2. Text is appended to the file.\n");
  fileptr = fopen("zp5in-1.txt", "a+");
  fprintf(fileptr, "Texas State University, Spring 2020, Unix Programming");

  printf("3. File is closed.\n");
  fclose(fileptr);

  time(&currTime);
  printf("4. Current date is : %s",ctime(&currTime));

  printf("5. Time of last file access  : %s", ctime(&fileStat.st_atime));



  system("echo 6. The content of the file is  : $(cat zp5in-1.txt)");

  system("echo 7. File mode changed $(chmod 770 zp5in-1.txt)");//change

  system("echo 8. File information is : $(ls -l zp5in-1.txt)");

  getSysName();
  getProcessId();
  getFileInfo();

  fileptr = fopen("zp5in-1.txt", "a+");
  fprintf(fileptr, "Final step");

  printf("26.  New text is appended  zp5in-1.txt  file.\n");
  fclose(fileptr);

  system("echo 27. '' Redisplaying the content of zp5in-1.txt  file. $(cat zp5in-1.txt)");
  printf("28.  The time of last access to be zp5in-1.txt file  : %s", ctime(&fileStat.st_atime));

  renameFile();

  system("echo 30. '' The content of the new zp5in-2.txt file : $(cat zp5in-2.txt)");
  printf("31.  The current date and time : %s",ctime(&currTime));

  removeFile();

  system("echo 33. '' Displaying the content of zp5in-2.txt  file :\n $(cat zp5in-2.txt)");

  printf("\n\n");



  printf("Implemented by Kenneth Omo and James Steckler\n");
  return 0;
}

void getSysName(){
  int uname(struct utsname *name);

  struct utsname uts;
  char hostBuf[256];
  int hostname;

  hostname = gethostname(hostBuf, sizeof(hostBuf));

  if(hostname == -1){
    perror("gethostname");
  }

  uname(&uts);
  printf("9. System name : %s\n", uts.sysname);
  printf("10.  Local host name : %s\n", hostBuf);
}

void getProcessId(){
  pid_t process_id;
  pid_t p_process_id;
  int which = PRIO_PROCESS;
  id_t pid;
  int ret;

  process_id = getpid();
  p_process_id = getppid();
  pid = getpid();
  ret = getpriority(which, pid);

  printf("12.  The process id : %d\n", process_id);
  printf("13.  Parent process id : %d\n", p_process_id);
  printf("14.  Priority level of the process : %d\n", ret);

}

void getFileInfo(){

  struct stat fileStat;
  char filename[]="zp5in-1.txt";
  if(stat(filename,&fileStat)==-1){
    printf("Something went wrong!!\n");
  }

  printf("17.  The inode is  : %ld\n", fileStat.st_ino);
  printf("19.  Number of hard links  : %ld\n", fileStat.st_nlink);
  printf("20.  Owner's user ID  : %d\n", fileStat.st_uid);
  printf("21.  Owner's group ID  : %d\n", fileStat.st_gid);
  printf("22.  Owner's effective user ID  :\n");                                 //Missing
  printf("23.  Size of  zp5in-1.txt   file  : %ld\n", fileStat.st_size);
  printf("24.  Block size of zp5in-1.txt   file  : %ld\n", fileStat.st_blocks);
  printf("25.  Number of blocks allocated to zp5in-1.txt  file  : %ld\n", fileStat.st_blocks);//Missing

}

void renameFile(){
  int ret;
  char oldName[] = "zp5in-1.txt";
  char newName[] = "zp5in-2.txt";

  ret = rename(oldName, newName);
  if(ret == 0){
    printf("29.  Renamed the file to be zp5in-2.txt .\n");
  }
  else{
    printf("Something went wrong!!!\n");
  }
}

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
