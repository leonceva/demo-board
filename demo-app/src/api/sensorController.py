#!/usr/bin/python3

from flask import Flask
from sensorAPI import DemoCommand
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
try:
    demo_board = DemoCommand()
except Exception as e:
    print("Unable to start Demo Board: %s" % e)

@app.route("/")
def test():
    return "<p>HTTP Demo Board API</p>"   

@app.route("/gyro")
def get_gyro():
    try:
        return(demo_board.getGyroData())
    except Exception as e:
        print("Unable to reach Demo Board: %s" % e)
        return

@app.route("/pot")
def get_pot():
    try:
        return(demo_board.getPotData())
    except Exception as e:
        print("Unable to reach Demo Board: %s" % e)
        return

@app.route("/switch")
def get_switch():
    try:
        return(demo_board.getSwitchData())
    except Exception as e:
        print("Unable to reach Demo Board: %s" % e)
        return

@app.route("/all")
def get_all():
    try:
        return(demo_board.getAllData())
    except Exception as e:
        print("Unable to reach Demo Board: %s" % e)
        return

app.run(host="localhost", port=3005)