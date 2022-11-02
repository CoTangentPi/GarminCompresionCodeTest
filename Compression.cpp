/**
 * Garmin Canada Code Design Test
 *
 * Aurhor Chachi (Shichao) Han
 * Chachi_h@hotmail.com
 * 
 * Compression.cpp
 * @version 2.2.2
 *
 */
 
#include <vector>
#include <iostream>
using namespace std;

/**
 * Data compression algorithm
 *
 * @param pointer to the data buffer
 * @param size of data
 * @return size of data after compression 
 *
 */
int byte_compress(uint8_t data_ptr[], int data_size){
	
	//encoding array and position counter, save draft encode, 
	//and apply to data poniter at the end
	int encoding[data_size];					
	int pos = 0;
	
	//loop to check and go through the given data pointer 
	for(int i = 0; i<data_size;i++){
		
		int counter = 1;
		
		//if it is not the end of data array and 
		//current data in the array is same as the next data,
		//increase the counter and trverse 
		while ( (data_ptr[i] == data_ptr[i+1]) && i<data_size-1 ){
			counter++;
			i++;
		}
		
		//save the current encoding data in to the temporary array 
		encoding[pos++] = counter;
		encoding[pos++] = data_ptr[i];
	}
	
	//We will detact if there is any data in series longer than 15
	bool shortSeriesArray = true;
	
	for(int i = 0; i < pos; i+=2){
		if(encoding[i] > 15){
			shortSeriesArray = false;
			break;
		}
	}
	
	//if no data series is longer than 15, procees to merge length index to futher compress the data.
	if(shortSeriesArray){
		int result[pos];
		int resultIndex = 0;
		
		uint8_t length;
		uint8_t value;
		
		
		for(int i = 0; i<pos;i+=4){
			if(encoding[i] < 16 && i+2>pos){
				uint8_t length = encoding[i];
				uint8_t value = encoding[i+1];
				result[resultIndex] = length;
				result[resultIndex+1] = value;
				resultIndex += 2;
			}
			if(encoding[i] < 16 && encoding[i+2] < 16){
				length = encoding[i];
				value = encoding[i+1];
				result[resultIndex] = length;
				result[resultIndex+1] = value;
				
				length = encoding[i+2];
				value = encoding[i+3];
				//use offset to access the upper bits of the byte,
				//With this method we can store two length index smaller than 16 in one byte 
				result[resultIndex] += length<<4;
				result[resultIndex+2] = value;
				
				resultIndex += 3;
			}
		}
		
		//Exit the program if compressed data is larger than original data
		//(Which will occor when there is not a lot of repeated data in the array
		if (resultIndex > data_size){
			cout<<"Error, data is incompressible by RLE"<<endl;
			cout<<"No data is changed, exiting the function"<<endl;
			return data_size;
		}
		
		//copy the data form temporary array to given data pointer 
		for (int i=0; i<resultIndex;i++){
			data_ptr[i+1] = result[i];
		}
		
		//use the first element of data array to indicate we have
		//futher compressed data from RLE
		data_ptr[0] = 0;
		
		return resultIndex+1;
		
		
	//if the data contain data in series longer than 15, leave data as is in simple RLE
	}else{
		
		//Exit the program if compressed data is larger than original data
		//(Which will occor when there is not a lot of repeated data in the array
		if (pos > data_size){
			cout<<"Error, data is incompressible by RLE"<<endl;
			cout<<"No data is changed, exiting the program"<<endl;
			exit(1);
		}
		
		//copy the data form temporary array to given data pointer 
		for (int i=0; i<pos;i++){
			data_ptr[i+1] = encoding[i];
		}
		
		//use the first element of data array to indicate we have
		//Left compression at RLE state 
		data_ptr[0] = 1;
	
		return pos+1;		
	}
}







/**
 * Data decompression algorithm
 *	
 * @param pointer to the data buffer
 * @param size of data
 * @return size of data after decompression 
 * 
 * Note this decompression function is draft version and for testing purpose only
 */
int byte_decompressRLE(uint8_t data_ptr[], int data_size){
	
	//if data is compressed futher from RLE
	if(data_ptr[0] == 0){
	
		//first decompress data into RLE form.
		//With decompression to RLE, as of version 1.2.2 
		//the size of the data should be 1.33333 size of original size
		int decoding[(int)(data_size * 1.5)];					
		int pos = 0;
		
		uint8_t firstLength;
		uint8_t secondLength;
		uint8_t firstData;
		uint8_t secondData;
		
		//decompression data to DRL
		for (int i = 1; i < data_size; i+=3){
			firstLength = data_ptr[i] & 0xF;
			secondLength = data_ptr[i] >> 4;
			firstData = data_ptr[i+1];
			secondData = data_ptr[i+2];

			decoding[pos++] = firstLength;
			decoding[pos++] = firstData;
			decoding[pos++] = secondLength;
			decoding[pos++] = secondData;
		}
		
		//the size of result could vary depends on the data
		//since this is a draft we will assume it does not exceed 100
		int result[100];					
		int resultPos = 0;
		
		//decoding method 
		for(int i = 0; i < pos; i+=2){
			for(int j = 0; j < decoding[i];j++){
				result[resultPos++] = decoding[i+1];
			}
		}

		//write to the array
		for (int i=0; i<resultPos;i++){
			data_ptr[i] = result[i];
		}

		return resultPos;	
	}
	
	
	
	//if data is compressed by RLE
	else{
		
		//the size of result could vary depends on the data
		//since this is a draft we will assume it does not exceed 100
		int result[100];					
		int resultPos = 0;
		
		//decoding method 
		for(int i = 1; i < data_size; i+=2){
			for(int j = 0; j < data_ptr[i];j++){
				result[resultPos++] = data_ptr[i+1];
			}
		}

		//write to the array
		for (int i=0; i<resultPos;i++){
			data_ptr[i] = result[i];
		}

		return resultPos;
	}

}