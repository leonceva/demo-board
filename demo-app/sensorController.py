#!/usr/bin/python3

from flask import Flask
from sensorAPI import DemoCommand

app = Flask(__name__)
demo_board = DemoCommand()

@app.route("/")
def test():
    return "<p>HTTP Demo Board API</p>"   



app.run(host="localhost", port=3005)