#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_JOB 50

typedef struct {
  pthread_t        thread_tid;
} Thread;

Thread    *tptr;
int current_job=1;
pthread_mutex_t    lock = PTHREAD_MUTEX_INITIALIZER;

static void sleep_ms(unsigned int secs)

{

    struct timeval tval;

    tval.tv_sec=secs/1000;

    tval.tv_usec=(secs*1000)%1000000;

    select(0,NULL,NULL,NULL,&tval);

}

int sm4enc(){
    char *msg="12306";
        int msg_len=strlen(msg);
        unsigned char pk[64]={0};
         unsigned char sec[64]={0};
        int ret=-1;
        int sec_len=0;
        unsigned char iv[8] = { 0 };
        ret=SM4Encrypt((unsigned char*)msg,msg_len,sec,&sec_len);
        if (ret==0){
               printf("sm4 enc success!msg_len:%d sec_len:%d\n",msg_len,sec_len);
               return 0;
        }else{
               printf("sm4 enc failed!ret:%d\n",ret);
               return -1;
        }
}

void* thread_run(void* arg)
{
    int i=0;
    printf("-----\n");
    for ( i = 0; i < 1000; ++i)
    {
        sm4enc();
        sleep_ms(100);
    }
}

int main (int argc ,char *argv[]) {
    int i;
    int threadNum=0;
    initwest();
    if (argc==2)
    {
        threadNum=atoi(argv[1]);
    }else{
       printf("parameter error!\n");
    }


    tptr=(Thread*)malloc(sizeof(Thread)*threadNum);

    for(i=0;i<threadNum;i++)
        pthread_create(&tptr[i].thread_tid, NULL, &thread_run, NULL );

   i=0;
    for(i=0;i<threadNum;i++)
        pthread_join(tptr[i].thread_tid,NULL);

    return 0;
}
                                    