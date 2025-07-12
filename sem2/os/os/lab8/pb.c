 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <unistd.h>
  4 #include <fcntl.h>
  5 #include <sys/wait.h>
  6
  7 int main(int argc, char *argv[]) {
  8     int w_fifo = open("./fifo1", O_WRONLY);
  9     int r_fifo = open("./fifo2", O_RDONLY);
 10     int guessed_nr = 500;
 11     int sol;
 12
 13     while ( 1 ) {
 14             write(w_fifo, &guessed_nr, sizeof(int));
 15             read(r_fifo, &sol, sizeof(int));
 16
 17             if ( sol == 0 ) {
 18                 printf("you guessed the right number %d", guessed_    nr);
 19                 break;
 20
 21             } else if ( sol < 0 )
 22                 guessed_nr++;
 23             else guessed_nr--;
 24     }
 25
 26     close(w_fifo);
 27     close(r_fifo);
 28
 29     return 0;
 30 }
 31
