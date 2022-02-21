/*
 * usb_file.c
 *
 *  Created on: 01.12.2020
 *      Author: Patrick
 */

#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "fatfs.h"
#include "usb_data.h"

FIL file;

char filename[20] = {0};
uint8_t usb_file_exists = 1;
uint32_t file_seek = 0;

char first_line[][8] =
{
	"ADC1_01;", "ADC1_02;", "ADC1_03;", "ADC1_04;", "ADC1_05;",
	"ADC1_06;", "ADC1_07;", "ADC1_08;", "ADC1_09;", "ADC1_10;",
	"ADC1_11;", "ADC1_12;", "ADC1_13;",
};


uint8_t usb_mount(void)
{
	FRESULT f_res = f_mount(&USBHFatFS, USBHPath, 0);

	if(f_res != FR_OK)
		return 1;

	return 0;
}

uint8_t usb_unmount(void)
{
	if(f_mount(NULL, USBHPath, 0) != FR_OK)
		return 1;

	return 0;
}

uint8_t usb_file_exists_get(void)
{
	return usb_file_exists;
}

void usb_file_exists_reset(void)
{
	usb_file_exists = 1;
}

char* usb_file_get_filename(void)
{
	return filename;
}

static uint8_t usb_file_get_name(char* filename)
{
	FRESULT f_res = FR_OK;
	FILINFO fno[10];

	uint8_t file_counter = 0;

	do
	{
		char tmp[2];

		if(file_counter >= 10)
			return 1;

		strcpy(filename, "voltage");
		sprintf(tmp, "%u", file_counter);
		strcat(filename, tmp);
		strcat(filename, ".csv");

		f_res = f_stat(filename, &fno[file_counter]);

		file_counter++;

	} while(f_res != FR_NO_FILE);

	return 0;
}

uint8_t usb_file_create(void)
{
	FRESULT f_res;

	usb_file_get_name(filename);

	f_res = f_open(&file, filename, FA_WRITE | FA_CREATE_ALWAYS);
	if(f_res != FR_OK)
	{
		return f_res;
	}

	uint32_t bw = 0;
	char str[200] = {0};

	strcat(str, "time;");
	strncat(str, &first_line[0][0], sizeof(first_line));
	strcat(str, "\n");

	file_seek = strlen(str);
	f_res = f_write(&file, str, file_seek, (unsigned int*)&bw);

	f_close(&file);
	usb_file_exists = 0;
	return 0;
}

uint8_t usb_file_write_data(void)
{
	FRESULT f_res;

	f_res = f_open(&file, filename, FA_WRITE);
	if(f_res != FR_OK)
	{
		return f_res;
	}

	f_lseek(&file, file_seek);

	while(1)
	{
		uint32_t bw = 0;
		char str[2000] = {0};

		size_t count = usb_data_get_data(str, 10);
		debug_set_usb_max_bytecount(count);
		if(count == 0)
			break;

		file_seek += count;
		f_res = f_write(&file, str, count, (unsigned int*)&bw);

		if(f_res != FR_OK)
			break;
	}

	f_close(&file);

	return f_res;
}
