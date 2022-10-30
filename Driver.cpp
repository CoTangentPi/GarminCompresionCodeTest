/**
 * Garmin Canada Code Design Test
 *
 * Aurhor Chachi (Shichao) Han
 * Chachi_h@hotmail.com
 *
 * Driver.cpp
 * @since 1.0.0
 * 
 * @param 
 * @param 
 * 
 */
 

#include <iostream>
#include <assert.h>
#include"Compression.h"

using namespace std;
 
int main (){
	
	int data_size = 24;
	int* data_ptr = new int[data_size] { 0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64, 
					0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09 };
	
	
	cout<<"the size of data before compress is: "<<data_size<<endl;
	for (int i =0; i<data_size; i++){
		cout<<i<<":\t"<<data_ptr[i]<<endl;
	}
	
	
	int result_size = byte_compress(data_ptr,data_size);
	
	
	cout<<"the size of data after compress is: "<<result_size<<endl;
	for (int i =0; i<result_size; i++){
		cout<<i<<":\t"<<data_ptr[i]<<endl;
	}
	
	
	
	
	
	return 0;
}