# Exam_In_Cpp

Implement and test an uncopyable template circular buffer class according to the requirements below.
1. Use a template type (T) and a non-type(N) template parameters.
  
2. A buffer is an array of type T whose length is N

3. Ensure that N is at least 4

4. The class shall have a function to clear a buffer

5. The class shall have a function to read data from a buffer

6. The class shall have a function to write data to a buffer

7. If the buffer is full then the oldest data shall be overwritten

8. The class shall have a function to return the number of data elements stored in a buffer

9. The class shall have a function to check if a buffer is full or not

Overload the insertion operator (<<) for the class to print all the stored elements in a buffer to the terminal
The class shall be tested using assertion.

Run: g++ main.cpp -o main ./main
