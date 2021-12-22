# **rolling hash**<br>
* **first, records all the hash numbers of the substr extracting from string with fixed length**<br>
* **second, compute the hash number for substr extracting from the others and get the repeating hash number**<br>
* **thirdly, collision check optionally**<br>
* **Finally, the repeating hash number will become fewer and fewer.**<br>
    * **And if we haven not traversed the string element into the end and the hash numbers become zero, there is no need to continue on**<br>
    * **And if we traverse the string element into the end and the hash numbers are not empty, there is a common substr**<br>
# **binary serach**<br>
* **the length must be floating between zero and the minimum value of all the legths of the elements**<br>
* **so we can try to find the maximum common length by binary search**<br>