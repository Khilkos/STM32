
// Файл img.h создан с помощью программы конвертатор ConvertBMP
// Массив для вывода изображения на дисплей. Передача цвета RGB 16 бит 5-6-5
// Разрешение изображения 160x128, размер массива 40 Кб
// Адрес изображения E:\Avr\LCD Display\ConvertBMP\picture\160х128.bmp
// Конвертация прямая

#ifndef IMG_H
#define IMG_H
#include "stdint.h"

//uint16_t width  = 160; 	// Ширина изображения
//uint16_t height = 128; 	// Высота изображения

extern	const uint16_t img[]; 
extern const uint16_t img1[];
extern const uint16_t img2[];

#endif /* IMG_H */

	