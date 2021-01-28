# get_next_line
## Description

My implementation of the get_next_line function. <br>
Function that reads line by line from a stream. <br>
## Usage

```c
#define BUFFER_SIZE 32
int	get_next_line(int fd, char **line);
```
* return ``1`` If the line is received and it is not the last one
* return ``0`` If this is the last line
* return ``-1`` If there is an error when reading the string
