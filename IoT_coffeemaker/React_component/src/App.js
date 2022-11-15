import './index.css';
import React from "react";
//import coffee from './coffee.js';
import empty from "./images/coffee_empty.png";
/*
import low from './images/coffee_low.png';
import mid from './images/coffee_mid.png';
import high from './images/coffee_high.png';
*/



class App extends React.Component {

    constructor(props) {
        super(props);
   
        this.state = {
            items: [],
            DataisLoaded: false
        };
    }

    componentDidMount() {
        fetch("http://10.5.1.29/from_mega")
            .then((res) => res.json())
            .then((json) => {
                this.setState({
                    items: json,
                    DataisLoaded: true
                });
            })
    }
  
    render() {

        const { DataisLoaded, items,} = this.state;
        if (!DataisLoaded) return <div>
            <h1> Loading... </h1> </div> ;
   
        return (
        <div className = "App">
            <h1> IoT_Coffeemaker</h1>
                    <img src={empty} alt="empty-coffeepot" style={{ height: "20vh" }}></img>
             {
                items.map((item) => ( 
                <ol key = {item}>
                    Coffee temperature: { item.temperature } °C
                    <div>Coffee amount: { item.weight } L</div>
                    <progress value = {item.weight} max ="1"/>
                    </ol>
                ))
            
            }
            <button onClick={() => window.location.reload()}>Refresh</button>
        </div>
    );

} 
}
   export default App;

