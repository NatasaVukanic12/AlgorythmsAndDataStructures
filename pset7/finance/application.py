from cs50 import SQL
import time
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
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

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    user_info = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    sh = db.execute("SELECT symbol, sum(quantity), company_name, sum(quantity * price) FROM users_shares WHERE user_id=:user group by symbol", \
        user=session["user_id"])
        
    # ukupan imetak: novac na racunu + vrednost svih nekretnina
    total = sum(x["sum(quantity * price)"] for x in sh)
    total += user_info[0]["cash"]
    
    result = {"user" : user_info[0], "share" : sh, "total" : total}
    return render_template("index.html", result=result)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    
    if request.method == "GET":
        return render_template("buy.html")
    
    if request.method == "POST": 
        """Buy shares of stock."""
        shares = lookup(request.form.get("symbol"))
        num_shares = int(request.form.get("quantity"))
        
        if shares == None:
            return apology("Stock Symbol must be provided.")
            
        if num_shares < 0:
            return apology("You must provide a positive number of shares")
        
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        
        if(shares["price"] * num_shares) > rows[0]["cash"]:
            return apology("You need more cash to buy " +  str(num_shares) + " " + str(shares["name"]) + " shares.")
            
        db.execute("INSERT INTO users_shares VALUES (:user_id, :symbol, :quantity, :price, :company_name, :date_and_time,  NULL)", \
        user_id=session["user_id"], symbol=shares["symbol"], quantity=num_shares, price=shares["price"], company_name=shares["name"], date_and_time=time.strftime("%c"))
            
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", id=session["user_id"], \
            cash=rows[0]["cash"] - shares["price"]*num_shares)
        
        return redirect(url_for("buy"))
    
@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    sh = db.execute("SELECT symbol, quantity, price, company_name, date_and_time FROM users_shares WHERE user_id=:user", \
        user=session["user_id"])
    
    return render_template("history.html", shares=sh)
   # return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        return render_template("quoted.html", data=lookup(request.form.get("symbol")))

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
        
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
            
        #ensure confirmation was submitted
        elif not request.form.get("confirm_password"):
            return apology("must provide password confirmation")
            
        #ensure confirmation is same as password
        elif request.form.get("password") != request.form.get("confirm_password"):
            return apology("password and confirm password must be same")
        
        #checks if user exist
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            return apology("already exists user with username: ", request.form.get("username"))

        psw_hash = pwd_context.encrypt(request.form.get("password"))
        rows = db.execute("INSERT INTO users VALUES (NULL, :username, :hash,'10000.0')", username=request.form.get("username"), \
            hash=psw_hash)

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    # return apology("TODO")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "GET":
        sh = db.execute("SELECT symbol, sum(quantity), company_name FROM users_shares WHERE user_id=:user group by symbol", \
            user=session["user_id"])
        
        for share in sh:
            # ne zelimo da prikazemo ako imamo 0 deonica u zbiru
            if share["sum(quantity)"] == 0:
                sh.remove(share)
                continue
            share["current_price"] = lookup(share["symbol"])["price"]
        return render_template("sell.html", shares=sh)
    
    if request.method == "POST":
        shares = lookup(request.form.get("symbol"))
        db.execute("UPDATE users SET cash=cash+:cash WHERE id=:id", id=session["user_id"], \
            cash=int(request.form.get("number_to_sell")) * float(request.form.get("price")))
        db.execute("INSERT INTO users_shares VALUES (:user_id, :symbol, :quantity, :price, :company_name, :date_and_time,  NULL)", \
        user_id=session["user_id"], symbol=shares["symbol"], quantity=-int(request.form.get("number_to_sell")), price=shares["price"], company_name=shares["name"], date_and_time=time.strftime("%c"))
        return redirect(url_for("sell"))
    
    else:
        return render_template("index.html")