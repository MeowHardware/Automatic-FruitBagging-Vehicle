from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def hello_world():
    print(request.dat)
    return "<p>Hello, World!</p>"

app.run(host="0.0.0.0" ,debug=True)
# pip install flask