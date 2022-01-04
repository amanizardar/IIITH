# from enum import unique
from os import name
from sys import platform
from flask import Flask, request, render_template,jsonify
import flask_login
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, login_manager, login_user, logout_user, login_required, UserMixin,current_user
from flask_restful import Resource, Api
from sqlalchemy.orm import relationship
from sqlalchemy import  ForeignKey
import random

from sqlalchemy.sql.sqltypes import Date
login_manager.login_view = 'login'

def uniqueid():
    seed = random.getrandbits(32)
    while True:
       yield seed
       seed += 1

unique_sequence = uniqueid()


app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///restaurants.db'
app.config['SECRET_KEY'] = 'secretkey'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

api = Api(app)


db = SQLAlchemy(app)
login_manager = LoginManager()
login_manager.init_app(app)


class User(UserMixin, db.Model):
    userid  = db.Column(db.String(80), primary_key=True)
    name = db.Column(db.String(80), nullable=False)
    password = db.Column(db.String(80), nullable=False)
    ischef   = db.Column(db.Boolean,nullable=False)

    def __init__(self,userid,name,password,ischef=False):
        self.userid=userid
        self.name=name
        self.password=password
        self.ischef=ischef

    # def is_authenticated(self):
    #     return True

    # def is_active(self):   
    #     return True           

    # def is_anonymous(self):
    #     return False          

    def get_id(self):
           return self.userid

class Menu(UserMixin, db.Model):
    menuid       = db.Column(db.String(80), primary_key=True)
    halfprice = db.Column(db.Integer, nullable=False)
    fullprice = db.Column(db.Integer, nullable=False)

    def __init__(self,menuid,halfprice,fullprice):
        self.menuid=menuid
        self.halfprice=halfprice
        self.fullprice=fullprice


class Transaction(UserMixin, db.Model):
    transactionid   = db.Column(db.Integer, primary_key=True)
    
    userid = db.Column(db.String(80),ForeignKey(User.userid))
    date=db.Column(db.Date,)
    tip=db.Column(db.Integer)
    discount=db.Column(db.Float)
    split=db.Column(db.Integer)
    total=db.Column(db.Float)

    def __init__(self,userid,tip,discount,split,total):
        id1 = next(unique_sequence)
        self.transactionida=id1
        self.userid=userid
        self.tip=tip
        self.discount=discount
        self.split=split
        self.total=total



class Order(UserMixin, db.Model):
    orderid   = db.Column(db.Integer, primary_key=True)
    userid   = db.Column(db.String(80), ForeignKey(User.userid))
    itemid=db.Column(db.String(80), ForeignKey(Menu.menuid))
    plate  = db.Column(db.String(80))
    quantity=db.Column(db.Integer)
    price=db.Column(db.Integer)

    # transactionR = relationship('Transaction', foreign_keys='Transaction.transactionid')
    # menuR = relationship('Menu', foreign_keys='Menu.menuid')


    def __init__(self,userid,itemid,plate,quantity,price):
        self.orderid=next(unique_sequence)
        self.userid=userid
        self.itemid=itemid
        self.plate=plate
        self.quantity=quantity
        self.price=price

class PrevOrder(UserMixin, db.Model):
    orderid   = db.Column(db.Integer, primary_key=True)
    userid   = db.Column(db.String(80), ForeignKey(User.userid))
    itemid=db.Column(db.String(80), ForeignKey(Menu.menuid))
    plate  = db.Column(db.String(80))
    quantity=db.Column(db.Integer)
    price=db.Column(db.Integer)

    # transactionR = relationship('Transaction', foreign_keys='Transaction.transactionid')
    # menuR = relationship('Menu', foreign_keys='Menu.menuid')


    def __init__(self,userid,itemid,plate,quantity,price):
        self.orderid=next(unique_sequence)
        self.userid=userid
        self.itemid=itemid
        self.plate=plate
        self.quantity=quantity
        self.price=price


# @app.route('/')
# def hello():
#     return 'Hello, World'


