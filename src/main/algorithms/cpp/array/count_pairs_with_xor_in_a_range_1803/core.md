Intuition 2: trie is often used to group numbers based on their bit prefixes.<br>
The trickiest part is how to use a trie to count pairs. Before inserting a number, we count how many pairs it can make with numbers that are already in the tree. For that, we need to store a count for each node, so we know how many numbers are under that node.<br>
For this problem, picking a good example is very important. Let's say our limit is 5 (0101), and we've added numbers 5, 10, 11, 12, and 13. Now, let's count how many pairs number 9 (1001) can make with the numbers in the trie.<br>

First bit is 0 for limit, and 1 for number. So we continue to subtree 1.<br>
    All numbers in the 0 subtree will not make any pairs (e.g. 5 XOR 9 = 12).<br>
    Continue to 1 subtree (0 XOR 1).<br>
Second bit is 1 for limit, and 0 for number.<br>
    All numbers in 0 subtree will make pairs with 9 (+ 2 pairs).<br>
    Continue to 1 subtree (1 XOR 0).<br>
Third bit is 0 for limit, and 0 for number.<br>
    Continue to 0 subtree (0 XOR 0).<br>
    Fourt bit is 1 for limit, and 1 for number.<br>
All numbers in 1 subtree will make pairs with 9 (+ 1 pair).<br>
    Continue to 0 subtree (1 XOR 1).<br>
    Therefore, 3 numbers in the trie make pair with 9 (1001):<br>
<br>
10: 1010 ^ 1001 = 0011 = 3<br>
11: 1011^ 1001 = 0010 = 2<br>
13: 1101 ^ 1001 = 0100 = 4<br>