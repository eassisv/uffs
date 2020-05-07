from flask import Blueprint, render_template, url_for, redirect, request
from sqlalchemy import desc
from flaskr.models.clients import Client
from flaskr.models import db_add

bp = Blueprint("clients", __name__, url_prefix="/clientes")


@bp.route("/")
def index():
    clients = Client.query.all()
    return render_template(
        "/clients/index.html", breadcrumbs=[("Clientes", "#")], clients=clients
    )


@bp.route("/adicionar", methods=["GET", "POST"])
def client_add():
    if request.method == "POST":
        form = request.form
        client = Client(
            form["name"],
            form["full_name"],
            form["cnpj"],
            form["address"],
            form["email"],
            form["phone"],
        )

        db_add(client)
        return redirect(url_for("clients.index"))

    client = Client.query.order_by(desc(Client.id)).first()
    code = 1 if client == None else client.id + 1
    return render_template(
        "/clients/add.html",
        breadcrumbs=[("Clientes", url_for("clients.index")), ("Adicionar", "#")],
        code=code,
    )
