# Cache-Simulator

## Overview
This project was created for the Computer Organization & Assembly Language course, taught at the American University in Cairo in the Summer 2024 semester, under the instruction of Dr. Mohamed Shalan.  
  
The project simulates a set-associative cache, precisely its special cases, Direct Map and Fully Associative caches. It aims to illustrate the effects of different cache parameters on its performance, thus helping us enhannce our understanding of how the cache works and how to analyze the effect of its different parameters on the hit ratio. 

## Repo Content
- Tests: a directory which has 5 test cases that were used to test the correctness of our cose
- cache.cpp: the source code used to run the experiment and generate the results
- Report.pdf: a report detailing the methodology used to collect the data, its the results and analysis, as well as the conclusions reached

## How to build 
Building the program can be done on the command line using the following commands:
- `cd <cloned_program_directory>`
- `g++ cache.cpp -o cache.exe`

## How to use 
After building the program, you have two options to run the program:
1- Run the executable file directly. In this case, the program will produce random data of the specified number of iterations, dictated by line 137.
2- Input a text file having the addresses in decimal, the program will read the addresses from the text file and output accordingly. 
That can be done using the following commands:
- for windows use `.\cache.exe <data_file>[optional]`
- for MacOS use `./cache.exe <data_file>[optional]`

## Program Design
The program operates as follows:
- The user has the option to either input a text file with addresses to simulate accessing them, or to use one of the avaiable 6 Memory Generator functions to generate a set amount of addresses.
- The user is then prompted to pick the line size and the cache type [DM | FA] they'd like to simulate.
- For every requested address, the program calls the decided cache type function to simulates the behavior of an actual cache and return whether the access was a hit or a miss.
- The total hit rate is calculated and output to the terminal, along with the individual return [Hit | Miss] results for each address.

## Limitations in the program 
- Only covers the extreme cases of Set Associative caches: 1-way (DM) and n-way (FA).
- Does not take into consideration cache size as a possible variable parameter that could affect cache performance.
- Does not test the effect of other replacement policies (e.g. LRU, LFU) for FA caches.
- As of now, changing the MemGen function used requires the user to edit the code rather than be prompted to pick.

## Challenges 
- As we do not have a lot of experience wth data analysis, we struggled at first on how to approach the analysis and what points to consider.
- Calculating some probabilities, used to aid our understanding of the data trends, sometimes proved to be tricky and more complicated than we were used to, resulting in some confusion.

## Test cases 
The following test case files were input to the program with the following parameters to test and verify the correctness of our program
Note: The cache size and FA replacement policy (RAND -> FIFO) were changed for testing purposes.
- Test1:
  - Tests: Re-accessing previously fetched addresses for both DM and FA
  - Cache Specifications: cache size = 4 bytes, line size = 2, expected hit ratio_DM = 50%, expected hit_ratio_FA = 50%.
- Test2: 
  - Tests: Random address access in DM / Replacement policies efficiency in FA.
  - Cache Specifications: cache size = 16 bytes, line size = 2, expected hit ratio_DM = 44%, expected hit ratio_FA = 44%
- Test3:  
   - Tests: Conflict misses in DM / Temporal locality in FA.
   - Cache Specifications: cache size = 128 bytes, line size = 16, expected hit ratio_DM = 40%, expected hit ratio_FA = 50%
- Test4: 
   - Tests: Sequential access in DM.
   - Cache cache size = 16 bytes , line size = 1, expected hit ratio_DM = 0% 
- Test5: 
   - Tests: Random Access in FA
   - Cache cache size = 16 bytes, line size = 1, expected hit ratio_FA = 27% 

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
