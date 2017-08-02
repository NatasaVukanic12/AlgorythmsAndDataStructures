from cs50 import SQL
import time
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.hash import pbkdf2_sha256 as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///user.db")

@app.route("/") 
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])  #DONE
def login():
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("password"):
            return apology("must provide password")
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]['hash']):
            return apology("invalid username and/or password")
        session["user_id"] = rows[0]["id"]
        return redirect(url_for("index"))
    else:
        return render_template("login.html")
        
@app.route("/register", methods=["GET", "POST"]) #DONE
def register():
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("password"):
            return apology("must provide password")
        elif not request.form.get("confirm_password"):
            return apology("must provide password confirmation")
        elif request.form.get("password") != request.form.get("confirm_password"):
            return apology("password and confirm password must be same")
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology("already exists user with username: ", request.form.get("username"))
        
        psw_hash = pwd_context.hash(request.form.get("password"))
    
        rows = db.execute("INSERT INTO users VALUES (NULL, :username, :hash, :first_name, :last_name, :email, :orders)", \
        username=request.form.get("username"), hash=psw_hash, first_name=request.form.get("first_name"), \
        last_name=request.form.get("last_name"), email=request.form.get("email"), orders = 0 )
        return redirect(url_for("index"))
    else:
        return render_template("register.html")
        
@app.route("/logout")  #DONE
def logout():
    session.clear()
    return redirect(url_for("index"))

@app.route("/about")
def about():
    return render_template("about.html")


@app.route("/menu")
def menu():
    return render_template("menu.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        result = {"name" : request.args.get("name"), "img" : request.args.get("img"), "price" : request.args.get("price")}
        return render_template("buy.html", result=result)
    
    elif request.method == "POST":
        db.execute("INSERT INTO reciept VALUES (NULL, :user, :item, :price, :time, :quantity, :flavour, :colour, :topping, :note)", user=session["user_id"], item=request.form["name"],\
        price=request.form["price"], time=time.strftime("%c"), quantity=request.form["quantity"], flavour=request.form["flavour"], colour=request.form["colour"], topping=request.form["topping"], note=request.form["note"])
        return render_template("menu.html")

@app.route("/contact")     #DONE
def contact():
    return render_template("contact.html")
    
@app.route("/cakesU", methods=["GET", "POST"])
def cakesU():
    sh = db.execute("SELECT type, name, price, img FROM article WHERE type='Torta' ")
    return render_template("cakes.html", cake=sh)
    
@app.route("/cakesD", methods=["GET", "POST"])
def cakesD():
    sh = db.execute("SELECT type, name, price, img FROM article WHERE type='Kolac' ")
    return render_template("cakes.html", cake=sh)
    
@app.route("/cakesT", methods=["GET", "POST"])
def cakesT():
    sh = db.execute("SELECT type, name, price, img FROM article WHERE type='Kolacici' ")
    return render_template("cakes.html", cake=sh)
    
@app.route("/cakesQ", methods=["GET", "POST"])
def cakesQ():
    sh = db.execute("SELECT type, name, price, img FROM article WHERE type='Cinija' ")
    return render_template("cakes.html", cake=sh)

@app.route("/drinks", methods=["GET", "POST"])
def drinks():
    sh = db.execute("SELECT type, name, price, img FROM article WHERE type='Pica' ")
    return render_template("cakes.html", cake=sh)