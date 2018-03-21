#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <signal.h>

#define MILLION 1000000
#define THOUSAND 1000

int main(void)
{
 timer_t time_ID;
 struct itimerspec value;
 struct itimerspec ovalue;
 long timedif;

 if (timer_create(CLOCK_REALTIME, NULL, &time_ID) < 0) { 
   perror(" Could not creat a timer based on CLOCK_REALTIMER");
   return(1);}

 value.it_interval.tv_sec= 0;
 value.it_interval.tv_nsec= 0;
 value.it_value.tv_sec= MILLION;
 value.it_value.tv_nsec= 0;
 timer_settime(time_ID,0,&value, NULL);
 timer_gettime(time_ID,&ovalue);
 printf("You can time it");
 fflush(stdout);
 /* function_to_time(); */
 timer_gettime(time_ID, &value);
 //timedif = MILLION*(ovalue.it_value.tv_sec value.it_value.tv_sec)
 //  + (ovalue.it_value.tv_nsec - value.it_value.tv_nsec)/THOUSAND;
 // printf("It took %ld microseconds \n",timedif);
return(1);
}


