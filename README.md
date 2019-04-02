# Comparision of Convex Hull Algorithm

We have implemented 3 algorithms, Graham Scan, Kirk Patrick Seidel, and Jarvis March algorithms to find the convex hull in two dimensions.

|   Algorithm                 |Complexity |
|-----------------------------|-----------|
|Graham Scan Algorithm        | O(nlog(n))|
|Kirk Patrick Seidel Algorithm|O(nlog(h)) |
|Jarvis March Algorithm       | O(n^2)    |

We have obtained these runtimes for the following algorithms.


|Size|Graham Scan Algorithm|Kirk Patrick Seidel Algorithm| Jarvis March Algorithm|
|-|-|-|-|
|10|0.004|0.009|0.004|
|100|0.004|0.009|0.004|
|1000|0.010|0.011|0.019|
|10000|0.048|0.026|0.147|

[*In seconds (4 is also the least possible value.)]

As we can see the Kirk Patrick Seidel Algorithm is slightly expensive while initializing for smaller datasets, but for larger datasets gives quite good performance.

As we can see, during the starting the time taken for Graham Scan and Jarvis March, but after 1000 points we can see the disparity in the time taken to compute.
