 /*
  2  * Scrieti un program C care creeaza doua procese fiu. Parintele citeste de     la tastatura un string (ce nu contine spatii) si il trimite prin pipe c    atre ambele procese fiu.
  3   7 Unul din procesele fiu extrage primele 5 litere din alfabet (a-e) din st    ring-ul primit, iar celalalt proces fiu extrage ultimele 5 litere din al    fabet (v-z) din string-ul primit.
  4   8 Ambele procese fiu trimit string-urile extrase prin pipe catre parinte.
  5   9 Parintele va afisa string-urile primite de la procesele fiu.
  6   */
  7
  8 #include <stdio.h>
  9 #include <stdlib.h>
 10 #include <unistd.h>
 11 #include <sys/wait.h>
 12 #include <string.h>
 13
 14 int main(int argc, char *argv[]) {
 15     (void) argc;
 16     (void) argv;
 17
 18     int ptc1[2], ptc2[2], c1tp[2], c2tp[2];
 19
 20     if ( pipe(ptc1) == -1 || pipe(ptc2) == -1 || pipe(c1tp) == -1 || pipe(c2tp) == -1 ) {
 21         perror("error creating the pipes");
 22         exit(1);
 23     }
 24
 25     int c1 = fork();
 26
 27     if ( c1 == -1 ) {
 28         perror("error creating the first child");
 29         exit(1);
 30     } else if ( c1 == 0 ) {
 31         //the first child
 32         //writes to parent the new string
 33         //receives from parent the string that must be changed
 34         close(ptc2[0]); close(ptc2[1]);
 35         close(c2tp[0]); close(c2tp[1]);
 36         close(ptc1[1]);
 37         close(c1tp[0]);
 38
 39         int l;
 40         if ( read(ptc1[0], &l, sizeof(int)) < 0 ) {
 41             perror("error on reading the length");
 42             exit(1);
 43         }
 44
 45         char *buf = malloc((l+1) * sizeof(char)); //we must not forget the null
 46         if ( read(ptc1[0], buf, sizeof(char) * l) < 0 ) {
 47             perror("error on reading the string");
 48             exit(1);
 49         }
 50
 51         char *nb = malloc((l+1) * sizeof(char));
 52         memset(nb, 0, (l+1) * sizeof(char));
 53         int l2 = 0;
 54         for ( int i = 0; i < l; ++i ) {
 55             if ( strchr("abcde", buf[i]) ) {
 56                 nb[l2] = buf[i];
 57                 l2++;
 58             }
 59         }
 60
 61         nb[l2] = 0;
 62
 63         //now we send to the parent the length of the new string and the new string
 64         if ( write(c1tp[1], &l2, sizeof(int)) < 0 ) {
 65             perror("error on writing the length");
 66             exit(1);
 67         }
 68
 69         if ( write(c1tp[1], nb, sizeof(char) * l2) < 0 ) {
 70             perror("error on writing the string");
 71             exit(1);
 72         }
 73
 74         //now we close the pipes, free the memory and exit
 75         close(c1tp[1]);
 76         close(ptc1[0]);
 77
 78         free(buf);
 79         free(nb);
 80
 81         exit(0);
 82
 83     }
 84
 85     int c2 = fork();
 86     if ( c2 == -1 ) {
 87         perror("error creating the second child");
 88         exit(1);
 89     } else if ( c2 == 0 ) {
 90         close(ptc1[0]); close(ptc1[1]);
 91         close(c1tp[0]); close(c1tp[1]);
 92         close(ptc2[1]);
 93         close(c2tp[0]);
 94
 95
 96         int l;
 97         if ( read(ptc2[0], &l, sizeof(int)) < 0 ) {
 98             perror("error reading the length");
 99             exit(1);
100         }
101
102         char *buf = malloc((l+1) * sizeof(char));
103         if ( read(ptc2[0], buf, l * sizeof(char)) < 0 ) {
104              perror("error reading the string");
105              exit(1);
106         }
107
108         char *nb = malloc((l+1)*sizeof(char));
109         memset(nb, 0, (l+1) * sizeof(char));
110
111         int l2 = 0;
112         for ( int i = 0; i < l; ++i ) {
113             if ( strchr("vwxyz", buf[i])) {
114                 nb[l2] = buf[i];
115                 l2++;
116             }
117         }
118
119         nb[l2] = 0;
120
121         if ( write(c2tp[1], &l2, sizeof(int)) < 0 ) {
122             perror("error writing the length");
123             exit(1);
124         }
125
126         if ( write(c2tp[1], nb, l2 * sizeof(char)) < 0 ) {
127             perror("error writing the string");
128             exit(1);
129         }
130
131         close(c2tp[1]);
132         close(ptc2[0]);
133
134         free(buf);
135         free(nb);
136         exit(0);
137     }
138
139     //parent
140     //writes to c1
141     //c1 reads from p
142     close(ptc1[0]);
143     close(c1tp[1]);
144     close(ptc2[0]);
145     close(c2tp[1]);
146
147     char *input = malloc(256 * sizeof(char));
148     if (fgets(input, 256, stdin) == NULL ) {
149         perror("error reading from stdin");
150         exit(1);
151     }
152
153     int len = strlen(input);
154
155     if ( write(ptc1[1], &len, sizeof(int)) < 0 )  {
156          perror("error writing the length");
157          exit(1);
158     }
159
160     if ( write(ptc1[1], input, len * sizeof(char)) < 0 ) {
161          perror("error writing the string");
162          exit(1);
163     }
164
165     if ( write(ptc2[1], &len, sizeof(int)) < 0 )  {
166           perror("error writing the length");
167           exit(1);
168     }
169
170     if ( write(ptc2[1], input, len * sizeof(char)) < 0 ) {
171           perror("error writing the string");
172           exit(1);
173     }
174
175     int l1, l2;
176
177     if ( read(c1tp[0], &l1, sizeof(int)) < 0 ) {
178         perror("error reading the length");
179         exit(1);
180     }
181
182     char* buf = malloc((l1+1) * sizeof(char));
183     memset(buf, 0, (l1+1) * sizeof(char));
184     if ( read(c1tp[0], buf, l1 * sizeof(char)) < 0 ) {
185         perror("error reading the string");
186         exit(1);
187     }
188
189     if ( read(c2tp[0], &l2, sizeof(int)) < 0 ) {
190         perror("error reading the length");
191         exit(1);
192     }
193
194     char* buf2 = malloc((l2+1) * sizeof(char));
195     memset(buf2, 0, (l2+1) * sizeof(char));
196     if ( read(c2tp[0], buf2, l2 * sizeof(char)) < 0 ) {
197          perror("error reading the string");
198          exit(1);
199     }
200
201     printf("the string made only by a-e: %s\n", buf);
202     printf("the string made only by v-z: %s\n", buf2);
203
204     free(input);
205     free(buf);
206     free(buf2);
207     close(ptc1[1]);
208     close(ptc2[1]);
209     close(c1tp[0]);
210     close(c2tp[0]);
211
212     wait(0);
213     wait(0);
214
215     return 0;
216 }
~   
