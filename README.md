***Read Me***

1. Copy the file apriori.cpp from “CPP files” folder to the “Data” folder and run the following command:

2. g++ -std=c++11 -o apriori apriori.cpp 
then type ./apriori in command line.

3. The executable should get three parameters as input: 1-file name; 2-minimum-support; and 3-minimum confidence. The thresholds should be numbers between 0 and 1. The fourth parameter is either "r", "f", "a", or absent. When "r", then all strong association rules are displayed. When "f" then all frequent itemsets are displayed. When "a" then all frequent itemsets and all strong association rules are displayed. When absent, then only the number of frequent itemsets of different sizes and the number of strong rules are displayed. When displaying the frequent itemsets, their support "(s)" is printed. When displaying the strong rules, their support and confidence "(s, c)" is printed. In both cases with 2 decimal point precision.


4. stats.txt in stats_* folder contains all the execution time and number of frequent item sets and strong association rules for 100, 1000 and 10,000 datasets.

5. Attached is the strong_rules.txt for all strong rules for 10000 (actually 9949) transactions.

6. Code references: I used some functions written by Stackoverflow (SO) users and I credited them (by putting the SO web url and their name) just before the respective functions in my .cpp files. 

7. apriori.cpp will always create strong_rules.txt and stats.txt for testing purpose.