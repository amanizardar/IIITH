import requests
import json
from random import randint

ischef=0
global uid
isloggedin=False

def signup():
    userid=input("Enter User id ")
    username=input("Enter name ")
    password=input("Enter password ")
    data={"userid":userid,"username":username,"password":password}
    response =requests.post('http://localhost:8000/user/signup',json=data).content
    response=response.decode().strip()
    global uid;
    if(response=="1"):
        uid=userid
        return True
    else:
        return False

def login():
    userid=input("Enter Userid ")
    # username=input("Enter student name ")
    password=input("Enter password ")
    data={"userid":userid,"password":password}
    response =requests.post('http://localhost:8000/user/login',json=data).content
    response=response.decode()
    response=json.loads(response)

    success=response['bool']
    chef=response['Chef']

    

    global uid
    global ischef
    if(success==1):
        uid=userid
        if(chef):
            ischef=chef
            print("HEY CHEF!!")
        return True
    else:
        return False

########################################################################

dicmenu = {}
'''a Dictionary that contains menuItems and prices and key_value pair.
    Key is the itemno and value is a list containing two numbers
    first one is the price of the half plate
    and second one is the price of the full plate.
'''

def ReadMenu():
    dicmenu.clear()   # Making dicmenu dictionary Empty 
    response =requests.get('http://localhost:8000/menu/read').content
    response=response.decode()
    y = json.loads(response)

    if len(y) == 0:
        print("\nNo Items In the Menu")
        return
    print("\nMenu is:>>>>>>>>\n")
    print("Item No ",end="\t")
    print("Halprice ",end="\t")
    print("Fullprice ")


    for item in y:
        print(item,end="\t\t")
        print(y[item]['halfprice'],end="\t\t")
        print(y[item]['fullprice'])
        # Appending data to dictionary
        itemno = int(item)
        halfplate = int(y[item]['halfprice'])
        fullplate = int(y[item]['fullprice'])
        listplate = []
        listplate.append(halfplate)
        listplate.append(fullplate)
        dicmenu[itemno] = listplate

 
    print("")



# ###########################################################################
# From Here Order food Logic starts



orderinfo = []  # item no,platesize,quantity,total price
'''A list that contains the information about the order
       It is a list of list that contains four values.
       first value is the item number
       second is the plate size
       third is the quantity of that order
       and forth is total price of that quantity.
'''
    


def Orderfood():
    print("\nPlease Place your Order")
    print("\nFirst Enter the total number of items you want to order from the menu")
    
    totalitems = 0
    '''total number of distinct item ordered'''
    totalbill=0.0
    '''A variable that store the total amount of the bill'''

    
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
    
    
    orderinfojson = {}
    
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

        orderinfojson[itemno]={'platesize':platesize, 'quantity': quantity,'price':price,'userid':uid}
        '''Appending order details in the orderinfo list'''


    response =requests.post('http://localhost:8000/orderfood',json=orderinfojson).content
    print("")
    print(response.decode())


