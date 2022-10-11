#!/usr/bin/python3

from flask import Flask
from sensorAPI import DemoCommand
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
demo_board = DemoCommand()

@app.route("/")
def test():
    return "<p>HTTP Demo Board API</p>"   

@app.route("/gyro")
def get_gyro():
    return(demo_board.getGyroData())

@app.route("/pot")
def get_pot():
    return(demo_board.getPotData())

@app.route("/switch")
def get_switch():
    return(demo_board.getSwitchData())

@app.route("/all")
def get_all():
    return(demo_board.getAllData())

app.run(host="localhost", port=3005)