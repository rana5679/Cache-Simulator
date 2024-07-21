# Cache-Simulator

## Overview
This project was created for the Computer Organization & Assembly Language course, taught at the American University in Cairo in the Summer 2024 semester, under the instruction of Dr. Mohamed Shalan.  
  
The project simulates a set-associative cache with its special cases, Direct Map and Fully Associative caches. It aims to illustrate the effect of different cache parameters on its performance which helps us understand how the cache works and how to analyze the effect of the parameters on the hit ratio. 

## Repo Content
- Tests
- cache.cpp

## How to build 
Building the program can be done on the command line using the following commands:
[...]

## How to use 
After building the program, you have two options to run the program:
1- Run the executable file directly. In this case, the program will produce random data of the specified number of iterations, dictated by line 137.
2- Input a text file having the addresses in decimal, the program will read the addresses from the text file and output accordingly. 
That can be done using the following commands:
- for windows use `.\cache.exe <text_file>[optional]`
- for MacOS use `./cache.exe <text_file>[optional]`

## Program Design

## Limitations in the program 

## Challenges 
- The ability to give accurate analysis to the results as we have not taken any data analysis course that might help in understanding the analysis.
- The ability to check the validity of the probabilities of the 1000000 iterations since it is difficult to simulate by hand. 
- 

## Test cases 
Note: We modified the cache size and the FA replacement policy (Rand -> FIFO) for testing purposes
- Test1.txt:- cache size = 4, line size = 2, hit ratio_DM = 50%, hit_ratio_FA = 50%, 
- Test2.txt:- cache size = 16, line size = 2, hit ratio_DM = 44%, hit ratio_FA = 44%,
- Test3.txt:- cache size = 128, line size = 16, hit ratio_DM = 40%, hit ratio_FA = 50%, 
- Test4.txt:- cache size = , line size = , hit ratio_DM = , hit ratio_FA = 
- Test5.txt:- cache size = , line size = , hit ratio_DM = , hit ratio_FA = 

## Collaborators
* [Arwa AbdelKarim](https://github.com/arwaabdelkarim)
* [Yasmina Mahdy](https://github.com/Yasmina-Mahdy)
  
## License
Copyright 2024 Arwa Abdelkarim  
Copyright 2024 Rana Taher  
Copyright 2024 Yasmina Mahdy  

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