def GenerateBill():

    if(not orderinfo):
        print("Please Order Some Item before genetating Bill Thankyou!\n")
        return



    print("Give Some tip : Enter 1 for 0% ,2 for 10% and 3 for 20% tip : ", end="")


    tip = input()
    try:
        tip = int(tip)
    except Exception as e:
        print("Please Enter a valid number")
    # tipamount = 0.0
    # '''A variable which stores the information about the total tip amount '''

    # if(tip == 1):
    #     tipamount = 0
    # elif(tip == 2):
    #     tipamount = totalbill*0.1
    # elif(tip == 3):
    #     tipamount = totalbill*0.2
    # else:
    #     print("Invalid Tip.")
    # totalbill = totalbill+tipamount
    # '''Increasing total bill by tipamount given'''

    # format_totalbill = "{:.2f}".format(totalbill)
    # '''Formating output to 2 decimal places'''

    # print()
    # print("Total amount including the tip you need to pay is = ", format_totalbill)

    print()

    peoplesplit = input("Please Enter how many people plan to split the bill= ")
    try:

        peoplesplit = int(peoplesplit)
    except Exception as e:
        print("Please Enter a valid number")
    # print(f"Share that {peoplesplit} people has to contribute is = ",
    #       "{:.2f}".format(round(totalbill/peoplesplit, 2)))

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


    # discountmoney = 0.0
    # '''total discount amount'''

    if(participate == 1):
        print("WELCOME to the “Test your luck” event\n")

        discount = randint(1, 100)
        '''Generating a random number between 1-100'''
        if(discount <= 5):   # 5% chance to get a 50% discount off the total bill
            print("Congratulation! You Got 50% Discount on your Total Bill")

            discountmoney = 0.5
            # totalbill = totalbill-discountmoney
        elif(discount > 5 and discount <= 15):   # 10% chance to get 25% discount
            print("Congratulation! You Got 25% Discount on your Total Bill")

            discountmoney = 0.25
            # totalbill = totalbill-discountmoney
        elif(discount > 15 and discount <= 30):    # 15% chance to get 10% discount
            print("Congratulation! You Got 10% Discount on your Total Bill")

            discountmoney = 0.1
            # totalbill = totalbill-discountmoney
        elif(discount > 30 and discount <= 50):     # 20 % chance o get no discount
            print("You Got No Discount. Better Luck Next time")

            discountmoney = 0.0
            # totalbill = totalbill-discountmoney
        elif(discount > 50 and discount <= 100):
            # 50 % chance that the total amount increases by 20%

            print("Bad Luck ! we are Increasing your bill amount by 20%")
            discountmoney = (0.20)*(-1)
            # totalbill = totalbill-discountmoney
        else:
            print("Invalid Discount")

        if(discountmoney > 0):
            '''If getting discount '''

            # print("Your total Discount amount is = ",
            #       "{:.2f}".format(discountmoney))
            # print()
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

    tip_split={'uid':uid,'tip':tip, 'split': peoplesplit,'discount':discountmoney}

        
    response =requests.post('http://localhost:8000/transaction/entry',json=tip_split).content
    response=response.decode()
    # print(response)
    # print(type(response))

    response=json.loads(response)




    print()
    print("This is Your Total Breakdown of The bill: ")
    print()
    # print(response[0])
    # print(response[1])
    # print(response[2])
    # print(response[3])


    totalbill = response['total']
    '''Total price of only ordered items
       without including any tip or anything else.'''
    discountmoney=response['discount']

    total=0

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

    orderinfo.clear()  #clearing prev orders


######################################################################################

def ShowPrevBill():

    data = {'userid':uid}
    response =requests.get('http://localhost:8000/transaction/fetch',json=data).content
    response=response.decode()
    response=json.loads(response)

    print("\n Your Previous Bill statements::>>>>>\n")
    

    print(response)




#########################################################################################

def Logout():
    # print("Calling logout route")
    global isloggedin
    global ischef

    if(not isloggedin):
        print("Please Login First")
        return

    response =requests.get('http://localhost:8000/user/logout').content
    isloggedin=False
    ischef=False
    print(response.decode())
    ProgramStart()





##########################################################################################

def  Add_to_the_menu():
    print("################")
    print("Hello Chef, Please add a New item to the Menu")
    itemid=input("Enter item id ")
    halfprice=input("Enter Half plate Price ")
    fullprice=input("Enter Full Plate Price ")
    data={"menuid":itemid,"halfprice":halfprice,"fullprice":fullprice}
    response =requests.post('http://localhost:8000/menu/add',json=data).content
    print(response.decode())

    

##########################################################################################

def ProgramStart():
    while(1):
        global isloggedin
        print("Welcome To the Indiana Restaurent")
        print("If you are a new customer Please Signup")
        print("If you are a Returning Customer Please Login")
        print("Press 1 for Signup or Press 2 for Login: ")
        login_or_signup=input()
        try:
            login_or_signup=int(login_or_signup)
        except Exception as e:
            print("Please Enter a Valid Input\n")
            continue
        if(login_or_signup==1):
            if(signup()):
                isloggedin=True
                print("Account Created Successfully You are Also Logged In")
                break
            else:
                print("\nUser Already Exist! Please Try to Login")
        elif(login_or_signup==2):
            if(login()):
                isloggedin=True
                print("\nCongratulations! You are Now Logged In")
                break
            else:
                print("\nInvalid Username or Password")
        else:
            print("\nPlease Enter a Valid Input")

ProgramStart()



while(1):
    print("\n\nTo Read Our Menu Press 1")
    print("To Order Food press 2")
    print("To Generate Bill press 3")
    print("To Show Previous Bill Statements press 4")
    print("To Logout Press 5")
    if(ischef):
        print("To add New Items To the Menu Press 6")
    print("")

    selected_option=int(input())

    if(selected_option==1):
        ReadMenu()
    elif(selected_option==2):
        Orderfood()
    elif(selected_option==3):
        GenerateBill()
    elif(selected_option==4):
        ShowPrevBill()
    elif(selected_option==5):
        Logout()
    elif(selected_option==6 and ischef):
        Add_to_the_menu()
    else:
        print("Please Enter Valid Input ")
    





