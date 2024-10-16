
#include <timer.h>

#define TIM2_CLK	(1U<<0)
#define TIM2_EN		(1U<<0)
#define OC_TOGGLE	(1U<<4) | (1U<<5)
#define CCER_CC1E	(1U<<0)

#define GPIOAEN		(1U<<0)
#define AFR5_TIM	(1U<<20)

void timer2_pa5_output_compare(void){

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//Set PA5 to alternate function mode
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |=  (1U<<11);

	//Set alternate function to TIM2_CH1 (AF0)
	GPIOA->AFR[0] |= AFR5_TIM;

	//Enable clock access to timer2
	RCC->APB1ENR |= TIM2_EN;

	//Set pre-scaler value
	TIM2->PSC = 1600 - 1;

	//Set auto-reload value
	TIM2->ARR = 10000 - 1;

	//Set output compare toggle mode
	TIM2->CCMR1 |= OC_TOGGLE ;

	//Enable TIM2 CH1 in compare mode
	TIM2->CCER |= CCER_CC1E;

	//Clear counter
	TIM2->CNT = 0;

	//Enable counter
	TIM2->CR1 |= TIM2_EN;
}
