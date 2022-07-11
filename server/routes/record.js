const Note = require('../models/note');
const express = require("express");
const recordRoutes = express.Router();
const dbo = require("../db/conn");
const ObjectId = require("mongodb").ObjectId;

const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const port = new SerialPort({ path: 'COM6', baudRate: 9600 });
let cod = {};
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

parser.on('data', function (dado) {
  cod = dado;
  espera();
});


function espera() {
  port.write("A");
}

function ok() {
  port.write("G");
}

function erro() {
  port.write("R");
}


recordRoutes.route("/registro").get(function (req, res) {
  let db_connect = dbo.getDb("test");
  db_connect
    .collection("passageiros")
    .find({})
    .toArray(function (err, result) {
      if (err) throw err;
      res.json(result);
    });
});

recordRoutes.route("/busca").get(function (req, res) {
    let db_connect = dbo.getDb("test");
    db_connect
      .collection("passageiros")
      .find({ RFID: cod })
      .toArray(function (err, result) {
        if (err) throw err;

        let x = JSON.stringify(result);
        let y = x.substring(85);
        //console.log(y)
        if (y == '') {
          erro();
          espera();
        } else if (y == 'Atrasada"}]') {
          res.json(result);
          erro();
          espera();
        } else if (y == ':"Paga"}]') {
          res.json(result);
          ok();
          espera();
        }
      });
});

module.exports = recordRoutes;
