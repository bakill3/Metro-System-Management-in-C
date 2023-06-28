# Metro System Management
# 1. Introduction
The company that manages the Metro Mondego mobility system wants a program that manages the various existing lines. This program should keep updated information about the lines that make up the system and suggest routes between 2 stops.

Each line of the Mondego Metro system consists of several stops. At each stop people can come and go. The lines can be traversed in both directions. You can consider that the lines are not circular and none of them passes twice through the same stop.

The system consists of several lines that intersect in some stops. In these locations, a passenger may exit one of the lines and enter another.

# 2. Program to Implement
It is intended to develop a program in C language that allows the management of the mobility system of Metro Mondego The planned features are described in the following points.

## 2.1	Stops

The stops belonging to the system are identified by a name and an alphanumeric code with 4 characters. Both the name and the alphanumeric code are unique, that is, there cannot be 2 stops with the same name and/or the same alphanumeric code. You can add other fields if you think it is convenient (for example, to how many lines a particular stop belongs to or other relevant information). During program execution, this information is stored in a dynamic array of structures.

### 2.1.1 Operations on Stops

- **Log Stop**: New stops can be added to the system. The name is entered by the user, but the unique alphanumeric code must be generated automatically by the program (this field is not specified by the user). When a new stop is added, it is not associated with any line. This will be done later (see point 2.2.1).

- **Eliminate Stop**: A system stop can be eliminated. The stop code to be deleted is entered by the user. Only stops that are not part of any line can be eliminated.

- **View Stops**: The full list of existing system stops can be displayed on the console.

## 2.2 Line Management
Complete information on metro lines shall be maintained in a dynamic structure of the linked list type.

### 2.1.1 Operations on Lines
 - **Add Lines**: New lines can be added to the mobility system. The addition can be made from information entered by the user or by reading this data from a text file1. All information required to create the line must be specified, including its name and the various stops. It is not possible to have two lines with the same name, nor to include in the line stops not registered in the system.
 - **Update Line**: The sequence of stops of a line can be updated. The update may consist of adding or deleting one or more stops.
 - **View Lines**: The program must allow the complete presentation of all existing lines in the system. It should also be possible to show lines passing at a given stop.

## 2.3	Calculation of Routes
In this feature, the program should present a list of all the routes that connect 2 stops. The user indicates the names of the starting point and the arrival point and the program shows which lines allow the connection. The entire route must be indicated, that is, all stops between the starting point and the arrival point.
The list should consider two possibilities:
i.	Route made in a single line
ii.	Route with a change of Line2

## 2.4	File Storage
Immediately before the execution ends, the program must store the stop and line information in a binary file. This information should allow to reconstruct the dynamic structures (dynamic array and linked list) when the program resumes execution.

# 3. Text File
Information about a new line to be added to the system can be specified through a text file. Each text file can only contain information about one line.

The format is as follows:
i.	- The name of the new line (i.e., the path name) of the metro line appears in the first line of the file
ii.	- On the following lines of the file the name and the alphanumeric identifier of the stops appear (1 stop per line).

The character '#' separates the stop name from its alphanumeric identifier. You can assume that this character is never part of the name or identifier and acts only as a separator.





