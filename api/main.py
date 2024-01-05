from flask import Flask, jsonify,request
from flask_cors import CORS
import serial
import time

app = Flask(__name__)
CORS(app)

ser = serial.Serial('COM4',baudrate=115200,timeout=1)

@app.route('/api/test',methods = ['GET'])
def get_data():
    return jsonify({'message':'Asssssss'})

@app.route('/api/input',methods = ['POST'])
def sendKeyPress():
    number = request.json.get('number')
    
    try:
        keypress = int(number)
    except ValueError:
        return jsonify({'error':'Invalid key input'}),400
    
    ser.write(str(keypress).encode())
    return jsonify({
        'message':'Keypress sent to Com4'
    })

if __name__=='__main__':
    app.run(port=5000)