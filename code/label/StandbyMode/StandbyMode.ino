

#define RCC_APB1Periph_PWR               ((uint32_t)0x10000000)
//void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) BDCR_RTCEN_BB = (uint32_t)NewState;
}


void PWR_BackupAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}


void PWR_ClearFlag(uint32_t PWR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));
  
#if defined (STM32F427_437xx) || defined (STM32F429_439xx)
  if (PWR_FLAG != PWR_FLAG_UDRDY)
  {
    PWR->CR |=  PWR_FLAG << 2;
  }
  else
  {
    PWR->CSR |= PWR_FLAG_UDRDY;
  }
#endif /* STM32F427_437xx ||  STM32F429_439xx */

#if defined (STM32F40_41xxx) || defined (STM32F401xx) 
  PWR->CR |=  PWR_FLAG << 2;
#endif /* STM32F40_41xxx */
}
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}
void RTC_ClearFlag(uint32_t RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

  /* Clear the Flags in the RTC_ISR register */
  RTC->ISR = (uint32_t)((uint32_t)(~((RTC_FLAG | RTC_ISR_INIT)& 0x0000FFFF) | (uint32_t)(RTC->ISR & RTC_ISR_INIT)));  
}
void PWR_WakeUpPinCmd(FunctionalState NewState)
{
  /* Check the parameters */  
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}

void PWR_EnterSTANDBYMode(void)
{
  /* Clear Wakeup flag */
  PWR->CR |= PWR_CR_CWUF;
  
  /* Select STANDBY mode */
  PWR->CR |= PWR_CR_PDDS;
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
  
/* This option is used to ensure that store operations are completed */
#if defined ( __CC_ARM   )
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

void StandbyMode(void)
{
  /* Enable PWR APB1 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Clear standby flag */
  PWR_ClearFlag(PWR_FLAG_SB);
  
  /* Disable of RTC wakeup source */
  PWR_BackupAccessCmd(ENABLE);  
  RCC_RTCCLKCmd(DISABLE); 
  
  /* Clear RTC Wakeup flag */ 
  RTC_ClearFlag(RTC_FLAG_WUTF);
  
  /* Clear Wakeup flag */ 
  PWR_ClearFlag(PWR_FLAG_WU);
  
  /* Enable WKUP pin */
  PWR_WakeUpPinCmd(ENABLE);

  /* Request to enter STANDBY mode (Wake Up flag is cleared in 
     PWR_EnterSTANDBYMode function) */
   PWR_EnterSTANDBYMode();
}

void setup (){
    StandbyMode();
}
void loop ()
{
 StandbyMode();
}
