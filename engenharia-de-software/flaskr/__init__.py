from flask import Flask, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from flaskr import models, routes


def create_app():
    app = Flask(__name__)
    app.config.from_mapping(
        SQLALCHEMY_DATABASE_URI="postgresql://postgres:postgres@localhost/imor",
        SQLALCHEMY_ECHO=True,
        SQLALCHEMY_TRACK_MODIFICATIONS=False,
        FLASK_ENV="development",
        SECRET_KEY="dev",
    )

    @app.route("/")
    def index():
        return redirect(url_for("products.index"))

    with app.app_context():
        models.init_db()
        routes.init_routes()

    return app
