## Implementation of dijkstra's algorithm


### How to use:

#### You need:

* Djikstra.exe,
* file with your Vertex data *f.e. (...).txt*



#### To run this program you have to run your cmd then give five arguments:

1. .exe file path
1.  data_file path *example below*
1. name of Vertex (source)
1. name of Vertex (target)
1. output file path *example below*



### Examples:

#####  *example of implication:*

```
C:\Users\user\Djikstra.exe C:\Users\user\distances.txt Bielsko-Biala Warszawa C:\Users\user\destination.txt
```



#####  *example of your data_file:*

```
Bielsko-Biala Katowice 61.7
Bielsko-Biala Wadowice 37.8
Czestochowa Lublin 322.0
Czestochowa Lodz 126.0
Czestochowa Warszawa 218.0
Gliwice Czestochowa 75.9
Gliwice Katowice 28.4
Katowice Czestochowa 74.6
Katowice Krakow 81.0
Katowice Wadowice 71.0
Krakow Czestochowa 141.0
Krakow Lublin 279.0
Krakow Wadowice 51.8
Krakow Warszawa 292.0
Lublin Warszawa 178.0
Lublin Lodz 294.0
Lodz Warszawa 140.0
```

#####  *example of output file:*

```
Warszawa 354.3
Czestochowa 136.3
Katowice 61.7
Bielsko-Biala 0
```


##### Compiled with Visual Studio 2017
