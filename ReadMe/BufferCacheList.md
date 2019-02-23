> This header file provides a **class** for **Circular Double Buffer Linked List**

## Structure Information
| S.No | Var. Name | Data Type | Use |
| ---- | --------- | --------- | --- |
|   1  |   head    |   Buffer  | Points to the *Head* of the Linked List |
|   2  |   tail    |   Buffer  | Points to the *Tail* of the Linked List |

## Functions
1. **isEmpty()**: Check whether the specific Linked List is Empty or Not
2. **findBuffer(...)**: Find the Buffer in the Linked List specified by Block Number
3. **searchBuffer(...)**: Check whether a specific Block Buffer is in the Linked List or Not
4. **insertBufferAtHeadFreeList(...)**: Insert Buffer at Head of Free List
5. **insertBufferAtTail(...)**: Insert Buffer at Tail of Free List or Hash Queue
6. **removeBufferFromHeadFreeList()**: Remove & Return a Buffer from Head of Free List
7. **removeSpecificBuffer(...)**: Remove a Buffer from Free List or Hash Queue
8. **displayHashQueue()**: Print the content of a specific Hash Queue
9. **displayFreeList()**: Print the content of Free List
