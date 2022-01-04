This is the Readme File For the SSD assignment 3A 

Submitted By :- Aman Izardar
Enroll No    :  2021201028
Email        :  aman.izardar@students.iiit.ac.in


To execute from cmd line simply execute the following cmd :-
        python3 -u < path of the bill.py file>

The First line of the input will be an interger n denoting the total number of items to order.
after that following n lines will contain three space seprates values:
    first value will be the itemnumber of the item to be ordered
    second value will be a string "half" or "full" in any case denoting the type of plate
    third value will be an integer that is the quantity of that item.

after that next line will contain a single integar 0 or 1 or 2 for the tip 
    if entered 0 means no tip
               1 means 10% tip
               2 means 20% tip

the next line will also be an integer denoting the number of people contributing in the bill amount.

next line will be 0 or 1 
    0 means no participation in the event
    1 means they will participate in the “Test your luck” event.


sample input 1 : 

    2
    1 half 2
    2 full 3
    1
    3
    1

sample input 2 : 

    3
    2 half 1
    3 full 2
    1 full 3
    2
    2
    0
