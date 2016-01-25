from flask import Flask, render_template, request
from flask_socketio import SocketIO
from flask_socketio import send, emit
import serial
import sys

if len(sys.argv) < 2:
    "Usage: python app.py <arduino_port>"
    sys.exit(1)
port=sys.argv[1]
arduinoSerial = serial.Serial(port, 9600)

app = Flask(__name__)
socketio = SocketIO(app)


@app.route('/')
def main():
    return render_template('main.html')

lastValues = [100, 100, 100, 100]

@socketio.on('connect')
def connect():
    global lastValues
    print "connected: %s" % lastValues
    emit('firstValues', lastValues)

@socketio.on('led_change')
def handle_led_change(obj):
    global lastValues
    lastValues = obj['leds']
    values=','.join([str(n) for n in obj['leds']])
    print "changes: %s" % values
    arduinoSerial.write(values+ ',')

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)
