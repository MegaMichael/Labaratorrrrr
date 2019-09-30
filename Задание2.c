// Подключение библиотек
#include "xtimer.h"
#include "timex.h"
#include "periph/gpio.h"

 xtimer_ticks32_t i,j; 
 uint32_t a,b;



// Обработчик прерывания по нажатию кнопки
void btn_handler(void *arg)
{
  // Прием аргументов, передаваемых из главного потока.
  (void)arg;
  //i = xtimer_now32();
  // Переключение состояния пина PC8
  //gpio_toggle(GPIO_PIN(PORT_C, 8));

  j = xtimer_now();

  a=xtimer_usec_from_ticks (j);
  //b=xtimer_usec_from_ticks (j);

if(a-b > 100000){
	gpio_toggle(GPIO_PIN(PORT_C, 8));
i = xtimer_now();
b=xtimer_usec_from_ticks(i);
}




}

int main(void)
{
 
  // Инициализация пина PA0, к которому подключена кнопка, как источника прерывания.
  // GPIO_RISING - прерывание срабатывает по фронту
  // btn_handler - имя функции обработчика прерывания
  // NULL - ничего не передаем в аргументах

     gpio_init_int(GPIO_PIN(PORT_A, 0), GPIO_IN, GPIO_BOTH, btn_handler, NULL);
	
  // Инициализация пина PC8 на выход
	 gpio_init(GPIO_PIN(PORT_C, 8), GPIO_OUT);
	



 // while(1){}

  return 0;
}

/*
Задание 1. Подавите дребезг контакта кнопки. Для этого запомните время, когда вызвалось прерывание, 
            и при последующем вызове, если не прошло 100 мс, не переключайте светодиод.
Задание 2. Сделайте так, чтобы при удержании кнопки светодиод светился, а при отпускании - гас. 
            В этом случае нужно заставить прерывание срабатывать и на фронт, и на спад. 
            Это задается при инициализации прерывания макросом GPIO_BOTH. 
            Обработчик прерывания должен узнать, его вызвал фронт или спад.
            Для этого можно прочитать значение пина с кнопкой функцией gpio_read. 
            Если прочитали высокое состояние - то это был фронт, если низкое - это был спад.   
*/
