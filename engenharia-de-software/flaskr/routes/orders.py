from flask import Blueprint, render_template, request, redirect, url_for, flash
from flaskr.models.clients import Client
from flaskr.models.products import Product
from flaskr.models.orders import Order, Order_Item
from flaskr.models import db_add
from sqlalchemy import desc
from datetime import date

bp = Blueprint("orders", __name__, url_prefix="/pedidos")


@bp.route("/")
def index():
    orders = Order.query.all()
    return render_template(
        "/orders/index.html", breadcrumbs=[("Pedidos", "#")], orders=orders
    )


@bp.route("/adicionar", methods=["GET", "POST"])
def order_add():
    if request.method == "POST":

        form = request.form

        delivery_date = form["delivery_date"]
        products = form.getlist("code")
        qtts = form.getlist("qtt")

        total_price = 0
        total_items = 0
        for p, q in zip(products, qtts):
            total_price = total_price + Product.query.filter(
                Product.id == p
            ).first().sale_price * int(q)
            stock = Product.query.filter(Product.id == p).total_quantity
            if stock < int(q):
                flash("Alguns produtos do pedido estão em falta")
                return redirect(url_for("orders.index"))

            total_items = total_items + int(q)

        order = Order(
            total_price,
            date.today(),
            total_items,
            "Pendente",
            delivery_date,
            int(form["client"]),
        )
        db_add(order)

        order_id = Order.query.order_by(desc(Order.id)).first().id

        for p, q in zip(products, qtts):
            order_price = Product.query.filter(
                Product.id == p
            ).first().sale_price * int(q)
            order_item = Order_Item(order_id, p, int(q), order_price)
            db_add(order_item)

        return redirect(url_for("orders.index"))

    if request.args.get("client") != None:
        try:
            client = int(str(request.args.get("client")))
        except ValueError:
            flash("Cliente inválido")
            return redirect(url_for("orders.index"))

        products = Product.query.all()
        return render_template(
            "/orders/add_products.html",
            breadcrumbs=[
                ("Pedidos", url_for("orders.index")),
                ("Selecionar Cliente", url_for("orders.order_add")),
                ("Selecionar Produtos", "#"),
            ],
            products=products,
            min_date=date.fromordinal(date.today().toordinal() + 2),
            client=client,
        )

    clients = Client.query.all()
    return render_template(
        "/orders/add_client.html",
        breadcrumbs=[("Pedidos", url_for("orders.index")), ("Selecionar Cliente", "#")],
        clients=clients,
    )
