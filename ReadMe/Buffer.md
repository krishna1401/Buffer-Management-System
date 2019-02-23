> This header file provides a **structure** for the **Cache Blocks**

## Structure Information
| S.No | Var. Name | Data Type | Use |
| ---- | --------- | --------- | --- |
|  1   | blockNumber |   int   | Store the *Block Number* whose data is available in the Buffer |
|  2   | processID |    int    | Store the *Process ID Number* accessing the Buffer |
|  3   |  status   |    int    | Defines the *Current Status* of the Buffer |
|  4   |   data    |  string   | Stores the *Actual Data* of the Block in the Buffer |
|  5   | nextHashQueue | Buffer | Pointer to the *Next Buffer* in Specific Hash Queue |
|  6   | prevHashQueue | Buffer | Pointer to the *Previous Buffer* in Specific Hash Queue |
|  7   | nextFreeList | Buffer | Pointer to the *Next Buffer* in Free List |
|  8   | prevFreeList | Buffer | Pointer to the *Previous Buffer* in Free List |

## Status Type's
| Status No. | Description |
| ---------- | ----------- |
| 0 | Free Buffer |
| 1 | Locked Buffer |
| 2 | Invalid Data Buffer |
| 3 | Marked Delayed Write |

## Functions
1. **Buffer()**: Default Constructor for the Buffer
2. **Buffer(...)**: Parameterized Constructor to initialize Variables for the Buffer
3. **display()**: Function to print Information about the Current Buffer 
