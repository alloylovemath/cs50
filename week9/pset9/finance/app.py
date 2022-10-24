import os
import time

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    list_of_shares = db.execute("SELECT symbol, shares FROM portfolios WHERE user_id = ?", session["user_id"])
    total = 0
    ls_s = []
    for i in range(len(list_of_shares)):
        symbol_e = list_of_shares[i]["symbol"]
        name_e = lookup(symbol_e)["name"]
        shares_e = list_of_shares[i]["shares"]
        price_e = lookup(symbol_e)["price"]
        total_e = int(shares_e) * price_e
        total += total_e
        ls_s.append((symbol_e, name_e, shares_e, usd(price_e), usd(total_e)))
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total_value = total + cash
    inform_package = [ls_s, usd(cash), usd(total_value)]
    return render_template("index.html", inform_package=inform_package)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    # invalid input
    symbol = request.form.get("symbol")
    inform_of_symbol = lookup(symbol)
    if not symbol or inform_of_symbol == None:
        return apology("Invalid symbol", 400)

    shares = request.form.get("shares")
    if not shares:
        return apology("Invalid shares", 400)
    # never trust client-side check!!!
    digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    dot_count = 0
    for item in shares:
        if item == ".":
            dot_count += 1
        if item not in digits:
            return apology("Silly!!!", 400)
    if dot_count > 1:
        return apology("Silly!!!", 400)
    if type(eval(shares)) != int:
        return apology("Invalid shares", 400)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    payment = inform_of_symbol["price"]*int(shares)
    if payment > cash:
        return apology("Oops, no enough money", 400)

    remaining_cash = cash - payment
    checking = db.execute("SELECT * FROM portfolios WHERE symbol = ?", inform_of_symbol["symbol"])

    # purchasing
    if len(checking) < 1:
        db.execute("INSERT INTO portfolios (user_id, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, int(shares))
    else:
        db.execute("UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?",
                   checking[0]["shares"] + int(shares), session["user_id"], symbol)
    db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, session["user_id"])
    db.execute("INSERT INTO transactions (user_id, symbol, shares, transaction_price, time, type) VALUES (?, ?, ?, ?, ?, 'buy')",
               session["user_id"], symbol, int(shares), inform_of_symbol["price"], time.strftime("%Y-%m-%d %H:%M:%S"))
    flash("Bought!")
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    ls_inform = []
    ls_inform_r = db.execute(
        "SELECT symbol, shares, transaction_price, time, type FROM transactions WHERE user_id = ?", session["user_id"])
    for i in range(len(ls_inform_r)):
        if ls_inform_r[i]["type"] == "buy":
            ls_inform.append([ls_inform_r[i]["symbol"], ls_inform_r[i]["shares"],
                              usd(ls_inform_r[i]["transaction_price"]), ls_inform_r[i]["time"]])
        if ls_inform_r[i]["type"] == "sell":
            ls_inform.append([ls_inform_r[i]["symbol"], -1*ls_inform_r[i]["shares"],
                              usd(ls_inform_r[i]["transaction_price"]), ls_inform_r[i]["time"]])
    return render_template("history.html", inform=ls_inform)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol")
    if not symbol:
        return apology("must provide symbol", 400)

    # inform is a dict
    inform_r = lookup(symbol)
    if inform_r == None:
        return apology("must provide symbol", 400)
    inform = [inform_r["name"], inform_r["symbol"], usd(inform_r["price"])]
    return render_template("quoted.html", inform=inform)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    # validate input
    username = request.form.get("username")
    if not username:
        return apology("must provide username", 400)
    check_name = db.execute("SELECT username FROM users WHERE username = ?", username)
    if len(check_name) != 0:
        return apology("username already exists", 400)

    password = request.form.get("password")
    if not password:
        return apology("must provide password", 400)

    confirmation = request.form.get("confirmation")
    if password != confirmation:
        return apology("passwords not match", 400)

    # add new users

    # transform user's password to it's hash
    password_hash = generate_password_hash(password)

    db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        ls_s = []
        ls_e = db.execute("SELECT symbol FROM portfolios WHERE user_id = ?", session["user_id"])
        for i in range(len(ls_e)):
            ls_s.append(ls_e[i]["symbol"])
        return render_template("sell.html", ls_s=ls_s)

    # valid input
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("Missing symbol", 403)
    inform_of_symbol = lookup(symbol)

    shares = request.form.get("shares")
    shares_r = db.execute("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?",
                          session["user_id"], symbol)[0]["shares"] - int(shares)
    if not shares or shares_r < 0:
        return apology("Invalid shares", 400)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    payment_b = inform_of_symbol["price"]*int(shares)

    remaining_cash = cash + payment_b

    # selling
    if shares_r == 0:
        db.execute("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
    else:
        db.execute("UPDATE portfolios SET shares = ? WHERE user_id = ? AND symbol = ?", int(shares_r), session["user_id"], symbol)
    db.execute("UPDATE users SET cash = ? WHERE id=?", remaining_cash, session["user_id"])
    db.execute("INSERT INTO transactions (user_id, symbol, shares, transaction_price, time, type) VALUES (?, ?, ?, ?, ?, 'sell')",
               session["user_id"], symbol, int(shares), inform_of_symbol["price"], time.strftime("%Y-%m-%d %H:%M:%S"))
    flash("Sold!")
    return redirect("/")
