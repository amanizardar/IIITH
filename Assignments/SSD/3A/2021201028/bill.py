"""import statements"""
import pprint
from random import randint


menu = []
'''A list that contains Menu.csv Lines'''


with open("Menu.csv", 'r') as f:
    menu = f.read().splitlines()
    '''reading all the lines into menu list'''


menu = menu[1:]
'''removing the first line'''

dicmenu = {}
'''a Dictionary that contains menuItems and prices and key_value pair.
    Key is the itemno and value is a list containing two numbers
    first one is the price of the half plate
    and second one is the price of the full plate.
'''

for item in menu:
    threethings = item.split(',')
    itemno = int(threethings[0])
    halfplate = int(threethings[1])
    fullplate = int(threethings[2])
    listplate = []
    listplate.append(halfplate)
    listplate.append(fullplate)
    dicmenu[itemno] = listplate

    '''Inserting data into dicmenu dictionary'''


print()
print("Menu is:=\n")
print("Item no \tHalf plate\tFull Plate\n", end="")
for item, price in dicmenu.items():
    print(item, end="\t\t")
    print(price[0], end="\t\t")
    print(price[1])

print()
print("Please Place your Order")
print("First Enter the total number of items you want to order from the menu")

totalitems = 0
'''total number of distinct item ordered'''

totalitems = input()
try:
    totalitems = int(totalitems)
except Exception as e:
    print("Sorry Please Enter a Valid number")

print()
print(f"Now Enter {totalitems} items you want to order:")
print(f"\nInput will be {totalitems} lines each containing 3 values,")
print(f"first value will be item number,")
print(f"second value will be a string half/full")
print(f"third will be a number ", end="")
print("denoting number of plates to be orderded,", end="")
print(" for example -> 1 half 2")
print()


orderinfo = []  # item no,platesize,quantity,total price
'''A list that contains the information about the order
   It is a list of list that contains four values.
   first value is the item number
   second is the plate size
   third is the quantity of that order
   and forth is total price of that quantity.
'''

totalbill = 0.0
'''A variable that store the total amount of the bill'''

for line in range(totalitems):
    '''Taking input
       Input consist of lines of three values.
       first is the itemno of the item to be ordered
       second is a string half/full plate
       third is the quantity of that item.
    '''

    line1 = input().split()
    itemno = int(line1[0])
    platesize = line1[1].lower()
    quantity = int(line1[2])
    price = 0
    if(platesize == "half"):
        price = dicmenu[itemno][0]*quantity

    elif(platesize == "full"):
        price = dicmenu[itemno][1]*quantity
    else:
        print("Wrong Input !!!")
        exit(0)

    totalbill = totalbill+price

    thisorder = []
    thisorder.append(itemno)
    thisorder.append(platesize)
    thisorder.append(quantity)
    thisorder.append(price)
    orderinfo.append(thisorder)
    '''Appending order details in the orderinfo list'''


print()
print("Give Some tip : Enter 1 for 0% ,2 for 10% and 3 for 20% tip : ", end="")


tip = input()
try:
    tip = int(tip)
except Exception as e:
    print("Please Enter a valid number")

tipamount = 0.0
'''A variable which stores the information about the total tip amount '''

if(tip == 1):
    tipamount = 0
elif(tip == 2):
    tipamount = totalbill*0.1
elif(tip == 3):
    tipamount = totalbill*0.2
else:
    print("Invalid Tip.")

totalbill = totalbill+tipamount
'''Increasing total bill by tipamount given'''

format_totalbill = "{:.2f}".format(totalbill)
'''Formating output to 2 decimal places'''

print()
print("Total amount including the tip you need to pay is = ", format_totalbill)
print()


peoplesplit = input("Please Enter how many people plan to split the bill= ")
try:
    peoplesplit = int(peoplesplit)
except Exception as e:
    print("Please Enter a valid number")

print(f"Share that {peoplesplit} people has to contribute is = ",
      "{:.2f}".format(round(totalbill/peoplesplit, 2)))