# @login_manager.user_loader
# def load_user(user_id):
#     return User.query.get(int(user_id))

# @app.route('/signin', methods = ['GET', 'POST'])
# def signin():
#     return render_template('signin.html')

# @app.route('/do_signin', methods = ['GET', 'POST'])
# def do_signin():
#     if(request.method=='POST'):
#         username = request.form['username']
#         password = request.form['password']
#         check_user = User.query.filter_by(username=username).first()
#         if(check_user is not None):
#             if(check_user.password == password):
#                 login_user(check_user)
#                 return "LOGGED in successfully"
#             else:
#                 return "Incorrect Password"
#         else:
#             return "No such User exists"

# @app.route('/signup', methods = ['GET', 'POST'])
# def signup():
#     return render_template('signup.html')

# @app.route('/do_signup', methods = ['GET', 'POST'])
# def do_signup():
#     if(request.method=='POST'):
#         username = request.form['username']
#         password = request.form['password']
#         check_user = User.query.filter_by(username=username).first()
#         if(check_user is not None):
#             return "User already registered, please sign in"
#         else:
#             user = User(username=username, password=password)
#             db.session.add(user)
#             db.session.commit()
#             return "Registered Successfully"

# @app.route('/signout')
# @login_required
# def signout():
#     logout_user()
#     return "Sign out successful"


# @app.route('/demo/<id>')
# def demo(id):
#     return "Id is " + id



class Home(Resource):
  
    # corresponds to the GET request.
    # this function is called whenever there
    # is a GET request for this resource
    def get(self):
  
        return jsonify({'message': 'hello world'})
  
    # Corresponds to POST request
    def post(self):
          
        data = request.get_json()     # status code
        return jsonify({'data': data}), 201
  
  
# # another resource to calculate the square of a number
# class Square(Resource):
  
#     def get(self, num):
  
#         return jsonify({'square': num**2})


# Mycode #########################################################################################



class SignUp(Resource):
    def post(self):
        data=request.get_json()
        userid = data['userid']
        name = data['username']
        password = data['password']
        check_user = User.query.filter_by(userid=userid).first()
        if(check_user is not None):
            # return "User already registered, please sign in"
            return 0
        else:
            user = User(userid=userid,name=name, password=password)
            db.session.add(user)
            db.session.commit()
            login_user(user)
            
            # # debug
            # print("Current user user id is ",current_user.userid)
            # #End of Debug

            # return "Registered Successfully"
            return 1


class Login(Resource):
    def post(self):
        data=request.get_json()
        userid = data['userid']
        password = data['password']
        check_user = User.query.filter_by(userid=userid).first()
        if(check_user is not None):
            if(check_user.password == password):
                login_user(check_user,remember=True)
                # debug
                # print("On Login Check",check_user.is_authenticated)
                # print("On Login Check",check_user.is_active)
                # print("On Login Check",check_user.is_anonymous)
                print("Current user user id is ",current_user.userid)
                print("Current user authenticated ",current_user.is_authenticated)



                response={"bool":1,"Chef":check_user.ischef}
                return response

                return 1
            else:
                response={"bool":0,"Chef":check_user.ischef}
                return response
                return 0
        else:
            return 0

@login_manager.user_loader
def load_user(userid):
    # return User.get(userid)
    # try:
    #     return User.query.get(userid)
    # except:
    #     return None
    return User.query.filter_by(userid=userid).first()


class Logout(Resource):
    # @login_required
    def get(self):
        logout_user()
        return "Sign out successful"
        # print("Sign out successful")

        


class Add(Resource):
    def post(self):
        data=request.get_json()
        menuid = data['menuid']
        halfprice = data['halfprice']
        fullprice = data['fullprice']
        check_menu = Menu.query.filter_by(menuid=menuid).first()
        if(check_menu is not None):
            return "Menu item already present. Please Add another Item"
        else:
            menu = Menu(menuid=menuid,halfprice=halfprice, fullprice=fullprice)
            db.session.add(menu)
            db.session.commit()
            return "Menu Item added Successfully"

