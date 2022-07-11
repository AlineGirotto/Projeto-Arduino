import React, { useEffect, useState } from "react";

const Passageiro = (props) => (
  <tr>
    <td>{props.passageiro.Nome}</td>
    <td>{props.passageiro.RFID}</td>
    <td>{props.passageiro.Mensalidade}</td>
  </tr>
);

export function Registro() {
  const [passageiro, setPassageiro] = useState([]);

  useEffect(() => {
    async function getPassageiro() {
      const response = await fetch(`http://localhost:5000/registro`);

      if (!response.ok) {
        const message = `An error occured: ${response.statusText}`;
        window.alert(message);
        return;
      }

      const passageiro = await response.json();
      setPassageiro(passageiro);
    }

    getPassageiro();

  }, [passageiro.length]);


  function recordList() {
    return passageiro.map((passageiro) => {
      return (
        <Passageiro
        passageiro={passageiro}
          key={passageiro._id}
        />
      );
    });
  }
  return (
    <div class="tudo">
      <h2>Listagem de Passageiros:</h2>
      <div class="cont1">
        <table class="passageiro">
        <thead>
         <tr>
           <th>Nome</th>
           <th>RFID</th>
           <th>Mensalidade</th>
         </tr>
       </thead>
       <tbody>{recordList()}</tbody>
        </table>
      </div>
    </div>
  );
}
