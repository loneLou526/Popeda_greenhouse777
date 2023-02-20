from flask import Flask, request

app = Flask(__name__)

@app.route("/api",methods=['POST'])
def hello():

    print(request.json['temp'])

    print(f"Request sended by {request.json['id']}") 
    return f"25;15;50;2"

if __name__ == "__main__":
    app.run(host="0.0.0.0")