class Read(Resource):
    def get(self):
        # # debug
        # print("Current user user id is ",current_user.is_authenticated)
        # #End of Debug
        data = Menu.query.all()
        result = {}
        for i in data:
            result[i.menuid] = {'halfprice':i.halfprice, 'fullprice': i.fullprice}
        return result

class Entry(Resource):
    def post(self):
        data = request.get_json()
        print(data)

    

        userid = data['uid']
        tip = data['tip']
        split = data['split']
        discount = data['discount']

        totalprice=0.0

       

        orderinfo=Order.query.filter_by(userid=userid).all()
        for i in orderinfo:
            # print(i.price)
            totalprice=totalprice+i.price
            prorder = PrevOrder(userid=i.userid,itemid=i.itemid,plate=i.plate,quantity=i.quantity,price=i.price)
            db.session.add(prorder)
            db.session.delete(i)
            db.session.commit()

        tipmoney=0.0
        if(tip == 1):
            pass
        elif(tip == 2):
            tipmoney=totalprice*0.10
        elif(tip == 3):
            tipmoney=totalprice*.20

        

        totalprice=totalprice+tipmoney

        discountmoney=totalprice*discount
        totalprice=totalprice-discountmoney
        # print("Original total ",totalprice)
        # print(discountmoney)
        # print(totalprice)

        


        transaction = Transaction(userid=userid,tip=tip, discount=discount,split=split,total=totalprice)
        db.session.add(transaction)
        db.session.commit()

        total_discount={'total':totalprice,'discount':discountmoney}
        return total_discount
       


class Fetch(Resource):
    def get(self):
        data=request.get_json()
        userid=data['userid']
        data = Transaction.query.filter_by(userid=userid).all()
        if(data is not None):
            result={}
            for check_transaction in data:
                result[check_transaction.transactionid] = {'userid':check_transaction.userid, 'tip': check_transaction.tip,'discount':check_transaction.discount,'split':check_transaction.split,'total':check_transaction.total}
            return result
        else:
            return "userid is Wrong"



class AllTransaction(Resource):
    def get(self):
        data = Transaction.query.all()
        result = {}
        for check_transaction in data:
            result[check_transaction.transactionid] = {'userid':check_transaction.userid, 'tip': check_transaction.tip,'discount':check_transaction.discount,'split':check_transaction.split,'total':check_transaction.total}
        return result


class OrderFood(Resource):
    def post(self):
        data=request.get_json()

        # print(data)

        # {'1': {'platesize': 'half', 'quantity': 2, 'price': 24, 'userid': '1'}, '2': {'platesize': 'full', 'quantity': 3, 'price': 90, 'userid': '1'}}

        for i in data:
            # neworder=Order()
            # print(data[i]['userid'],i,data[i]['platesize'],data[i]['quantity'],data[i]['price'])
            neworder=Order(userid=data[i]['userid'],itemid=i,plate=data[i]['platesize'],quantity=data[i]['quantity'],price=data[i]['price'])
            db.session.add(neworder)
            db.session.commit()
            # print(i)
        return "Order Placed Successfully"


        # itemno=data['itemno']
        # platesize=data['platesize']
        # quantity=data['quantity']
        # price=data['price']
        


        

        



api.add_resource(Home, '/')
api.add_resource(SignUp, '/user/signup')
api.add_resource(Login, '/user/login')
api.add_resource(Logout, '/user/logout')
api.add_resource(Add, '/menu/add')
api.add_resource(Read, '/menu/read')
api.add_resource(Entry, '/transaction/entry')
api.add_resource(Fetch, '/transaction/fetch')
api.add_resource(AllTransaction, '/transaction/all')
api.add_resource(OrderFood, '/orderfood')






db.create_all()
chef = User.query.filter_by(userid="121").first()
if(chef is not None):
    pass
else:
    newchef = User(userid="121",name="chef1",password="password",ischef=True)
    db.session.add(newchef)
    db.session.commit()


if(__name__ == '__main__'):
    app.run(port=8000,debug=True)
    


# app.run(port=8000,debug=True)