# binary-search and then BFS
* ***binary search***<br>
    * **mid and judgement**<br>
    ```
    // [left, right)
    while (left < right) {
        mid = (left + right + 1) / 2;
        if (canThrough(arguments)) {
            // other operation to remember the position
            left = mid + 1;
        } else {
            right = mid;

        }
    }

    // [left, right]
    while (left <= right) {
        mid = (left + right + 1) / 2;
        if (canThrough(arguments)) {
            // other operation to remember the position
            left = mid + 1;
        } else {
            right = mid - 1;

        }
    }
    ```
* ***BFS***<br>
* **because no need to record the specified order or path, so we can do it together**<br>