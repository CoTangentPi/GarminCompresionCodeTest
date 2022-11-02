Garmin Canada Code Design Test

Aurhor Chachi (Shichao) Han
*Chachi_h@hotmail.com

Version: 2.2.2
To compile the code:
g++ -Wall Driver.cpp Compression.cpp

Code included: 
Driver.cpp Compression.h and Compression.cpp 



If run the driver program, it will call test code with given data array, 
which is hard coded in the driver.cpp code
The driver will print out original data, data after compression, and data after decompression
Function will edit on the original data and return the size of compressed data. 
Thus, the end of the original data, will still be occupied and will not be deleted. 

*-------------------------------------------------------------------------------------------------------*
| Design concept: 																			                                        		   	|
|																										                                                    |
| At current state of the program, the compression algorithm is based on Run Length Encoding		      	|
| The program first run standard RLE to the given data,											                        		|
| 																									                                                  	|
| Then the program check if there is any series of data longer than 16 									                |
| If not, RLE might not be the most efficiency method, program will attempt to compress further		    	|
| program will merge the length index of the compression, 										                      		|   
| write first index in the lower bit of a byte and write second index to the upper bit of the same byte |
| This way it can effectively compress 4 byte RLE into 3 byte						                      					|
|																							                                                    			|
| If there does exist a series of data longer than 16,													                        |
| Assuming if there is predictable pattern in the data, therefore if there is a repeated data chain		  |
| longer than 16, there will be more data chain longer.												                        	|
| Due to the effectiveness of RLE for long chain of datas,										                       		|
| we will simply stop the compression program at RLE state. 									                      		|
|																									                                                    	|
| The RLE only works for array with same value repeated in series.									                   	|
| And RLE algorithm has complexity of O(n). 														                              	|
*-------------------------------------------------------------------------------------------------------*
