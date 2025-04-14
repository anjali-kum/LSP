
      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       
       int main(){
       char x[10]=        {1,1,1,1,1,1,1,1,1,1};
       int i;
       for(i=0;i<10;i++){
       printf("x[%d] = %d = %p\n",i,x[i],x[i]);
       }       

       for(i=0;i<100000;i++){
       printf("\n\nx[%d] = %d = %p\n",i,*((int *)(x+i)),*((int *)(x+i)));
      }
       
       }
