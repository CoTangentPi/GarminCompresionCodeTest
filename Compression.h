/**
 * Garmin Canada Code Design Test
 *
 * Aurhor Chachi (Shichao) Han
 * Chachi_h@hotmail.com
 * 
 * Compression.h
 *
 * @version 2.2.2
 */
 
#ifndef compression
#define compression


int byte_compress(uint8_t data_ptr[], int data_size);

int byte_decompressRLE(uint8_t data_ptr[], int data_size);

#endif