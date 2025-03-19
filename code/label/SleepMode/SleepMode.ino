static void SleepMode(void)
{
  /* Request to enter SLEEP mode */
  __WFI();
}
void setup(){
  SleepMode();
}
void loop(){
  SleepMode();}
