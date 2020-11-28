# Algorithm_and_DataStructure

University project from Algorithm and data structures's exam.
This is one of the most important exam in computer science, learning data structures, algorithms and their complexity. This is just one part of the exam.

# 1
Suppose you have to memorize rows which are stored in this format :
key1:key2:data.
Key1 and Key2 are integers and data is an alphanumeric string having arbitrary lenght. 
Project and implement a data structure like so, from a red-black tree where each node points to an hash table. Keep in mind that key1 is the key for red-black tree's node and key2 is the indexing the hash table where is stored data.
This data structure has to allows you to insert, search and delete a row; create a menu for doing so.


# 2
You a text file within the first row there are three integers separeted by a space : 
  1. number S of stellar systems (from 1 to S);
  2. number C of connection between systems;
  3. number W wormholes;
  
The last W systems have a wormhole.
The other C rows have three numbers S1,S2 and T; starting system, end system and travel time.
  1. every travel between two points on the map has a different T time;
  2. every travel between two points is bidirectional;
  3. travel between two wormhole costs one unit time;
  4. the traveler can decide to use wormhole or not.

The goal is to compute the fastest path from system1 to system2, indicating the systems to cross.
Assume that :
  1. 2 ≤ S ≤ 1000
  2. 1 ≤ C ≤ 10000
  3. 2 ≤ W ≤ S
