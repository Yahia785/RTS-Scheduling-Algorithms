#include "scheduler.h"

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;
TaskHandle_t xHandle5 = NULL;
// the loop function runs over and over again forever
void loop() {}


static void testFunc1( void *pvParameters )
{
	(void) pvParameters;
	volatile int i,a;
	for( i = 0; i < 160; i++ )
	{
		a = 1 + i*i*i*i;
	}	

}

static void testFunc2( void *pvParameters )
{ 
	(void) pvParameters;	
	volatile int i, a;	
  for(i = 0; i < 400; i++ )
	{
    for(int j=0; j < 100; j++)
    {
      a = 1 + a * a * i;
    }
		
  }	
}


int main( void )
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
	char c1 = 'a';
	char c2 = 'b';	
	char c3 = 'c';
	char c4 = 'd';
  char c5 = 'e';				

	vSchedulerInit();
	// Last 3 parameters T - C - D


  // //CASE1 START: Periodic task set where D<T (where EDF would fail, RM/DM would pass)
  // vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 0, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(100), pdMS_TO_TICKS(20), pdMS_TO_TICKS(80));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t3", configMINIMAL_STACK_SIZE, &c3, 0, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(150), pdMS_TO_TICKS(30), pdMS_TO_TICKS(120));  
  // //CASE1 END


  //CASE2 START: Periodic task set where D=T (where all algorithms would pass)
  vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 0, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(1000), pdMS_TO_TICKS(200), pdMS_TO_TICKS(1000));
  vSchedulerPeriodicTaskCreate(testFunc2, "t3", configMINIMAL_STACK_SIZE, &c3, 0, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(1500), pdMS_TO_TICKS(300), pdMS_TO_TICKS(1500)); 
  //edf 
  //CASE2 END


  // //CASE3 START: Overloaded periodic task set where D=T (where all algorithms would fail)
  // vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 0, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(100), pdMS_TO_TICKS(150), pdMS_TO_TICKS(100));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t3", configMINIMAL_STACK_SIZE, &c3, 0, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(120), pdMS_TO_TICKS(170), pdMS_TO_TICKS(120));  
  // //rm and dm 
  // //CASE3 END


  //CASE4 START: Periodic task set where D>T (where EDF would outperform RM and DM)
  // vSchedulerPeriodicTaskCreate(testFunc2, "t1", configMINIMAL_STACK_SIZE, &c1, 0, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(1000), pdMS_TO_TICKS(500), pdMS_TO_TICKS(1200));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 0, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(1500), pdMS_TO_TICKS(700), pdMS_TO_TICKS(1700));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t3", configMINIMAL_STACK_SIZE, &c3, 0, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(2000), pdMS_TO_TICKS(400), pdMS_TO_TICKS(2700));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t4", configMINIMAL_STACK_SIZE, &c4, 0, &xHandle4, pdMS_TO_TICKS(0), pdMS_TO_TICKS(2500), pdMS_TO_TICKS(300), pdMS_TO_TICKS(3200));
  // //CASE4 END

  //vSchedulerPeriodicTaskCreate(testFunc2, "t1", configMINIMAL_STACK_SIZE, &c1, 0, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(70), pdMS_TO_TICKS(28), pdMS_TO_TICKS(70));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 0, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(900), pdMS_TO_TICKS(400), pdMS_TO_TICKS(850));
  // vSchedulerPeriodicTaskCreate(testFunc2, "t3", configMINIMAL_STACK_SIZE, &c3, 0, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(1000), pdMS_TO_TICKS(400), pdMS_TO_TICKS(1050));  
  // vSchedulerPeriodicTaskCreate(testFunc2, "t4", configMINIMAL_STACK_SIZE, &c4, 0, &xHandle4, pdMS_TO_TICKS(0), pdMS_TO_TICKS(800), pdMS_TO_TICKS(400), pdMS_TO_TICKS(950));
  //vSchedulerPeriodicTaskCreate(testFunc2, "t5", configMINIMAL_STACK_SIZE, &c5, 0, &xHandle5, pdMS_TO_TICKS(0), pdMS_TO_TICKS(100), pdMS_TO_TICKS(120), pdMS_TO_TICKS(100));

  vSchedulerStart();
	/* If all is well, the scheduler will now be running, and the following line
	will never be reached. */
	
	for( ;; );
}