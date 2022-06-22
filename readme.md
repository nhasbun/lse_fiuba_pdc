# Driver para HDC1000

Este repositorio contiene un driver para la lectura de temperatura y humedad
relativa que se capturan en un sensor **HDC1000**. La comunicación con el sensor
es por bus I2C y se indica una nueva captura disponible por medio de un pin de
interrupción `DRDYn` de lógica negativa disponible en el integrado.

El driver actualmente contiene un port para ser utilizado en los
microcontroladores stm32f4xx, pero posiblemente sea aplicable a la mayoria de
los stm32 sin mayores problemas.

Port a nuevas plataformas es posible modificando el archivo `stm32_port.c`.

## Instrucciones de Uso

1. El recurso del bus i2c debe estar inicializado, configurado y funcionando
   previo al uso del driver.

1. Debe configurarse una interrupción en el flanco de bajada para el pin del
   microcontrolador que va a leer la señal de `DRDYn`. Se agrega un ejemplo para
   la placa de desarrollo **Nucleo F429ZI**.

1. Esta interrupción debe llamar a la función `hdc_on_new_data()` del driver.

1. Indicar el handle relacionado al periférico de comunicación i2c haciendo uso
   de la función `hdc_set_iic_handle()`.

1. Verificar comunicación y hardware correcto con la función
   `hdc_get_manufacturer_id()` y `hdc_get_device_id()`. Deben retornar 0x5449 y
   0x1000 respectivamente.

1. Cargar configuración esperada en el sensor por el driver con la función
   `hdc_set_config()`. Se puede verificar con `hdc_get_config()` y debe retornar
   0x1000.

1. Hacer un llamado constante a la función `hdc_update_data()` (se recomienda un
   mínimo de 20 ms). Esto actualizará las últimas mediciones del driver de
   temperatura y humedad relativa que se acceden mediante `hdc_temperature()` y
   `hdc_humidity()`.

Ejemplo para asociación de interrupción (para STM32):

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_5) hdc_on_new_data();
}
```

## Documentación con Doxygen

Se agrega documentacion con doxygen que puede ser generada con el siguiente comando:

```bash
doxygen Doxyfile
```
