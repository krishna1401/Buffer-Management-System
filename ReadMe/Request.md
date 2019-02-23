> This header file provides a **structure** for **Process Request**

## Structure Information
| S.No | Var. Name | Data Type | Use |
| ---- | --------- | --------- | --- |
|  1   | processID |    int    | Store the *Process ID Number* accessing the Buffer |
|  2   | blockNumber |   int   | Store the *Block Number* whose data is available in the Buffer |
|  3   | requestType |   int   | Defines the *Request Type* for the Buffer |

## Request Type's
| Status No. | Description |
| ---------- | ----------- |
|      1     | Get Block Buffer |
|      2     | Release Block Buffer |
|      3     | Release Block Buffer with Delayed Write |

## Functions
1. **Request()**: Default Constructor for Request
2. **Request(...)**: Parameterized Constructor to initialize Variables for the Request
3. **display()**: Function to print Information about the Current Request

## Other Functions
1. **string_to_integer(...)**: Convert the String Input into corresponding Integer Value
