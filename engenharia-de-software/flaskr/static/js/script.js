document.querySelectorAll('tr.select').forEach(function(tr) {
  tr.addEventListener('click', function() {
    document.querySelectorAll('input[type="radio"').forEach(function(input) {
      input.removeAttribute('checked');
    });

    document
      .querySelector('input[value="' + tr.id + '"]')
      .setAttribute('checked', 'checked');
  });
});

document
  .querySelectorAll('button.main-section__add-button')
  .forEach(function(button) {
    button.addEventListener('click', function() {
      let row = document.createElement('tr');
      let tr = document.querySelector(
        '[id="' + button.getAttribute('value') + '"]',
      );
      let qtd = document.getElementById('qtd_item').value;
      let qtd_btn = document.getElementById('qtd_item');
      if (qtd == '') {
        qtd_btn.value = '';
        qtd_btn.focus();
        return;
      }

      let p_id = tr.querySelector('[name=id]').innerHTML;
      row.setAttribute('name', p_id);
      let exists = document.querySelector('tr[name="' + p_id + '"]');
      if (exists !== null) {
        let ex_qtd = exists.querySelector('input[name="qtt"]');
        ex_qtd.value = (parseInt(ex_qtd.value) + parseInt(qtd)).toString();
        let ex_price = exists.querySelector('td[name="total"]');

        let ex_p_item = tr.querySelector('td[name="price"]');

        ex_price.innerHTML =
          'R$ ' +
          (
            parseFloat(ex_p_item.innerHTML.split(' ')[1]) *
            parseFloat(ex_qtd.value)
          ).toFixed(2);

        let order_total = document.getElementById('order_total');
        let list = document.getElementById('product-list');
        let f_total = 0.0;
        list.querySelectorAll('td[name="total"]').forEach(function(item) {
          f_total += parseFloat(item.innerHTML.split(' ')[1]);
        });

        order_total.value = f_total.toFixed(2);

        qtd_btn.value = '';
        qtd_btn.focus();

        return;
      }

      let hidden = document.getElementById('nxt_item');
      let td = document.createElement('td');
      td.innerHTML = hidden.value;
      row.appendChild(td);
      hidden.value = (parseInt(hidden.value) + 1).toString();

      let item_price;
      let ind = document.createElement('input');
      ind.setAttribute('name', 'code');
      ind.readOnly = true;
      ind.setAttribute('value', p_id);
      td = document.createElement('td');
      td.appendChild(ind);
      row.appendChild(td);

      ['name', 'brand', 'price'].forEach(function(a) {
        txt = tr.querySelector('[name=' + a + ']').innerHTML;
        if (a === 'price') {
          txt = txt.split(' ')[1];
          item_price = 'R$ ' + (parseFloat(txt) * parseFloat(qtd)).toFixed(2);
          txt = 'R$ ' + txt;
        }
        td = document.createElement('td');
        td.innerHTML = txt;
        row.appendChild(td);
      });

      let qtd_input = document.createElement('input');
      qtd_input.readOnly = true;
      qtd_input.value = qtd;
      qtd_input.setAttribute('name', 'qtt');
      td = document.createElement('td');
      td.appendChild(qtd_input);
      row.appendChild(td);

      td = document.createElement('td');
      td.innerHTML = item_price;
      td.setAttribute('name', 'total');
      row.appendChild(td);

      let btn = document.createElement('button');
      btn.innerHTML = 'remover';
      btn.className = 'main-section__add-button';

      btn.addEventListener('click', function() {
        row.remove();
      });

      td = document.createElement('td');
      td.appendChild(btn);
      row.appendChild(td);
      document.getElementById('product-list').appendChild(row);

      // Calcula o total

      let order_total = document.getElementById('order_total');
      let list = document.getElementById('product-list');
      let f_total = 0.0;
      list.querySelectorAll('td[name="total"]').forEach(function(item) {
        f_total += parseFloat(item.innerHTML.split(' ')[1]);
      });

      order_total.value = f_total.toFixed(2);

      qtd_btn.value = '';
      qtd_btn.focus();
    });
  });