print()
print("Attention Please!\nWe have a good news for you")
print("The Restaurant has started a limited time event called")
print("“Test your luck”")
print("Participate into event ", end="")
print("and get a chance to win upto 50% Discount on you bill")
print()

participate = input(
    "Please Enter 1 to participate in the Event or Press 0 to skip= ")
try:
    participate = int(participate)
except Exception as e:
    print("Please Enter a valid number")

print()


discountmoney = 0.0
'''total discount amount'''

if(participate == 1):
    print("WELCOME to the “Test your luck” event\n")
    discount = randint(1, 100)
    '''Generating a random number between 1-100'''

    if(discount <= 5):   # 5% chance to get a 50% discount off the total bill
        print("Congratulation! You Got 50% Discount on your Total Bill")
        discountmoney = totalbill*0.5
        totalbill = totalbill-discountmoney

    elif(discount > 5 and discount <= 15):   # 10% chance to get 25% discount
        print("Congratulation! You Got 25% Discount on your Total Bill")
        discountmoney = totalbill*0.25
        totalbill = totalbill-discountmoney

    elif(discount > 15 and discount <= 30):    # 15% chance to get 10% discount
        print("Congratulation! You Got 10% Discount on your Total Bill")
        discountmoney = totalbill*0.1
        totalbill = totalbill-discountmoney

    elif(discount > 30 and discount <= 50):     # 20 % chance o get no discount
        print("You Got No Discount. Better Luck Next time")
        discountmoney = 0.0
        totalbill = totalbill-discountmoney

    elif(discount > 50 and discount <= 100):
        # 50 % chance that the total amount increases by 20%
        print("Bad Luck ! we are Increasing your bill amount by 20%")
        discountmoney = (totalbill*0.20)*(-1)
        totalbill = totalbill-discountmoney

    else:
        print("Invalid Discount")

    if(discountmoney > 0):
        '''If getting discount '''
        print("Your total Discount amount is = ",
              "{:.2f}".format(discountmoney))

        print()
        print("****\t****")
        print("|  |\t|  |")
        print("|  |\t|  |")
        print("|  |\t|  |")
        print("****\t****")
        print("     {}      ")
        print("   ______   ")
        print()

    else:
        '''If amount Increased.'''
        increase = 0.0
        if(discountmoney != 0):
            increase = discountmoney*(-1)
        print("Total increase in your bill is = ", "{:.2f}".format(increase))
        print()
        print(" **** \n")
        print("*    *\n")
        print("*    *\n")
        print("*    *\n")
        print("*    *\n")
        print(" **** \n")

print()
print("This is Your Total Breakdown of The bill: ")
print()

total = 0.0
'''Total price of only ordered items
   without including any tip or anything else.'''


for item in orderinfo:
    itemno = item[0]
    platesize = item[1]
    itemquantity = item[2]
    itemTprice = item[3]
    total = total+itemTprice

    print(f"item {itemno} [{platesize}] [{itemquantity}] :",
          "{:.2f}".format(itemTprice))

print("Total :", "{:.2f}".format(total))

if(tip == 1):
    print("Tip Percentage: 0%")
elif(tip == 2):
    print("Tip Percentage: 10%")
elif(tip == 3):
    print("Tip Percentage: 20%")
if(discountmoney != 0.0):
    print("Discount/Increase : ", "{:.2f}".format(-discountmoney))
else:
    print("Discount/Increase : ", "{:.2f}".format(discountmoney))
print("Final Total : ", "{:.2f}".format(totalbill))

print()
print("Final Share That Each Person Has to Contribute is = ",
      "{:.2f}".format(round(totalbill/peoplesplit, 2)))
print()
print()


'''
    End of the Code
    Thankyou
'''
'''
Submitted by  : Aman Izardar
Enroll No.    : 2021201028
Email         : aman.izardar@students.iiit.ac.in
'''
