
      #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
       #include <stdio.h>
       
       int main(){
       char x[5]="ABCD";
       int i;
       for(i=0;i<4;i++){
       printf("x[%d] = %c = %p\n",i,x[i],x[i]);
       }       

       i=0;
       printf("\n\n*((int *)(x+%d)) = %d = %p\n",i,*((int *)(x+i)),*((int *)(x+i)));
     
       
       }
