/**
 * Garmin Canada Code Design Test
 *
 * Aurhor Chachi (Shichao) Han
 * Chachi_h@hotmail.com
 * 
 * Compression.cpp
 * @since 1.0.0
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
int byte_compress(int data_ptr[], int data_size){
	
	int pos = 0;
	
	for(int i = 0; i<data_size;i++){
		int counter = 1;
		while ( (data_ptr[i] == data_ptr[i+1]) && i<data_size-1 ){
			counter++;
			i++;
		}
		cout<<"It Works!!!!"<<data_ptr[i]<<" "<<counter<<endl;
		data_ptr[pos++] = counter;
		data_ptr[pos++] = data_ptr[i];
		// cout<<"position is "<<pos<<endl;
		cout<<"---------------------"<<endl;
	}
	
	
	// data_ptr[pos] = 11;
	// data_ptr[pos++] = 22;
	// data_ptr[pos++] = 33;
	// data_ptr[pos++] = 44;
	// data_ptr[pos++] = 55;
	
	
	return pos;
}