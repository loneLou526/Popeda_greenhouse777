from flask import Flask
app = Flask(__name__)

@app.route("/api")
def hello():
    print("Hello World!") 
    return "12;82;Достаточно влажная;Полный;30;1"

if __name__ == "__main__":
    app.run(host='0.0.0.0')