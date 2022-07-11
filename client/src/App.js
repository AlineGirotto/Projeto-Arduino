import './App.css';
import { BrowserRouter, Link, Route } from "react-router-dom";
import { Registro } from "./components/Registro";
import { Cartao } from "./components/Cartao";

function App() {
  return (
    <div className="App">
      <BrowserRouter>
      <nav className="menu">
          <ul>
            <li>
              <Link to="/registro">Lista</Link>
            </li>
            <li>
              <Link to="/cartao">Home</Link>
            </li>
          </ul>
        </nav>
      <div className="Main">
      <Route exact path="/registro" component={Registro} />
      <Route exact path="/" component={Cartao} />
      <Route exact path="/cartao" component={Cartao} />
    </div>
      </BrowserRouter>
    </div>
  );
}

export default App;